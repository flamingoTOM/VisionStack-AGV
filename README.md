# VisionStack AGV：立体仓库式码垛智能车

![Robot Demo](pic/640p.gif)

**基于视觉的自主决策、路径规划、取放工件的 AGV 小车**

> 2024 中国机器人大赛暨 RoboCup 机器人世界杯中国赛

## 项目简介

本项目开发了一款**立体仓库式码垛智能车（AGV）**，能够实现：

- 自主导航与路径规划
- 视觉识别（颜色检测、二维码识别、立体仓库定位）
- 精准的机械臂控制与工件抓取放置
- 基于陀螺仪和光电传感器的闭环定位系统

### 竞赛任务流程

```
起点 → 阶梯平台(抓取彩球) → 圆盘机(放置球) → 立体仓库(码垛) → 接替平台 → 回家
```

## 技术架构

### 硬件平台

| 组件 | 型号/规格 |
|------|-----------|
| 主控制器 | Arduino Mega 2560 (ATmega2560) |
| 底盘电机 | 4x 42闭环步进电机 |
| 托盘电机 | 1x 42闭环步进电机 |
| 机械臂 | 6自由度机械臂 (Lobot伺服控制器) |
| 陀螺仪 | HWT101 |
| 超声传感器 | HC-SR04 x2 |
| IC卡读卡器 | MFRC522 |
| 二维码扫描 | GM65 |
| 显示 | OLED (SSD1306) |
| 视觉 | 树莓派 (OpenCV) |

### 软件架构（mega2560）

```
mega2560/src/
├── main.cpp         # 主程序入口
├── work.cpp         # 任务流程控制 (JTPY/YPJ/LTCK)
├── motor.cpp        # 底盘运动学控制与PID算法
├── arm.cpp          # 机械臂动作控制
├── JY901.cpp        # 陀螺仪数据解析
├── HC_SR04.cpp      # 超声波测距
├── ICCard.cpp       # IC卡读写
├── white_detect.cpp # 白线巡线检测
├── GM65.cpp         # 二维码扫描
└── oled.cpp         # OLED显示
```

### 核心算法

- **运动学解算**：阿克曼转向模型实现直行、侧移、原地转向
- **PID闭环控制**：
  - 陀螺仪 yaw 角 PID 校准
  - 超声测距 PID 跟随
  - 轮式里程计融合定位
- **任务决策算法**：阶梯平台→圆盘机→立体仓库的顺序执行
- **视觉通信协议**：与树莓派串口通信实现颜色/二维码识别

## 快速开始

### 开发环境

- [PlatformIO IDE](https://platformio.org/) (推荐)
- Arduino IDE 1.8+

### 编译与烧录

```bash
cd mega2560
pio run -t upload
```

### 硬件连接

详见 `mega2560/include/config.h` 中的引脚定义。

## 项目结构

```
VisionStack-AGV/
├── README.md              # 本文件
├── pic/
│   └── 640p.gif           # 演示视频
├── mega2560/              # Arduino Mega 2560 下位机代码
│   ├── src/              # 源代码
│   ├── include/          # 头文件
│   └── platformio.ini    # PlatformIO 配置
└── mt/                   # 舵机控制板资料(不参与学习)
```

## 关键代码说明

### 底盘控制 (motor.cpp)

实现了多种运动模式：

```cpp
// 直行/后退
mt.Stepmotor_Closed_Control(FORWARD, 9500);
mt.Stepmotor_Closed_Control(BACKWARD, 6000);

// 原地侧移
mt.Stepmotor_Closed_Control(MOVE_LEFT, 3100);
mt.Stepmotor_Closed_Control(MOVE_RIGHT, 3500);

// 陀螺仪PID校准
mt.adjust_yaw_pid(x_yaw);
```

### 超声测距PID跟随

```cpp
// 基于PID的超声距离控制
Ultrasound_ms_1(3000, 4);  // 3秒内保持距墙4cm
```

### 机械臂控制 (arm.cpp)

使用动作组预定义动作：

```cpp
Arm.jtpy_catch_1();   // 阶梯平台抓取
Arm.ypj_hold();       // 圆盘机持球
Arm.ck_1_put_3();     // 仓库第三层放置
```

### 视觉通信协议

```cpp
Serial2.print('4');   // 启动视觉颜色检测
Serial2.print('5');   // 立体仓库定位
// 通过 Serial2.readStringUntil('\n') 获取结果
```

## 比赛成绩

本项目参加 **2024 中国机器人大赛暨 RoboCup 机器人世界杯中国赛**，完成了全部任务流程。

## License

MIT License

## 致谢

- 感谢队友们的通力合作
- 感谢指导老师的悉心指导
