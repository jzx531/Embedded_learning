# RK3568 等开发板：具身智能、语音与音视频工程项目推荐

检索与源码核对日期：2026-11-23。

本文补充此前的视觉检测项目调研，侧重“能够找到实际应用源码”的语音交互、机器人感知控制和音视频系统。排序依据是与你的 C/C++、Linux、STM32、通信接口和时间戳经验的匹配程度，以及在现有 RK3568 上完成一个可验证作品的可行性，不是按 Star 排名。

核实方式包括 GitHub 仓库元数据、递归文件树、README 和关键实现文件；Gitee 部分核实了仓库 API 和源码目录。本文没有在你的板子上编译、运行或测量这些项目。仓库作者的演示和性能数据不等于你已经复现的成果。

## 1. 先选方向：最值得你做的三个工程

| 优先级 | 作品方向 | 主要参考 | 为什么适合你 |
|---|---|---|---|
| 1 | RK3568 音视频采集、分析与流媒体网关 | `cccoddad/rk3568-edge-av-gateway` | 直接面向 RK3568，C++，有 V4L2/ALSA、NPU、MPP、音视频封装、队列与异常恢复，与你现有视觉路线衔接最好 |
| 2 | RK3568＋STM32 视觉跟随/巡检机器人 | OriginBot；`WayV5/RK3588-STM32-ROS2-SLAM-Robot` | 将 Linux 感知、ROS 2、串口/CAN 和 MCU 控制闭环连起来，更能体现嵌入式上下位机能力；需要额外底盘硬件 |
| 3 | 离线语音指令＋视觉确认的交互终端 | sherpa-onnx；小智 Linux；OpenVoiceStream | 先把语音采集、识别、命令执行和播报做成闭环，再接摄像头或执行器；RK3568 不必承担大模型对话 |

如果只选一个替换简历中的通用 Web 项目，建议先做第 1 个。如果明确投机器人嵌入式岗位，再选第 2 个。第 3 个适合暂时没有底盘、希望先做语音与多模态交互的人。

“具身智能”需要有感知、决策、动作和反馈。只有麦克风聊天与表情显示的设备属于语音交互终端；摄像头推流属于音视频系统。它们可以成为机器人子系统，但不能仅因接入大模型就写成完成了自主机器人。

## 2. 总览：源码范围、平台与许可证

这里的“应用源码齐全”指公开了应用的主要模块和构建入口；不代表传感器驱动、NPU Runtime、模型权重、机械结构与板卡 BSP 全都开源。

| 项目 | 实际公开范围 | 上游平台 | 当前 RK3568 的使用方式 | 许可/成熟度要点 |
|---|---|---|---|---|
| RK3568 Edge AV Gateway | C++ 采集、推理、叠加、编码、MP4/RTSP、配置、测试与部署工具 | RK3568 / Buildroot | 适配 Ubuntu 的构建依赖、设备和服务管理后验证 | MIT；作者提供实板与长稳记录，本次未独立复现 |
| 小智 Linux＋RK3568 适配 | 录放音、Opus、通信控制、LVGL 客户端 | 嵌入式 Linux；社区 RK3568 适配 | 重建 Ubuntu ARM64 依赖，调整声卡、显示与输入 | 已查核心源文件标注 GPL-3.0-only；按模块核对，不当作 MIT |
| sherpa-onnx | 语音引擎、C/C++ API、麦克风/识别/合成等示例 | ARM64 Linux 等；官方 RKNN 文档列出 RK3568 | 做离线语音子系统；机器人命令和控制流程需自己实现 | Apache-2.0；是组件与示例，不是完整机器人 |
| OpenVoiceStream | 语音服务、会话、应用插件、Web 演示和部署配置 | RK3588/RK3576、Jetson、树莓派 | 移植客户端或轻量后端；重型推理先放 PC | MIT；不同应用成熟度不同，陪伴机器人仍有 stub/迁移项 |
| OriginBot 三仓库 | 机器人 ROS 包、PC 模型/仿真、STM32 控制器源码与电气资料 | RDK X3 等配套环境 | 保留通用 ROS/串口控制，替换平台 AI 部分 | Apache-2.0；跨平台迁移工作真实存在 |
| RK3588＋STM32 SLAM Robot | ROS 2 C++ 节点、CAN、导航配置、NPU 推理、STM32 FreeRTOS 源码 | RK3588＋STM32F407，Ubuntu 22.04/Humble | 迁移应用与 MCU 协议，重新转换 RK3568 模型 | README 有 MIT 徽章，但文件树未见根 LICENSE，授权范围需确认 |
| ELF2 语音视觉抓取机器人 | Python 视觉、串口语音接入、底盘/舵机/任务状态机 | RK3588 与配套底盘机械臂 | 先学习闭环，再适配 IO、摄像头和推理后端 | MIT；现有视觉是 OpenCV DNN，不是 RKNN |
| Luckfox Pico RKNN Example | 摄像头 AI、显示、模型转换和构建示例 | Luckfox Pico / RV1106 系列 | 参考相机 AI 终端设计，不能直接用它的二进制 | 未见统一根 LICENSE；第三方目录有各自许可 |
| WVP-GB28181-pro | 视频平台 Java 后端、Vue 前端、设备管理/信令 | Linux/服务器＋ZLMediaKit | 优先部署在 PC，RK3568 作为采集/推流端 | MIT；README 同时列有闭源功能，需按功能区分 |
| ZLMediaKit＋FFmpeg Rockchip | 完整流媒体服务器、编解码/滤镜源码 | ARM/Linux；Rockchip BSP | 作为上述项目的媒体基础设施 | ZLM 是带附加保留标识要求的 MIT-like；FFmpeg 依构建配置确定许可 |
| EdgeArm | 语音服务集成、SO-101 任务接口、运行配置与回归检查 | RK3588＋RK1828＋SO-101 | 仅取架构参考，不是当前 RK3568 的直接部署目标 | MIT；上游明确列出尚未完成的实机与抓放验收 |

## 3. 工程例子一：RK3568 实时音视频边缘分析网关

源码：[cccoddad/rk3568-edge-av-gateway](https://github.com/cccoddad/rk3568-edge-av-gateway)

这是本轮最贴近你已有开发板、也最贴近 C++ 音视频岗位的应用工程。它把摄像头、麦克风、视觉推理、硬件编码和网络输出接在同一条管线中，并提供 Mock 后端，便于先在没有板卡外设时理解架构。

```text
USB 摄像头 → V4L2 → MJPEG 解码 → 检测/OSD → RGA/MPP → H.264 ─┐
USB 麦克风 → ALSA → PCM → AAC ────────────────────────────┤
                                                        ↓
                                             MP4 / RTSP → ZLMediaKit
```

已核对的实现入口：

- [V4L2 采集](https://github.com/cccoddad/rk3568-edge-av-gateway/blob/7e3a94acd7f18f591cd8466425344d005a2261a9/src/capture/v4l2/v4l2_video_capture.cpp)：实际使用 `ioctl`、`VIDIOC_*`，不是只有接口声明。
- [ALSA 采集](https://github.com/cccoddad/rk3568-edge-av-gateway/blob/7e3a94acd7f18f591cd8466425344d005a2261a9/src/capture/alsa/alsa_audio_capture.cpp)：这一实现直接使用 ALSA 内核 UAPI；可以与常见的 alsa-lib PCM API 对照学习。
- [MPP/RGA 编码](https://github.com/cccoddad/rk3568-edge-av-gateway/blob/7e3a94acd7f18f591cd8466425344d005a2261a9/src/media/mpp/mpp_rga_video_encoder.cpp)：RGB/BGR 到 NV12，再输出 H.264。
- [RTSP 输出](https://github.com/cccoddad/rk3568-edge-av-gateway/blob/7e3a94acd7f18f591cd8466425344d005a2261a9/src/output/ffmpeg/ffmpeg_rtsp_sink.cpp)：实际调用 libavformat，包含会话和重连处理。
- `src/app/application.cpp`、`src/output/packet_router.cpp`、`config/`：学习线程编排、输出路由与配置契约。
- [基准记录](https://github.com/cccoddad/rk3568-edge-av-gateway/blob/7e3a94acd7f18f591cd8466425344d005a2261a9/docs/BENCHMARKS.md)：学习如何记录测试条件、阶段耗时与运行证据。

**适配你的板子：** 上游使用 Buildroot、特定 RKNN/MPP/RGA 组合和 SysV 启动方式。你的 Ubuntu 环境需要重新处理库版本、声卡编号、摄像头格式、设备权限、链接路径和 systemd 服务。不能照搬其交叉编译 sysroot，也不应为了运行它更换当前可用的桌面图形库。

**建议你完成的扩展：** 增加音视频统一时钟说明、录制分段、磁盘容量策略、设备热拔插恢复和远程状态接口；把原有 HTTP 框架用作设备配置/指标 API。先复现单路，再比较 CPU 与硬件处理的收益。

作者声明的 120 小时长稳、测试数量和延迟属于上游结果。阅读这些记录可以学习验收方法，但你的简历应填写自己在 KICKPI 上得到的数据。特别要区分“编码入口丢帧”“推流写入失败”和“接收端实际丢包”，不能把其中一个指标替代另外两个。

## 4. 工程例子二：小智 Linux 语音终端，补齐自建后端

相关源码：

- [100askTeam/xiaozhi-linux](https://github.com/100askTeam/xiaozhi-linux)：嵌入式 Linux 客户端核心代码。
- [100askTeam/xiaozhi-linux-SupportList](https://github.com/100askTeam/xiaozhi-linux-SupportList)：单板适配资料入口；核心仓库说明它不包含所有 BSP 与依赖。
- [Yinyifeng18/xiaozhi-linux-rk3568](https://github.com/Yinyifeng18/xiaozhi-linux-rk3568)：明确面向 RK3568 的社区适配。
- [xinnan-tech/xiaozhi-esp32-server](https://github.com/xinnan-tech/xiaozhi-esp32-server)：独立开源的小智后端实现；提供 Python 服务及 Java/Vue 管理功能，根许可证 MIT。

**能做出的作品：** 带 DSI 触摸屏的语音交互终端，包含按键/触摸开始说话、语音上传、回复播放、文字与状态显示。后续可增加设备查询、摄像头截图和 MCU 指令工具。

RK3568 客户端已核对的代码：

- [sound_app/record.cpp](https://github.com/Yinyifeng18/xiaozhi-linux-rk3568/blob/e6fc25df65401d83f44837708c7b29316ce5d99d/sound_app/record.cpp)：ALSA 录音、采样率与通道配置。
- [sound_app/opus.cpp](https://github.com/Yinyifeng18/xiaozhi-linux-rk3568/blob/e6fc25df65401d83f44837708c7b29316ce5d99d/sound_app/opus.cpp)：Opus 编解码和 Speex 重采样。
- [control_center/websocket_client.cpp](https://github.com/Yinyifeng18/xiaozhi-linux-rk3568/blob/e6fc25df65401d83f44837708c7b29316ce5d99d/control_center/websocket_client.cpp)：WebSocket/TLS 与文本/二进制消息处理。
- `gui/lv_100ask_xz_ai/`：LVGL 的交互界面；`ipc_udp.*`：进程间数据传递。
- 后端入口已核对 `main/xiaozhi-server/app.py`，实际创建 HTTP/WebSocket 服务，并非只有展示页面。

**移植重点：** 社区 RK3568 Makefile 使用了特定厂商 Buildroot 工具链。当前 Ubuntu 上宜从源码重建依赖，先单独验证录音和播放，再接协议。DSI 屏 800×1280 的布局和输入设备也要适配。保留 XFCE 时，优先使用能与现有桌面共存的显示后端，不直接让旧版 framebuffer/输入程序接管正在使用的显示与触摸设备。

**“整套源码”的边界：** 客户端源码、后端源码可以分别获得，但两者不是本次已经验证兼容的一套发布包；需要核对协议版本、鉴权、激活流程、消息字段、Opus 采样率和帧时长。后端的 ASR/LLM/TTS 既可依赖外部 API，也可配置本地模型，不等于默认全部离线。建议先将服务端放 PC，RK3568 负责设备端音频与交互。

**许可：** 100ask 与社区 RK3568 仓库抽查的音频核心文件标注 `GPL-3.0-only`，且有版权说明；虽然根目录 LICENSE 信息不完整，也不能据此说“完全没有许可”或随意改按 MIT 使用。LVGL、Opus、Speex、后端和模型按各自条款核对。

## 5. 工程例子三：离线语音指令控制台，逐步接入机器人

源码：[k2-fsa/sherpa-onnx](https://github.com/k2-fsa/sherpa-onnx)

平台依据：[官方 RKNN 文档](https://k2-fsa.github.io/sherpa/onnx/rknn/index.html)明确列出 RK3568、RK3566、RK3562、RK3576 和 RK3588。源码中的 SenseVoice RKNN 导出脚本也列出 `rk3568` 目标。这比只看到“支持 ARM”更有依据，但仍需针对具体模型、驱动和 Runtime 验证。

这个仓库是语音组件与完整示例集合，**不是已经集成好电机、摄像头和任务系统的机器人产品**。推荐用它做下面这个小而完整的工程：

```text
麦克风 → VAD/分段 → ASR → 确定性指令解析 → 执行与反馈 → TTS
                                        ↓
                              截图 / 查询设备 / MCU 状态
```

建议读的源码：

- [麦克风识别 C++ 示例](https://github.com/k2-fsa/sherpa-onnx/blob/cdbcacf732271ca373c9f323cff3c6083ab50dbe/cxx-api-examples/sense-voice-simulate-streaming-microphone-cxx-api.cc)：PortAudio 设备、采样率和识别调用；该示例是模拟流式使用，不应当成模型天然支持任意流式解码的证明。
- [RKNN ARM64 构建脚本](https://github.com/k2-fsa/sherpa-onnx/blob/cdbcacf732271ca373c9f323cff3c6083ab50dbe/build-rknn-linux-aarch64.sh)：RKNN 头文件、Runtime 库和 CMake 开关。
- [SenseVoice 模型导出](https://github.com/k2-fsa/sherpa-onnx/blob/cdbcacf732271ca373c9f323cff3c6083ab50dbe/scripts/sense-voice/rknn/export-rknn.py)：目标平台和模型转换。
- `cxx-api-examples/matcha-tts-zh-cxx-api.cc`、`sherpa-onnx/csrc/keyword-spotter.*`：中文 TTS 与关键词能力的不同入口。

第一版只识别十几个固定命令，例如“拍照”“开始录制”“停止录制”“查询温度”。先用 WAV 验证识别正确性，再接实时麦克风。动作命令使用明确的命令表和参数校验，执行器返回完成/失败反馈后再播报结果。

CPU 上先选轻量模型做基线，再选官方支持转换的模型验证 NPU。不要把“库支持 RKNN”理解成所有 ASR、TTS、VAD 模型都能在 RK3568 NPU 上运行，也不要直接运行名称带 RK3588 的预编译模型。模型权重许可与 Apache-2.0 的代码许可分别检查。

## 6. 工程例子四：OpenVoiceStream 语音应用与交互机械臂

源码：[Seeed-Solution/openvoicestream](https://github.com/Seeed-Solution/openvoicestream)

它比单个语音引擎更接近应用系统：公开了语音服务、会话与插件框架、Web 演示、部署配置和多个应用。当前明确提供的 Rockchip 部署目标主要是 RK3588/RK3576；不能由此推导出 RK3568 整套即装即用。

可以拆成三个独立的学习例子：

| 应用 | 源码入口 | 可以学习的工程能力 | 核实后的边界 |
|---|---|---|---|
| 对话终端 | [conversation](https://github.com/Seeed-Solution/openvoicestream/tree/main/agent/ovs_agent/apps/conversation) | 流式 ASR/LLM/TTS、会话生命周期、打断和播放排空 | 应用 README 明确说明部署配置不等于所有组合已经完成应用级实测 |
| 实时字幕屏 | [live_caption/app.py](https://github.com/Seeed-Solution/openvoicestream/blob/main/agent/ovs_agent/apps/live_caption/app.py) | 部分结果与最终结果、字幕提交、WebSocket 广播 | `noop` 翻译后端只是原文透传，不能算已实现翻译 |
| 语音控制机械臂 | [voice_rebot_arm](https://github.com/Seeed-Solution/openvoicestream/tree/main/agent/ovs_agent/apps/voice_rebot_arm) | 唤醒、工具调用、执行器插件、视觉抓取接口和状态面板 | 需要 B601-DM、声学服务、LLM 与相机；部分部署示例面向 Jetson，不是通用 RK3568 固件 |

已读取 `live_caption/app.py` 和 `voice_rebot_arm/app.py` 的实现，存在应用类与插件注册。机械臂应用不等于全仓库每个机器人应用都完整：[companion_robot 的 README](https://github.com/Seeed-Solution/openvoicestream/blob/main/agent/ovs_agent/apps/companion_robot/README.md)明确列有 no-op stub、迁移计划和未包含的硬件控制部分。

**在你的板子上怎么用：** 先让 RK3568 做麦克风/扬声器、触摸屏与串口客户端，PC 跑推理服务；之后才考虑将轻量语音模型下沉。C++ 岗位作品应重点展示你实现的设备端音频、缓冲、取消和控制协议，而不只是运行 Python Web 服务。

代码根许可证 MIT；底层语音库、加速后端、驱动及模型另有依赖与许可。上游的多平台性能表不能作为 RK3568 的性能承诺。

## 7. 工程例子五：OriginBot 完整移动机器人三仓库

这一组适合学习“机器人主机＋MCU＋PC 调试端”的完整分工。要看三个仓库，而不是只下载机器人端软件包：

| 部分 | GitHub | 公开内容 |
|---|---|---|
| 机器人端 | [guyuehome/originbot](https://github.com/guyuehome/originbot) | 底盘驱动、传感器接入、导航与视觉应用包 |
| PC 端 | [guyuehome/originbot_desktop](https://github.com/guyuehome/originbot_desktop) | 机器人模型、RViz、Gazebo、示例与模型转换相关工具 |
| 控制器 | [guyuehome/originbot_controller](https://github.com/guyuehome/originbot_controller) | STM32 源工程、通信协议、电气原理图和预编译固件 |

三个仓库均识别到 Apache-2.0。控制器目录里既有 hex，也有真正的 `source/originbot_controller_project/` 工程，不能只拿“提供固件下载”当作公开了 MCU 源码。

建议沿着数据链阅读：

1. [originbot_base.cpp](https://github.com/guyuehome/originbot/blob/4270223147304832dede6f4336703388c672f103/originbot_base/src/originbot_base.cpp)：订阅 `cmd_vel`，串口通信，发布 odom/状态/IMU 等信息。
2. 控制器 `Source/APP/protocol.c`、`app_motion_control.c`、`pid.c`：下位机协议解析和运动控制。
3. `originbot_navigation/`：建图/导航的组织方式。
4. `originbot_deeplearning/body_tracking/`：人体跟随，把感知输出接到运动指令。
5. PC 仓库：TF、URDF、可视化和仿真，用于检查坐标与控制方向。

**移植边界：** 人体跟随文档使用 RDK X3/tros 环境，平台 BPU 推理和模型不适用于 RK3568。保留通用 ROS 消息、串口和底盘控制，把感知节点替换为 RKNN。PC 仓库还存在 Foxy/Gazebo 的旧环境说明，迁到 Jazzy 时需要调整 API、依赖与仿真版本。

**Gitee：** [机器人端](https://gitee.com/guyuehome/originbot)、[PC 端](https://gitee.com/guyuehome/originbot_desktop)、[控制器](https://gitee.com/guyuehome/originbot_controller)来自上游中文 README 的明确链接。本次机器人端入口返回 403，API 返回 404，未核实三个 Gitee 入口的当前完整性；实际源码判断以本次可读取的 GitHub 为依据，不声称镜像同步。

## 8. 工程例子六：RK3588＋STM32 FreeRTOS 自主导航机器人

源码：[WayV5/RK3588-STM32-ROS2-SLAM-Robot](https://github.com/WayV5/RK3588-STM32-ROS2-SLAM-Robot)

这份工程与你的 STM32、定时器、DMA、Linux 和 C++ 背景很匹配：上位机是 ROS 2 与视觉，下位机是 STM32F407＋FreeRTOS，通过 CAN 连接。导航使用 slam_toolbox/Nav2，包含模型、参数和启动文件。

已核对的真实实现：

- [can_interface.cpp](https://github.com/WayV5/RK3588-STM32-ROS2-SLAM-Robot/blob/aeb6303041bc14dd3b8c710d96979c0353058c47/app/src/robot_can_gateway/src/can_interface.cpp)：`PF_CAN`、`CAN_RAW`、绑定网口等 SocketCAN 操作。
- `app/src/robot_can_gateway/`：协议、运动学、ROS 节点与缓冲组织。
- [freertos.c](https://github.com/WayV5/RK3588-STM32-ROS2-SLAM-Robot/blob/aeb6303041bc14dd3b8c710d96979c0353058c47/stm32/prj/Core/Src/freertos.c)：电机控制、IMU、CAN 发送调度与命令处理任务。
- [can_protocol.c](https://github.com/WayV5/RK3588-STM32-ROS2-SLAM-Robot/blob/aeb6303041bc14dd3b8c710d96979c0353058c47/stm32/prj/Core/Src/can_protocol.c)：中断接收、环形队列、协议分发和急停状态。
- `app/src/robot_ai/`、`robot_bringup/`：NPU 检测、导航与传感器启动配置。

**迁到 RK3568 的顺序：** 先用仿真/离线数据理解 ROS 消息，再完成 RK3568 与 MCU 的通信和里程计，随后接相机和轻量检测，最后接导航。模型需要从原始模型按 RK3568 目标转换；仓库中的 `yolov8n_fp16_rk3588.rknn` 不应直接使用。还要核实 KICKPI 的 CAN 引出、收发器和驱动；没有可用 CAN 时，可另行设计串口或 USB-CAN 适配。

上游有 PREEMPT_RT 和 cyclictest 内容，但这不是开始项目的前置条件。你可以先让 MCU 承担电机控制闭环，Linux 做非硬实时任务；不要为了复现上游参数直接替换当前可用内核。

**授权注意：** README 的 MIT 徽章链接指向 LICENSE，但本次递归树未见根 LICENSE；第三方 RPLIDAR 和 SDK 目录的许可证不代表作者自有全部代码的许可。它可以作为公开源码学习材料，若要复制分发或商业复用，需要先确认相关代码授权。上游性能也未在你的板子复现。

## 9. 工程例子七：ELF2 语音目标输入＋视觉靠近＋机械臂抓取

源码：[wwwzhzh123/elf2-rk3588-voice-vision-robot](https://github.com/wwwzhzh123/elf2-rk3588-voice-vision-robot)

这个项目的优点是链路直观：输入物体名称，摄像头寻找目标，小车靠近并停止，机械臂执行夹取。主要业务代码集中在少量 Python 文件，适合先理解一套实际的任务状态机。

核心目录为 `elf2 rk3588 作品/`：

- [camera.py](https://github.com/wwwzhzh123/elf2-rk3588-voice-vision-robot/blob/9d29c4a178fee2ff5d5fc20a5cecaf8a44d3bf4f/elf2%20rk3588%20%E4%BD%9C%E5%93%81/camera.py)：相机、ONNX 检测、目标筛选、TCP 位置消息。
- `voice_listener.py`：读取外部语音模块串口，将结果转换为命令。
- `main.py`、`task.py`：控制主循环和搜索、靠近、停止、抓取状态机。
- `motor.py`、`servo.py`、`kinematics.py`、`encoder.py`：执行器与运动学相关代码。

**源码核对后的两个重要结论：** 视觉代码调用 `cv2.dnn.readNetFromONNX`，没有因此获得 RKNN NPU 加速；语音代码通过串口接收识别结果，并没有公开一个板端完整 ASR 模型实现。当前相机消息中的深度位置还使用固定的 `0` 字段，停车依据包含画面特征/阈值；不能按 README 的概括就宣称完成了精确 RGB-D 测距与三维抓取。

根许可证 MIT。仓库有主程序、模型和执行器业务源码，但配套语音模块内部固件、具体硬件驱动与标定仍需另外核对，README 提到的部分运行说明/启动文件也未在当前树中找到。

**适合你的改进：** 将视觉推理迁到 RKNN；把文本协议升级为带长度、序号、校验和超时的协议；增加目标丢失、相机断连、抓取失败的状态转换。先验证固定位置/固定物体的动作闭环，再引入距离估计和抓取坐标标定。仅完成状态机发出动作，不等于已经验证抓取成功。

## 10. 工程例子八：Luckfox Pico 摄像头 AI＋小屏显示

源码：[LuckfoxTECH/luckfox_pico_rknn_example](https://github.com/LuckfoxTECH/luckfox_pico_rknn_example)

这是“RK3568 等板子”中可补充学习的低成本相机终端案例。包含 YOLOv5 检测、RetinaFace/FaceNet、人脸比对、小屏显示、构建脚本和模型转换脚本。公开内容比只有一张推理截图的仓库更便于跟读。

源码入口：`example/luckfox_pico_yolov5/src/main.cc`、`example/luckfox_pico_retinaface_facenet/src/main.cc`、`build.sh`、`scripts/luckfox_onnx_to_rknn/`。README 链接到 RV1106 系列说明，并区分 glibc/uClibc 工具链与不同显示屏。

**与现有板子的关系：** 可借鉴相机采集、图像处理、模型部署和显示分层。RV1106 系列的 ARM32 工具链、摄像头媒体接口和模型，不能直接复制到 RK3568 ARM64 Ubuntu。迁移时保留算法流程，换成你的 V4L2/显示/RKNN 适配。

这不是完整音视频对讲设备，也不是完整机器人。未见统一根 LICENSE，不应以第三方目录中某个 MIT/BSD 文件推断整个应用授权。上游为释放摄像头而停止 `rkicp` 的步骤只针对其对应系统，不适用于直接照抄到你的 KICKPI。

## 11. 工程例子九：WVP＋ZLMediaKit，机器人/相机视频管理平台

GitHub：[648540858/wvp-GB28181-pro](https://github.com/648540858/wvp-GB28181-pro)

Gitee：[pan648540858/wvp-GB28181-pro](https://gitee.com/pan648540858/wvp-GB28181-pro)

这是本轮确认有 GitHub 和 Gitee 源码入口的完整应用平台。公开了 Java 后端、Vue 前端、GB28181 设备信令、设备管理、点播与录像相关业务，依赖 ZLMediaKit 提供媒体能力。

核对到 `pom.xml`、`src/main/java/com/genersoft/iot/vmp/VManageBootstrap.java`、`web/package.json`；Gitee API 也返回了真实 Java 源码树。当前 GitHub master 的构建配置使用 JDK 21，不应照搬较旧教程中的 JDK 版本。

**适合做什么：** 把移动机器人或巡检终端产生的视频接入可管理的平台，实现设备列表、在线状态、视频预览和事件回看。你可以让 RK3568 做采集、编码与推流，PC 运行 WVP、ZLM 和数据库，避免一开始就让约 4GB 内存的板子承担全部服务。

**需分清的方向：** WVP 是平台端软件，不是 RK3568 摄像头驱动。板子向 ZLM 推送 RTSP/RTMP、平台把已有流代理/转发到国标上级，与“板子实现完整 GB28181 SIP 设备端”是不同工作。若选择后者，还需实现或选择设备端注册、目录、INVITE、媒体封装与 RTP 发送代码。

根许可证 MIT，但 README 同时有闭源内容章节，包括部分 ONVIF、设备配置和国标新能力；还提到依赖 ZLM 闭源版本的存储能力。公开前后端源码不代表宣传清单中每项都能免费从当前仓库编译得到。本轮未验证 GitHub/Gitee 每个分支同步。

如果目标是嵌入式 C++，建议把它用作测试和展示后台；简历主线仍应是你在 RK3568 设备端实现的媒体与通信工程。

## 12. 媒体基础设施：ZLMediaKit＋FFmpeg Rockchip

### 12.1 ZLMediaKit：视频服务与远程机器人媒体网关

- GitHub：[ZLMediaKit/ZLMediaKit](https://github.com/ZLMediaKit/ZLMediaKit)
- Gitee：[xia-chu/ZLMediaKit](https://gitee.com/xia-chu/ZLMediaKit)
- 已核对服务入口 `server/main.cpp`；Gitee 也能读取源码树和子模块路径。

适合学习 C++ 网络服务、RTSP/RTMP/WebRTC、协议转换、事件回调、REST API 与录像。它是完整服务器工程，但不等于已实现摄像头采集、麦克风声学处理和板卡编码驱动。

最实用的组合是：RK3568 采集/编码 → ZLM → 浏览器预览；再独立加入机器人控制通道。媒体延迟和控制反馈分别测量，避免视频阻塞拖住执行器命令。

**许可核对结果：** 当前 LICENSE 在 MIT 文本后增加保留 ZLMediaKit 标识的要求，包括服务中的部分 `title`、`Server`、`User-Agent` 等字段；应按其完整 MIT-like 条款使用，不能只抄 README 徽章。README 另有闭源专业版，不能把专业版 AI/转码等特性一并当成开源功能。构建还应获取指定子模块，不是下载主仓库源码包就一定齐全。

### 12.2 FFmpeg Rockchip：硬件编解码与图像处理

源码：[nyanmisaka/ffmpeg-rockchip](https://github.com/nyanmisaka/ffmpeg-rockchip)

它是完整 FFmpeg 分支，接入 MPP 编解码和 RGA 滤镜，适合研究 `h264_rkmpp`、`hevc_rkmpp`、`scale_rkrga` 等媒体路径。README 明确说明典型平台是 RK3588，要求 Rockchip BSP/vendor kernel，并列出已测试的 5.10/6.1 内核系列与设备节点。

你的内核属于 6.1 并不自动满足全部条件。还要确认 MPP/RGA 驱动、用户态库、格式、内存分配方式和设备权限；RK3568 的编码规格与滤镜限制按其芯片能力验证，不能拿 README 的最高 8K 能力作为 RK3568 指标。

许可随 FFmpeg 编译选项与依赖变化；该分支 README 明确提到 MPP/RGA 对应 `--enable-version3` 的 LGPLv3 兼容方式，加入其他 GPL 组件后还需重新判断。硬件模块之间支持 DMA 共享，不等于你的 USB 输入、CPU 推理前后处理、叠字、封装与网络整条链路已经零拷贝。

## 13. 两个可以参考、但不能当成现成完整成品的项目

### 13.1 EdgeArm：本地语音＋SO-101 任务系统

源码：[Qin-tuo/EdgeArm](https://github.com/Qin-tuo/EdgeArm)，根许可证 MIT。

默认硬件是 RK3588 主板、PCIe RK1828 和 SO-101，分配 Qwen3-ASR、Qwen3-4B、Matcha/Vocos 等语音与对话功能。公开了 agent、服务、串口执行器任务接口、模型清单、配置和检查脚本。

值得学习的是模型清单、服务就绪状态、单一串口所有者、任务取消、观察数据时效和动作反馈的组织方式。它不是“LLM 输出一串电机参数”的简单拼接。

但 [README](https://github.com/Qin-tuo/EdgeArm/blob/f15348cdbc087b7e431911f6c8ff4b7e641295df/README.md) 和 [scope](https://github.com/Qin-tuo/EdgeArm/blob/f15348cdbc087b7e431911f6c8ff4b7e641295df/docs/scope.md)明确写出：完整录放音/语音链路、机械臂实机动作仍需验收；D435i、接触传感器、抓放规划和结果验证仍有待实现/接入部分。RK1828 的稳定性也有未解决记录。

因此把它列作架构研究材料，不列为已经完成实机抓放的成熟系统；也不建议为在当前 RK3568 上复现它先购买整套加速卡和机械臂。

### 13.2 FishBot：仿真、运动控制和许可要分仓库看

- [GitHub fishros/fishbot](https://github.com/fishros/fishbot)：本次查看的是 humble 分支，README 明确说明该分支主要是仿真代码。
- [Gitee fishros/fishbot](https://gitee.com/fishros/fishbot)：本次确认 master 有 URDF、Gazebo 与 RViz 相关文件，不能把它直接当成完整实机固件。
- [fishbot_motion_control_microros](https://github.com/fishros/fishbot_motion_control_microros)：另一个运动控制固件仓库，已核对 PlatformIO、ESP32 与 micro-ROS 配置、源程序入口。
- [fishbot-motion-control](https://github.com/fishros/fishbot-motion-control)：硬件/驱动相关仓库；与前一个仓库不是同一份许可或同一版本。

当前 micro-ROS 固件 LICENSE 是明确的**非商业许可**，不能笼统称为 MIT 或 Apache 的自由商用项目；另一硬件/驱动仓库读取到 GPLv2 文本。它们适合按各自许可做学习和仿真实验，但不能由于都叫 FishBot 就混用分支、固件、接线和授权结论。

## 14. 现有 KICKPI 上的落地顺序

依据本会话此前的板卡记录：KICKPI K1Mini / RK3568、ARM64、约 4GB RAM、约 32GB eMMC，Ubuntu 24.04，厂商 6.1 内核，DSI 800×1280，当前本地使用 XFCE 并保留 GNOME。这里没有重新 SSH 核验；项目启动前应再次确认系统、外设和剩余资源。

### 14.1 先做与显示系统无关的能力检查

以下命令是启动项目时的只读检查示例，本轮未在板端执行：

```bash
uname -a
cat /etc/os-release
free -h
df -h
ls -l /dev/video* /dev/snd /dev/dri /dev/rga /dev/mpp_service /dev/dma_heap
arecord -l
aplay -l
v4l2-ctl --list-devices
```

`arecord`、`aplay`、`v4l2-ctl` 依赖对应工具已安装。设备节点不存在本身就是检查结果；存在也不代表驱动和 Runtime 已匹配。NPU 版本检查还需结合实际驱动日志、Runtime 查询结果和厂商 SDK，不能只根据某个通用设备路径判断。

音频优先使用已有可工作的声卡或 USB 声卡；视频先用 UVC 摄像头或固定文件。CSI/DSI 的连接器相似不代表驱动、供电和模组可直接通用。当前桌面已经经历过图形兼容性调整，项目依赖尽量放独立目录/虚拟环境，避免覆盖系统图形库、DTB 和内核。

### 14.2 ROS 版本要与系统一致

Ubuntu 24.04 优先评估 ROS 2 Jazzy；Ubuntu 22.04 对应 Humble。上游 Humble/Foxy/tros 的安装步骤不能原封不动放到当前系统。迁移可能涉及消息、导航参数、依赖和 Gazebo 版本。

RViz、Gazebo、模型训练与大部分转换工具先放 PC；RK3568 跑采集、轻量推理、状态机和通信节点。容器也依赖宿主内核功能及硬件设备映射，并不能自动解决 BSP/驱动问题。

### 14.3 分阶段交付

| 阶段 | 音视频路线 | 语音/机器人路线 | 完成判据 |
|---|---|---|---|
| A：无外设基线 | Mock/固定文件，单路录制与播放 | WAV 识别，模拟命令与反馈 | 输入固定、配置记录、退出正确、日志能定位失败 |
| B：真实采集 | UVC＋声卡，格式与时间戳核对 | 实时麦克风、按键说话、识别与播报 | 采集持续可用，设备断连有明确处理 |
| C：板卡加速 | MPP/RGA/RKNN 逐个替换并对照 | 轻量语音/视觉模型，MCU 通信 | 结果与 CPU 基线一致性可解释，队列有界 |
| D：应用闭环 | RTSP/浏览器、事件/录像回看 | 跟随/定点动作、超时、取消、反馈 | 不仅“发出命令”，还能判断任务完成或失败 |
| E：工程验收 | 断网重连、磁盘满、音视频漂移 | 误识别、目标丢失、MCU 断连 | 有可复现故障记录和自己的稳定性数据 |

## 15. 学习重点与作品证据

| 方向 | 应自己掌握的实现 | 建议记录的证据 |
|---|---|---|
| 音频 | 采样格式、声道、重采样、PCM 队列、欠载/溢出、播放取消 | 采集丢块、缓冲时长、ASR RTF、CER/WER、首包/首个可听声音时间 |
| 视频 | V4L2 buffer 生命周期、像素格式、stride、编解码、封装 | 分阶段耗时、端到端延迟、丢帧、CPU/RSS/温度、录像可播放性 |
| 同步 | PTS/DTS、时基换算、单调时钟、音视频漂移 | 持续录制后的声画偏差及其变化，统一测量定义 |
| 机器人 | TF/里程计、串口/CAN、MCU 控制、任务状态机与反馈 | 控制周期抖动、命令到反馈延迟、目标丢失后的行为、超时与重连记录 |
| 系统 | 有界队列、背压、资源所有权、配置、退出与恢复 | 固定版本配置、故障注入日志、进程/FD/RSS 趋势、可复现运行脚本 |

音频的“服务首个字节返回”和“扬声器已经发声”是两个时间点；视频编码完成时间和浏览器看到画面的时间也不同。跨设备测量需要时钟同步或外部观测方法，不能直接相减未同步的系统时间。

全双工对话需要考虑扬声器回声、输入输出延迟和打断；降噪、VAD 不等于已经实现 AEC。第一版采用按键说话与轮流录放，更容易把问题分清。

涉及底盘和机械臂时，先接模拟执行器或无负载测试，确认命令超时、取消和 MCU 停止机制，再验证真实运动。这些是控制链路的功能验收，不应仅用上层 HTTP 返回成功代替。

你已有的 STM32 定时/DMA 和 FPGA/共享缓冲经验可以迁移到周期测量、协议、帧生命周期、队列和时间戳分析。简历中最有说服力的内容是“你改了哪个模块、解决了什么故障、如何测量”，而不是把上述仓库的能力清单整体复制为个人成果。

## 16. 本次核对版本与检索边界

固定提交可帮助日后对照源码；下列 SHA 仅代表本次读取的快照，不保证未来默认分支不变化。

| 仓库 | 本次读取的提交或分支 |
|---|---|
| cccoddad/rk3568-edge-av-gateway | `7e3a94acd7f18f591cd8466425344d005a2261a9` |
| Yinyifeng18/xiaozhi-linux-rk3568 | `e6fc25df65401d83f44837708c7b29316ce5d99d` |
| k2-fsa/sherpa-onnx | `cdbcacf732271ca373c9f323cff3c6083ab50dbe` |
| guyuehome/originbot | `4270223147304832dede6f4336703388c672f103` |
| guyuehome/originbot_controller | `33660926c7143b9619761985122ccab00bf841e3` |
| guyuehome/originbot_desktop | `5858baf9def498f4c34712de87434bb6ad507f2d` |
| WayV5/RK3588-STM32-ROS2-SLAM-Robot | `aeb6303041bc14dd3b8c710d96979c0353058c47` |
| wwwzhzh123/elf2-rk3588-voice-vision-robot | `9d29c4a178fee2ff5d5fc20a5cecaf8a44d3bf4f` |
| LuckfoxTECH/luckfox_pico_rknn_example | `16ef54a2ad56211287d6064d5a5cd52570f50746` |
| ZLMediaKit/ZLMediaKit | `117ab934d48e256689318484bbf7f24e103ed25e` |
| nyanmisaka/ffmpeg-rockchip | `9f4b3ed30399f2fb84579c4597482940638e0442` |
| Qin-tuo/EdgeArm | `f15348cdbc087b7e431911f6c8ff4b7e641295df` |
| fishros/fishbot | GitHub humble：`3e486537c2ce9c3d1359bb304c3c103463a6a98e`；Gitee 另查 master |
| 100askTeam/xiaozhi-linux | master 的 README 与音频/控制源文件快照，未锁定提交 |
| xinnan-tech/xiaozhi-esp32-server | main 的 README、LICENSE、服务入口快照，未锁定提交 |
| Seeed-Solution/openvoicestream | main 的 README、LICENSE 与相关应用源码快照，未锁定提交 |
| 648540858/wvp-GB28181-pro | master 的 README、LICENSE、Maven/前端配置与 Java 入口；Gitee 另查 master |
| fishros/fishbot_motion_control_microros | master 的 README、LICENSE、PlatformIO 与程序入口，未锁定提交 |
| fishros/fishbot-motion-control | main 的 LICENSE 文本；未完成全树核对，仅作配套资料入口 |

研究缓存位于工作区 `work/embodied-av-research/`；本次抽查的源文件缓存复用了 `work/completed-vision-projects/source/`。后半程 GitHub API 出现未认证速率限制，部分补充项目通过原始文件读取；这些项目没有冒充已完成全树审计或构建验收。Gitee 的目录可读取不代表已核对每个文件、所有子模块或与 GitHub 的逐提交一致性。

本文与此前视觉告警路线可以组合，但建议先选一条主线完成自己的板端证据，再增加语音或底盘。对现有 RK3568，最稳妥的起点是“单路音视频网关”，接着做“语音操作设备”，最后扩展到“感知—动作—反馈”的机器人闭环。
