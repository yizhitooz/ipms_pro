> [!NOTE] 
>
> 致读者：
>
> 本项目基于[开源项目](https://github.com/we0091234/Car_recognition)修改而来，主要在树莓派上部署该模型，连接两个摄像头进行车牌识别。使用的相应技术为`YOLOv5`检测模型，`CRNN`理解文本识别网络。
>
> 如有疑问可参照原项目或提出 issue 。

## 车辆识别系统

车辆检测（YOLOv5）+车牌检测识别（YOLOv5）

环境要求: Python >=3.6，PyTorch >=1.7

#### 图片测试demo

```bash
python Car_recognition.py --detect_model weights/detect.pt  --rec_model weights/plate_rec_color.pth --image_path imgs --output result
```

参数说明：测试文件夹`imgs`，结果保存在`result`文件夹中。

<img src="image/test.jpg" alt="Image text" style="zoom:50%;" />

## 车牌检测训练

1. **下载数据集：**  [datasets](https://pan.baidu.com/s/1YSURJvo4v1N5x7NVsxEA_Q) 提取码：3s0j     数据从CCPD和CRPD数据集中选取并转换的
   数据集格式为 YOLO 格式：

   ```
   label x y w h  pt1x pt1y pt2x pt2y pt3x pt3y pt4x pt4y
   ```

   关键点依次是（左上，右上，右下，左下）
   坐标都是经过归一化，x,y是中心点除以图片宽高，w,h是框的宽高除以图片宽高，ptx，pty是关键点坐标除以宽高

   车辆标注不需要关键点 关键点全部置为-1即可
2. **修改 `data/widerface.yaml`  文件里的` train`和`val`路径,换成你的数据路径**

   ```yaml
   train: /your/train/path #修改成你的路径
   val: /your/val/path     #修改成你的路径
   # number of classes
   nc: 3                #这里用的是3分类，0 单层车牌 1 双层车牌 2 车辆
   
   # class names
   names: [ 'single_plate','double_plate','Car'] 
   
   ```
3. **训练**

   ```bash
   python3 train.py --data data/plateAndCar.yaml --cfg models/yolov5n-0.5.yaml --weights weights/detect.pt --epoch 250
   ```

   结果存在`run`文件夹中。

## 车牌识别训练

车牌识别训练链接如下：

[车牌识别训练](https://github.com/we0091234/crnn_plate_recognition)

## 参考链接

* [https://github.com/we0091234/Chinese_license_plate_detection_recognition](https://github.com/we0091234/Chinese_license_plate_detection_recognition)
* [https://github.com/deepcam-cn/yolov5-face](https://github.com/deepcam-cn/yolov5-face)
* [https://github.com/meijieru/crnn.pytorch](https://github.com/meijieru/crnn.pytorch)
