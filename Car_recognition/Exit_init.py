"""
停车场出口初始化
"""
import argparse
import os
import sqlite3
import torch
from picamera2 import Picamera2
from Car_recognition import load_model, init_model, init_car_rec_model, detect_Recognition_plate, draw_result
from datetime import datetime
from gpiozero import DistanceSensor

from database_op import insert_data_when_enter
from plate_recognition.plate_rec import cv_imread
import cv2

sensor_tri = 14
sensor_echo = 15

if __name__ == '__main__':
    # 初始化模型
    parser = argparse.ArgumentParser()
    parser.add_argument('--detect_model', nargs='+', type=str, default='weights/detect.pt',
                        help='model.pt path(s)')  # 检测模型
    parser.add_argument('--rec_model', type=str, default='weights/plate_rec_color.pth',
                        help='model.pt path(s)')  # 车牌识别+车牌颜色识别模型
    parser.add_argument('--car_rec_model', type=str, default='weights/car_rec_color.pth',
                        help='car_rec_model')  # 车辆识别模型
    parser.add_argument('--image_path', type=str, default='imgs_backup', help='source')
    parser.add_argument('--img_size', type=int, default=384, help='inference size (pixels)')
    parser.add_argument('--output', type=str, default='result1', help='source')
    parser.add_argument('--video', type=str, default='', help='source')

    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    # device =torch.device("cpu")

    opt = parser.parse_args()
    print(opt)
    save_path = opt.output
    count = 0

    detect_model = load_model(opt.detect_model, device)
    plate_rec_model = init_model(device, opt.rec_model)
    car_rec_model = init_car_rec_model(opt.car_rec_model, device)

    total_detect = sum(p.numel() for p in detect_model.parameters())
    total_plate = sum(p.numel() for p in plate_rec_model.parameters())
    # print("detect params: %.2fM,rec params: %.2fM" % (total_detect / 1e6, total_plate / 1e6))

    # 初始化距离传感器和摄像头
    sensor = DistanceSensor(trigger=sensor_tri, echo=sensor_echo)  # 传感器
    sensor.max_distance = 10

    picam2 = Picamera2()
    camera_config = picam2.create_preview_configuration()
    picam2.configure(camera_config)

    # 初始化数据库
    conn = sqlite3.connect('ipms.db')
    cursor = conn.cursor()

    while True:
        # print('Distance to nearest object is', sensor.distance, 'm')
        # sleep(1)
        if sensor.distance < 5:
            picam2.start()
            timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]
            filename = str(timestamp)
            picam2.capture_file(f"./imgs/{filename}.jpg")
            img = cv_imread(f"./imgs/{filename}.jpg")

            if img.shape[-1] == 4:
                img = cv2.cvtColor(img, cv2.COLOR_BGRA2BGR)

            dict_list = detect_Recognition_plate(detect_model, img, device, plate_rec_model, opt.img_size,
                                                 car_rec_model)
            ori_img = draw_result(img, dict_list)
            img_name = os.path.basename(f"./imgs/{filename}.jpg")
            save_img_path = os.path.join(save_path, img_name)
            cv2.imwrite(save_img_path, ori_img)

            car_color = ', '.join([item['car_color'] for item in dict_list if 'car_color' in item])
            plate_color = ', '.join([item['plate_color'] for item in dict_list if 'plate_color' in item])
            plate_no = ', '.join([item['plate_no'] for item in dict_list if 'plate_no' in item])
            plate_confidence = [item['score'] for item in dict_list if 'plate_no' in item]
            if plate_confidence < 0.9:
                print("车牌不可信")
                continue
            if plate_no:
                timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]
                if (plate_color == '绿色') and (len(plate_no) == 8):
                    print("新能源绿牌汽车")
                    print(f"车牌号码: {plate_no}")
                    insert_data_when_enter(timestamp, plate_no, "新能源小汽车", car_color)
                elif (plate_color == '蓝色') and (len(plate_no) == 7):
                    print("普通蓝牌汽车")
                    print(f"车牌号码: {plate_no}")
                    insert_data_when_enter(timestamp, plate_no, "普通汽车", car_color)
                else:
                    os.remove(f"./imgs/{filename}.jpg")
                    os.remove(f"./{save_img_path}/{filename}".jpg)
                    print("车牌不合法或不在考虑的范围")
                    print(f"车牌号码: {plate_no}")
            else:
                os.remove(f"./imgs/{filename}.jpg")
                os.remove(f"./{save_img_path}/{filename}".jpg)


