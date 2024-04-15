# -*- coding: UTF-8 -*-
import argparse
import sqlite3
import time
import cv2
import os
import torch
# from numpy import random
import copy
import numpy as np
from picamera2 import Picamera2
from database_op import insert_data_when_enter
from models.experimental import attempt_load
from utils.datasets import letterbox
from utils.general import check_img_size, non_max_suppression_face, scale_coords
from utils.torch_utils import time_synchronized
from utils.cv_puttext import cv2ImgAddText
from plate_recognition.plate_rec import get_plate_result, allFilePath, init_model, cv_imread
# from plate_recognition.plate_cls import cv_imread
from plate_recognition.double_plate_split_merge import get_split_merge
# from plate_recognition.color_rec import plate_color_rec, init_color_model
from car_recognition.car_rec import init_car_rec_model, get_color_and_score
from datetime import datetime

clors = [(255, 0, 0), (0, 255, 0), (0, 0, 255), (255, 255, 0), (0, 255, 255)]
danger = ['危', '险']
object_color = [(0, 255, 255), (0, 255, 0), (255, 255, 0)]
class_type = ['单层车牌', '双层车牌', '汽车']


def order_points(pts):  # 四个点安好左上 右上 右下 左下排列
    """

    @param pts:
    @return:
    """
    rect = np.zeros((4, 2), dtype="float32")
    s = pts.sum(axis=1)
    rect[0] = pts[np.argmin(s)]
    rect[2] = pts[np.argmax(s)]
    diff = np.diff(pts, axis=1)
    rect[1] = pts[np.argmin(diff)]
    rect[3] = pts[np.argmax(diff)]
    return rect


def four_point_transform(image, pts):  # 透视变换得到车牌小图
    """

    @param image:
    @param pts:
    @return:
    """
    rect = order_points(pts)
    (tl, tr, br, bl) = rect
    widthA = np.sqrt(((br[0] - bl[0]) ** 2) + ((br[1] - bl[1]) ** 2))
    widthB = np.sqrt(((tr[0] - tl[0]) ** 2) + ((tr[1] - tl[1]) ** 2))
    maxWidth = max(int(widthA), int(widthB))
    heightA = np.sqrt(((tr[0] - br[0]) ** 2) + ((tr[1] - br[1]) ** 2))
    heightB = np.sqrt(((tl[0] - bl[0]) ** 2) + ((tl[1] - bl[1]) ** 2))
    maxHeight = max(int(heightA), int(heightB))
    dst = np.array([
        [0, 0],
        [maxWidth - 1, 0],
        [maxWidth - 1, maxHeight - 1],
        [0, maxHeight - 1]], dtype="float32")
    M = cv2.getPerspectiveTransform(rect, dst)
    warped = cv2.warpPerspective(image, M, (maxWidth, maxHeight))
    return warped


def load_model(weights, device):
    model = attempt_load(weights, map_location=device)  # load FP32 model
    return model


def scale_coords_landmarks(img1_shape, coords, img0_shape, ratio_pad=None):  # 返回到原图坐标
    """

    @param img1_shape:
    @param coords:
    @param img0_shape:
    @param ratio_pad:
    @return:
    """
    # Rescale coords (xyxy) from img1_shape to img0_shape
    if ratio_pad is None:  # calculate from img0_shape
        gain = min(img1_shape[0] / img0_shape[0], img1_shape[1] / img0_shape[1])  # gain  = old / new
        pad = (img1_shape[1] - img0_shape[1] * gain) / 2, (img1_shape[0] - img0_shape[0] * gain) / 2  # wh padding
    else:
        gain = ratio_pad[0][0]
        pad = ratio_pad[1]

    coords[:, [0, 2, 4, 6]] -= pad[0]  # x padding
    coords[:, [1, 3, 5, 7]] -= pad[1]  # y padding
    coords[:, :8] /= gain
    # clip_coords(coords, img0_shape)
    coords[:, 0].clamp_(0, img0_shape[1])  # x1
    coords[:, 1].clamp_(0, img0_shape[0])  # y1
    coords[:, 2].clamp_(0, img0_shape[1])  # x2
    coords[:, 3].clamp_(0, img0_shape[0])  # y2
    coords[:, 4].clamp_(0, img0_shape[1])  # x3
    coords[:, 5].clamp_(0, img0_shape[0])  # y3
    coords[:, 6].clamp_(0, img0_shape[1])  # x4
    coords[:, 7].clamp_(0, img0_shape[0])  # y4
    # coords[:, 8].clamp_(0, img0_shape[1])  # x5
    # coords[:, 9].clamp_(0, img0_shape[0])  # y5
    return coords


def get_plate_rec_landmark(img, xyxy, conf, landmarks, class_num, device, plate_rec_model, car_rec_model):
    """

    @param img:
    @param xyxy:
    @param conf:
    @param landmarks:
    @param class_num:
    @param device:
    @param plate_rec_model:
    @param car_rec_model:
    @return:
    """
    # h, w, c = img.shape
    result_dict = {}
    x1 = int(xyxy[0])
    y1 = int(xyxy[1])
    x2 = int(xyxy[2])
    y2 = int(xyxy[3])
    landmarks_np = np.zeros((4, 2))
    rect = [x1, y1, x2, y2]

    if int(class_num) == 2:
        car_roi_img = img[y1:y2, x1:x2]
        car_color, color_conf = get_color_and_score(car_rec_model, car_roi_img, device)
        result_dict['class_type'] = class_type[int(class_num)]
        result_dict['rect'] = rect  # 车辆roi
        result_dict['score'] = conf  # 车牌区域检测得分
        result_dict['object_no'] = int(class_num)
        result_dict['car_color'] = car_color
        result_dict['color_conf'] = color_conf
        return result_dict

    for i in range(4):
        point_x = int(landmarks[2 * i])
        point_y = int(landmarks[2 * i + 1])
        landmarks_np[i] = np.array([point_x, point_y])

    class_label = int(class_num)  # 车牌的的类型0代表单牌，1代表双层车牌
    roi_img = four_point_transform(img, landmarks_np)  # 透视变换得到车牌小图
    if class_label:  # 判断是否是双层车牌，是双牌的话进行分割后然后拼接
        roi_img = get_split_merge(roi_img)
    plate_number, plate_color, min_confidence = get_plate_result(roi_img, device, plate_rec_model)  # 对车牌小图进行识别,得到颜色和车牌号
    for dan in danger:  # 只要出现‘危’或者‘险’就是危险品车牌
        if dan in plate_number:
            plate_number = '危险品'
    # cv2.imwrite("roi.jpg",roi_img)
    result_dict['class_type'] = class_type[class_label]
    result_dict['rect'] = rect  # 车牌roi区域
    result_dict['landmarks'] = landmarks_np.tolist()  # 车牌角点坐标
    result_dict['plate_no'] = plate_number  # 车牌号
    result_dict['roi_height'] = roi_img.shape[0]  # 车牌高度
    result_dict['plate_color'] = plate_color  # 车牌颜色
    result_dict['object_no'] = class_label  # 单双层 0单层 1双层
    result_dict['score'] = conf  # 车牌区域检测得分
    result_dict['min_confidence'] = min_confidence
    return result_dict


def detect_Recognition_plate(model, orgimg, device, plate_rec_model, img_size, car_rec_model=None):
    """
    这个函数用于检测车辆的颜色信息和车牌信息
    @param model: 检测模型
    @param orgimg: 原始图片
    @param device: 检测设备类型 [CPU/GPU]
    @param plate_rec_model: 车牌识别模型
    @param img_size: 图像大小
    @param car_rec_model: 车辆识别模型，默认值为 None
    @return: 包含检测信息的字典
    """
    # Load model
    # img_size = opt_img_size
    conf_thres = 0.6  # 置信度阈值
    iou_thres = 0.5  # 边框交并比
    dict_list = []
    # orgimg = cv2.imread(image_path)  # BGR
    img0 = copy.deepcopy(orgimg)
    assert orgimg is not None, 'Image Not Found '

    h0, w0 = orgimg.shape[:2]  # 原始图像的高度和宽度
    r = img_size / max(h0, w0)  # 缩放图像的缩放比
    if r != 1:  # always resize down, only resize up if training with augmentation
        interp = cv2.INTER_AREA if r < 1 else cv2.INTER_LINEAR
        img0 = cv2.resize(img0, (int(w0 * r), int(h0 * r)), interpolation=interp)

    imgsz = check_img_size(img_size, s=model.stride.max())  # check img_size

    img = letterbox(img0, new_shape=imgsz)[0]
    # img =process_data(img0)
    # Convert
    img = img[:, :, ::-1].transpose(2, 0, 1).copy()  # BGR to RGB, to 3x416x416

    # Run inference
    t0 = time.time()

    img = torch.from_numpy(img).to(device)
    img = img.float()  # uint8 to fp16/32
    img /= 255.0  # 0 - 255 to 0.0 - 1.0
    if img.ndimension() == 3:
        img = img.unsqueeze(0)

    # Inference
    t1 = time_synchronized()
    pred = model(img)[0]
    t2 = time_synchronized()
    # print(f"infer time is {(t2-t1)*1000} ms")

    # Apply NMS
    pred = non_max_suppression_face(pred, conf_thres, iou_thres)

    # print('img.shape: ', img.shape)
    # print('orgimg.shape: ', orgimg.shape)

    # Process detections
    for i, det in enumerate(pred):  # detections per image
        if len(det):
            # Rescale boxes from img_size to im0 size
            det[:, :4] = scale_coords(img.shape[2:], det[:, :4], orgimg.shape).round()

            # Print results
            for c in det[:, -1].unique():
                n = (det[:, -1] == c).sum()  # detections per class

            det[:, 5:13] = scale_coords_landmarks(img.shape[2:], det[:, 5:13], orgimg.shape).round()

            for j in range(det.size()[0]):
                xyxy = det[j, :4].view(-1).tolist()
                conf = det[j, 4].cpu().numpy()
                landmarks = det[j, 5:13].view(-1).tolist()
                class_num = det[j, 13].cpu().numpy()
                result_dict = get_plate_rec_landmark(orgimg, xyxy, conf, landmarks, class_num, device, plate_rec_model,
                                                     car_rec_model)
                dict_list.append(result_dict)
    return dict_list
    # cv2.imwrite('result.jpg', orgimg)


def draw_result(orgimg, dict_list):
    """

    @param orgimg:
    @param dict_list:
    @return:
    """
    result_str = ""
    for result in dict_list:
        rect_area = result['rect']
        object_no = result['object_no']
        if not object_no == 2:
            x, y, w, h = rect_area[0], rect_area[1], rect_area[2] - rect_area[0], rect_area[3] - rect_area[1]
            padding_w = 0.05 * w
            padding_h = 0.11 * h
            rect_area[0] = max(0, int(x - padding_w))
            rect_area[1] = max(0, int(y - padding_h))
            rect_area[2] = min(orgimg.shape[1], int(rect_area[2] + padding_w))
            rect_area[3] = min(orgimg.shape[0], int(rect_area[3] + padding_h))

            height_area = int(result['roi_height'] / 2)
            landmarks = result['landmarks']
            result_p = result['plate_no']
            if result['object_no'] == 0:  # 单层
                result_p += " " + result['plate_color']
            else:  # 双层
                result_p += " " + result['plate_color'] + "双层"
            result_str += result_p + " "
            for i in range(4):  # 关键点
                cv2.circle(orgimg, (int(landmarks[i][0]), int(landmarks[i][1])), 5, clors[i], -1)

            if len(result) >= 1:
                if "危险品" in result_p:  # 如果是危险品车牌，文字就画在下面
                    orgimg = cv2ImgAddText(orgimg, result_p, rect_area[0], rect_area[3], (0, 255, 0), height_area)
                else:
                    orgimg = cv2ImgAddText(orgimg, result_p, rect_area[0] - height_area,
                                           rect_area[1] - height_area - 10, (0, 255, 0), height_area)
        else:
            height_area = int((rect_area[3] - rect_area[1]) / 20)
            car_color = result['car_color']
            car_color_str = "车辆颜色:"
            car_color_str += car_color
            orgimg = cv2ImgAddText(orgimg, car_color_str, rect_area[0], rect_area[1], (0, 255, 0), height_area)

        cv2.rectangle(orgimg, (rect_area[0], rect_area[1]), (rect_area[2], rect_area[3]), object_color[object_no],
                      2)  # 画框
    print(result_str)
    return orgimg


def get_second(capture):
    if capture.isOpened():
        rate = capture.get(5)  # 帧速率
        FrameNumber = capture.get(7)  # 视频文件的帧数
        duration = FrameNumber / rate  # 帧速率/视频总帧数 是时间，除以60之后单位是分钟
        return int(rate), int(FrameNumber), int(duration)


if __name__ == '__main__':
    # picam2 = Picamera2()
    # camera_config = picam2.create_preview_configuration()
    # picam2.configure(camera_config)
    # picam2.start()
    if not os.path.exists("./imgs"):
        os.makedirs("./imgs")
    # filename = str(timestamp)
    # picam2.capture_file(f"./imgs/{filename}.jpg")
    # picam2.close()
    # 命令行参数解析
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

    if not os.path.exists(save_path):
        os.mkdir(save_path)

    detect_model = load_model(opt.detect_model, device)
    plate_rec_model = init_model(device, opt.rec_model)
    car_rec_model = init_car_rec_model(opt.car_rec_model, device)
    # 算参数量
    total_detect = sum(p.numel() for p in detect_model.parameters())
    total_plate = sum(p.numel() for p in plate_rec_model.parameters())
    print("detect params: %.2fM,rec params: %.2fM" % (total_detect / 1e6, total_plate / 1e6))

    time_all = 0
    time_begin = time.time()
    if not opt.video:  # 处理图片
        if not os.path.isfile(opt.image_path):
            file_list = []
            allFilePath(opt.image_path, file_list)
            for img_path in file_list:
                print(count, img_path, end=" ")
                time_b = time.time()
                img = cv_imread(img_path)

                if img is None:
                    continue
                if img.shape[-1] == 4:
                    img = cv2.cvtColor(img, cv2.COLOR_BGRA2BGR)
                # detect_one(model,img_path,device)
                dict_list = detect_Recognition_plate(detect_model, img, device, plate_rec_model, opt.img_size,
                                                     car_rec_model)
                # print(dict_list)
                ori_img = draw_result(img, dict_list)
                img_name = os.path.basename(img_path)
                save_img_path = os.path.join(save_path, img_name)
                time_e = time.time()
                time_gap = time_e - time_b
                if count:
                    time_all += time_gap
                cv2.imwrite(save_img_path, ori_img)
                count += 1

                conn = sqlite3.connect('ipms.db')
                cursor = conn.cursor()
                print(dict_list)
                car_color = ', '.join([item['car_color'] for item in dict_list if 'car_color' in item])
                plate_color = ', '.join([item['plate_color'] for item in dict_list if 'plate_color' in item])
                plate_no = ', '.join([item['plate_no'] for item in dict_list if 'plate_no' in item])
                plate_confidence = [item['score'] for item in dict_list if 'plate_no' in item]
                # 打印结果
                if plate_no:
                    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]
                    if (plate_color == '绿色') and (len(plate_no) == 8):
                        print("新能源绿牌汽车")
                        print(f"车牌号码: {plate_no}")
                        print(f"车牌置信度:{plate_confidence}")
                        # insert_data_when_enter(timestamp, plate_no, "新能源小汽车", car_color)
                    elif (plate_color == '蓝色') and (len(plate_no) == 7):
                        print("普通蓝牌汽车")
                        print(f"车牌号码: {plate_no}")
                        print(f"车牌置信度:{plate_confidence}")
                        # insert_data_when_enter(timestamp, plate_no, "普通汽车", car_color)
                    else:
                        pass
                        print("车牌不合法或不在考虑的范围")
                        print(f"车牌号码: {plate_no}")
                        print(f"车牌置信度:{plate_confidence}")
