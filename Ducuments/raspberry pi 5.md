# 树莓派 5 

## GPIO 与 40 针引脚指引

树莓派的一个显著特点是其顶部边缘的一排**通用输入/输出（GPIO）引脚**。目前市面上所有的树莓派型号都配备了一个40针的GPIO接口。值得注意的是，在树莓派Zero系列（包括树莓派Zero、树莓派Zero W和树莓派Zero 2 W）中，这些引脚是未焊接状态。所有型号的GPIO接口针脚间距均为标准的0.1英寸（2.54毫米）。

在软件层面，您可以自由地将任何一个GPIO引脚设置为输入或输出模式，以适应多样化的应用需求。这意味着您可以根据项目的具体需求，编程控制GPIO引脚来接收（作为输入）或发送（作为输出）信号，实现对各种电子元件的精确交互与控制。这一功能为树莓派提供了巨大的灵活性和扩展性，使其成为电子和编程爱好者的理想选择。

<img src="./Raspberry Pi 5.assets/GPIO-Pinout-Diagram-2-1713256251462-5-1713256507588-9.png" alt="GPIO pins" style="zoom: 50%;" />

<img src="./Raspberry Pi 5.assets/GPIO-1713256251462-6-1713256507588-10.png" alt="GPIO layout" style="zoom: 67%;" />

### 电压

树莓派主板上有两个5V引脚和两个3.3V引脚，以及多个接地引脚（GND），这些引脚不能重新配置。其余的引脚都是通用的3.3V引脚，这意味着输出设置为3.3V，输入为3.3V容忍。

### 输出

作为输出引脚的GPIO引脚可以设置为高（3.3V）或低（0V）。

### 输入

 作为输入引脚的GPIO引脚可以读取为高（3.3V）或低（0V）。使用内部上拉或下拉电阻可以简化这一过程。GPIO2和GPIO3引脚有固定的上拉电阻，但其他引脚可以在软件中配置。

### 其他功能

除了简单的输入和输出设备外，GPIO引脚还可以用于多种替代功能，有些功能适用于所有引脚，有些则仅适用于特定引脚。

#### PWM（脉冲宽度调制）：

- 所有引脚都可用的软件PWM
- GPIO12、GPIO13、GPIO18、GPIO19上可用的硬件PWM

#### SPI（串行外设接口）：

- SPI0：MOSI（GPIO10）；MISO（GPIO9）；SCLK（GPIO11）；CE0（GPIO8），CE1（GPIO7）
- SPI1：MOSI（GPIO20）；MISO（GPIO19）；SCLK（GPIO21）；CE0（GPIO18）；CE1（GPIO17）；CE2（GPIO16）

#### I2C（集成电路总线）：

- 数据：（GPIO2）；时钟（GPIO3）
- EEPROM数据：（GPIO0）；EEPROM时钟（GPIO1）

#### 串行通信：

- 发送（TX）（GPIO14）；接收（RX）（GPIO15）

#### GPIO Zero 模块

##### 距离传感器

<img src="./Raspberry Pi 5.assets/image-20240416164831659.png" alt="image-20240416164831659" style="zoom:50%;" />

* 检测物体距离

```python
from gpiozero import DistanceSensor
from time import sleep

sensor = DistanceSensor(23, 24)

while True:
    print('Distance to nearest object is', sensor.distance, 'm')
    sleep(1)
```

* 当有东西靠近传感器

```python
from gpiozero import DistanceSensor, LED
from signal import pause

sensor = DistanceSensor(23, 24, max_distance=1, threshold_distance=0.2)
led = LED(16)

sensor.when_in_range = led.on
sensor.when_out_of_range = led.off

pause()
```

## 摄像头

### IMX219

#### 安装

<img src="./Raspberry Pi 5.assets/image-20240416165640018.png" alt="image-20240416165640018" style="zoom: 67%;" />

#### 配置

修改`/boot/firmware/config.txt`配置文件

1. 打开树莓派终端，输入以下指令；

   ```bash
   sudo nano /boot/firmware/config.txt
   ```

2. 在结尾加上`dtoverlay=imx219`。

<img src="./Raspberry Pi 5.assets/image-20240416171022805.png" alt="image-20240416171022805" style="zoom: 80%;" />

#### 测试与编程

* 命令行驱动

  ```bash
  libcamera-hello # 打开一个窗口短暂展示摄像头捕获到的画面，相当于 Hello，world！
  ```

* Python 编程驱动

  ```Python
  # 导入模块
  from picamera2 import Picamera2, Preview
  import time
  
  # 初始化
  picam2 = Picamera2()  
  camera_config = picam2.create_preview_configuration() 
  picam2.configure(camera_config) 
  picam2.start_preview(Preview.QTGL) 
  picam2.start() 
  
  time.sleep(2) 
  
  # 摄像头捕获画面
  picam2.capture_file("test.jpg") 
  ```

  
