# RK3568 等 ARM 开发板开源项目推荐：按面试展示价值排序

调研日期：**2026-11-22，Asia/Shanghai**。面向你当前的 **KICKPI K1Mini / RK3568 / 约 4 GB RAM / Ubuntu 24.04.4 / Linux 6.1.141**，并兼顾 RK3566、RK3588、树莓派和其他 ARM Linux 板。来源包括实际读取的 GitHub 仓库 README、Gitee 项目资料和公开岗位正文；资料快照保存在 [调研目录](work/rk3568-project-research/)。

**最推荐的三条路线：边缘 AI 视觉设备、工业协议网关、BSP/驱动与系统构建。选一条做深，再补上可靠性、自动部署和测量报告，比同时部署十几个现成服务更适合写进简历。**

## 1. “面试官青睐程度”的定义与依据

这里给的是面向**嵌入式 Linux / BSP / C/C++ / 边缘 AI 求职**的推荐顺序，不是面试官问卷、录用概率或全国招聘市场统计，也不按 GitHub Star 数排序。默认你希望通过自己的代码和实测展示能力，而非只展示安装结果。

排序主要看五件事：

1. **岗位关联：** 能否对应 C/C++、Linux、驱动、协议、并发、性能和可靠性等实际工作。
2. **个人贡献：** 除了编译运行，上游之外由你实现了什么，能否通过提交记录清楚区分。
3. **可追问深度：** 是否能解释数据流、线程、内存、故障处理、软硬件边界和取舍。
4. **结果可验证：** 是否有可复现实验、原始日志、对照基线和正确性检查。
5. **当前板卡可完成性：** 现有系统能否起步，是否需要额外传感器、驱动、底盘或重做系统镜像。

可核查的岗位依据如下。检索时官方招聘接口仍返回这些条目，但职位状态可能变化；接口的 `updated_at` 是更新时间，不能当作首次发布日期。

| 公开岗位 | 实际读到的能力要求 | 对选项目的影响 |
|---|---|---|
| [Canonical：Junior Linux Kernel Engineer - Ubuntu](https://job-boards.greenhouse.io/canonical/jobs/5370815) | C/Rust、Git、操作系统原理；内核问题诊断、测试自动化、补丁提交；驱动/BSP 为加分项 | BSP/驱动项目要交付补丁和回归结果，不能只截图“编译成功” |
| [Canonical：Ubuntu Linux Kernel Engineer - Silicon Enablement](https://job-boards.greenhouse.io/canonical/jobs/6076909) | C、驱动、BSP、内核原理、平台适配、调试和性能优化 | 板级适配、真实外设驱动、系统性能定位有直接关联 |
| [Canonical：Embedded Linux Field Engineer (Mandarin speaking)](https://job-boards.greenhouse.io/canonical/jobs/6994398) | Linux/Ubuntu、打包、Yocto/Buildroot、C/C++/Python 等语言、系统调试和交付 | 完整设备项目应包含系统服务、打包、升级和维护 |

上述是**同一公司的少量公开岗位样本**，可支撑能力映射，不代表中国企业的项目偏好分布。边缘 AI、工业控制、机器人等方向的具体排序属于下文的工程判断，未冒充对应行业的招聘统计。岗位正文快照见 [canonical-jobs.json](work/rk3568-project-research/canonical-jobs.json)。

## 2. 总体推荐排序

“适配 A”表示核心上游明确列出 RK3568；“适配 B”表示通用 Linux/ARM 项目，仍需编译和依赖适配；“适配 C”表示还需要板级移植、其他硬件或独立系统环境。它们都不等于已在你的 K1Mini 上完成实测。

| 排名 | 建议做成的项目 | 面试价值判断 | 主要开源基础 | 适配与额外条件 |
|---:|---|---|---|---|
| 1 | **RK3568 边缘视觉检测与告警设备** | 很高：C++、并发、NPU、视频链路、性能与正确性 | RKNN Model Zoo、MPP、librga、ZLMediaKit | A；先用视频文件，后加 USB 摄像头或 RTSP 摄像头 |
| 2 | **工业协议网关：Modbus → MQTT + 断网续传** | 很高：协议、状态机、持久化、异常恢复；落地门槛适中 | libmodbus、Mosquitto | B；TCP 模拟可起步，真实 RTU 增加 USB-RS485 |
| 3 | **BSP/设备驱动 + Buildroot 可复现系统** | 很高；投驱动/BSP 岗时应排第一 | Rockchip Linux、Buildroot、U-Boot | C；需要匹配板厂源码、串口和可恢复启动介质 |
| 4 | **带签名、回退与健康检查的设备 OTA** | 高：系统交付、启动链、故障设计 | RAUC、U-Boot、Buildroot | C；先做应用升级，系统 A/B 要独立测试镜像 |
| 5 | **低延迟视频网关 / 小型 NVR** | 高：网络、音视频、资源管理、长稳运行 | ZLMediaKit、MPP | A+B；RTSP 源、文件源即可起步 |
| 6 | **EtherCAT 数据采集与周期任务测量平台** | 工控/实时岗很高；通用岗位适用面较窄 | SOEM | B+C；需要合适网口和真实 EtherCAT 从站 |
| 7 | **工业 HMI：触控界面 + 实时采集 + 告警** | 中高：界面与后端分离、设备管理、故障可视化 | LVGL、libmodbus | B；先在桌面窗口运行，触摸屏再适配 |
| 8 | **RK3568 + STM32/RT-Thread 协同控制终端** | 中高：Linux 与 MCU 两端联调、通信协议和实时边界 | RT-Thread、libmodbus/MQTT 组件 | B+C；增加 STM32 等 MCU 板 |
| 9 | **ROS 2 / Nav2 自主导航小车** | 机器人岗高，通用嵌入式岗中高 | Navigation2 | B+C；底盘、里程计、雷达等成本和工作量较高 |
| 10 | **Linux 语音交互终端** | 中等；音频链路做深可提高 | xiaozhi-linux-rk3568 | A（社区项目）；麦克风、扬声器、外部服务 |
| 11 | **OpenWrt 网络网关与可观测性插件** | 中等；网络/路由岗可提高 | OpenWrt | C；核对具体板型、网口和无线驱动 |
| 12 | **Home Assistant 本地设备接入网关** | 基础部署较低；自研集成后中等 | Home Assistant Core、Mosquitto | B；核对容器/运行时版本和设备接口 |
| 13 | **NAS / 家庭备份与存储监控系统** | 只部署较低；做存储可靠性后中等 | OpenMediaVault | C；独立 Debian 环境、外接盘及稳定供电 |

这些是**基于开源组件进行二次开发的作品方向**，不是十三个“一键下载即完成”的完整 K1Mini 固件。第 1 与第 5 有技术重叠；第 4 适合作为第 2 或第 3 的升级模块，不必全做成独立简历项目。

## 3. 第 1 名：边缘 AI 视觉检测与告警设备

**适合岗位：** 嵌入式 C/C++、边缘 AI 部署、安防、工业视觉、音视频。

**核实的上游：**

- [airockchip/rknn-toolkit2](https://github.com/airockchip/rknn-toolkit2)：README 明确列出 RK3566/RK3568；区分 PC 端模型转换、板端 Lite2 / Runtime 和内核驱动。
- [airockchip/rknn_model_zoo](https://github.com/airockchip/rknn_model_zoo)：明确支持 RK3568，提供模型转换与 Python/C API 推理示例。
- [rockchip-linux/mpp](https://github.com/rockchip-linux/mpp)：README 明确包含 RK3566/RK3568 的媒体处理支持。
- [airockchip/librga](https://github.com/airockchip/librga)：明确列出 RK3568 和 Linux aarch64 库，提供图像处理接口。
- [ZLMediaKit/ZLMediaKit](https://github.com/ZLMediaKit/ZLMediaKit)：C++ 流媒体框架，README 描述 RTSP、RTMP、WebRTC、协议转换、C API 和 ARM 支持。
- [Qengineering/YoloV8-NPU](https://github.com/Qengineering/YoloV8-NPU)：面向 RK3566/68/88 的社区示例，适合辅助理解；当前快照最后推送为 2024-06-19，优先参考官方 SDK 的版本匹配要求。

**建议作品：** 摄像头/RTSP 输入，识别人或指定物体，实现区域入侵、停留时间或越线计数，提供事件列表、告警截图、网页预览及状态接口。第一版先用固定视频，减少摄像头适配对算法链路的干扰。

建议的数据流：

```text
文件 / 摄像头 / RTSP
  → 解码（先正确，后接 MPP）
  → 缩放与色彩转换（先 CPU，后比较 RGA）
  → RKNN 推理 → 后处理 / 规则状态机
  → 事件与截图存储 + 网页/流媒体输出
```

**你应自己实现：** C++ 帧队列、有界缓存与丢帧策略；时间戳贯穿；线程退出与错误恢复；规则引擎；配置热加载；资源监控。DMA-BUF、共享缓冲区等优化应在驱动与 API 支持、正确性验证之后进行，不应提前宣称“全链路零拷贝”。

**完成证据：** 固定视频、模型、输入尺寸、SDK/驱动版本；逐阶段耗时及端到端 P50/P95；CPU/RSS/温度/丢帧；CPU 与 NPU 或不同预处理方案的公平对照；标注数据上的精度结果；断流重连与长稳记录。全部是待测指标，本文没有给出已达到的 FPS 或延迟。

**面试追问：** 为什么单次推理快但端到端慢？如何避免队列越积越长？INT8 精度下降怎么定位？NV12/RGB 转换和 stride 出错会怎样？Runtime 与内核 NPU 驱动如何匹配？

**RK3568 边界：** 不照搬 RK3588 的模型吞吐、多核 NPU 设置和性能数字。Toolkit2 的模型转换建议放在它支持的 PC 环境，Windows 可考虑匹配版本的 WSL/Linux；板端运行 Runtime。Ubuntu 24.04 默认 Python 版本是否有对应 wheel 要逐版本确认，不能只看 SoC 支持表。

## 4. 第 2 名：工业协议网关与断网续传

**适合岗位：** 工业物联网、嵌入式 Linux 应用、协议网关、C/C++ 系统软件。

**上游：** [stephane/libmodbus](https://github.com/stephane/libmodbus) 提供串口与以太网 Modbus 通信，README 明确列出 Linux 支持；[eclipse-mosquitto/mosquitto](https://github.com/eclipse-mosquitto/mosquitto) 提供 MQTT broker 和客户端库。注意 libmodbus 的正确仓库是 `stephane/libmodbus`，不是根据项目名猜出的同名组织仓库。

**建议作品：** 多台设备轮询采集 → 数据标准化 → MQTT 上报 → 本地落盘；断网期间继续采集，恢复后补传；可配置寄存器映射、单位、采样周期和告警阈值。

第一步可以只用 Modbus TCP 服务模拟器，完全不需要购买 PLC；第二步接 USB-RS485 和真实从站。不要把板上的 TTL UART 直接当作 RS485 接口。

**你应自己实现：** 设备配置模型、独立超时与重试、连接状态机、离线队列、SQLite 等本地存储、消息编号和业务去重、配置校验、systemd 服务、故障注入脚本。MQTT QoS 不等于业务全链路“绝不重复”，应说明端到端语义。

**完成证据：** 串口/TCP 抓包、协议异常测试、断网与 broker 重启测试、补传前后数据总量和唯一性对账、采集抖动分布、持续运行的内存曲线。记录设备数、寄存器数和实际采样周期。

**面试追问：** RS485 半双工方向如何控制？超时设备是否拖慢全部设备？寄存器大小端如何配置？断电时队列是否损坏？如何处理重复消息、磁盘写满和时间回拨？

**推荐理由：** 相比只跑一个检测 demo，这条路线更容易形成“功能、可靠性、部署、测试”的完整证据链；缺少摄像头和 NPU 环境时，可以优先于第 1 名开始。

## 5. 第 3 名：BSP/驱动与可复现系统构建

**适合岗位：** Linux 驱动、BSP、系统移植、平台软件。投这类岗位时将它排第一。

**上游：** [rockchip-linux/kernel](https://github.com/rockchip-linux/kernel)、[buildroot/buildroot](https://github.com/buildroot/buildroot)、[u-boot/u-boot](https://github.com/u-boot/u-boot)。U-Boot README 还给出其 [官方代码托管入口](https://git.u-boot-project.org/u-boot/u-boot)。

**建议作品：** 基于匹配的 K1Mini BSP，构建精简 rootfs，完成一个真实外设的设备树、驱动、用户态接口及自动测试。可选一个未支持的 I²C 传感器、按键中断输入或带缓冲采样的设备；优先使用 IIO、input、hwmon 等已有子系统，而非全部塞进私有字符设备。

按以下层次推进：

1. 保留板厂引导链和工作 DTB，先实现可复现 rootfs 与交叉编译。
2. 用启动日志说明 BootROM、加载器、U-Boot、内核和 rootfs 的关系；具体链路以板厂 SDK 为准。
3. 实现外设 pinctrl、regulator/clock、总线节点和驱动绑定；同时写用户态验证工具。
4. 做错误注入、资源释放与设备恢复测试，提供清晰的 patch series 和构建配置。

**完成证据：** defconfig、固定提交号、DTS/驱动补丁、串口启动日志、驱动绑定证据、用户态接口说明、回归脚本，以及启动时间和 rootfs 体积的前后对照。

**面试追问：** probe 为什么延迟？中断上下文能否睡眠？devm 的边界是什么？设备树 compatible 如何匹配？内核、模块、DTB 不匹配有什么表现？为什么选择 IIO 而非自行设计 ioctl？

**当前系统边界：** 上游 Rockchip 仓库存在 `develop-6.1` 并不意味着它就是你镜像的精确源码。必须匹配板厂补丁、配置、DTB 和驱动接口；不能拿另一块 RK3568 板的固件直接刷入 K1Mini。建议用备用 SD 卡/可恢复介质和串口开展，保留当前可用桌面镜像。

你之前的 GNOME 故障排查可作为“小型兼容性案例”：区分 HDMI 链路、EGL、Xorg 和输入事件。但目前是 fbdev/软件渲染兼容方案，分辨率尚未做开机恢复，不能包装成已完成 GPU 驱动修复或完整 BSP 移植。详见 [gnome.md](gnome.md)。

## 6. 第 4 名：可靠 OTA 与设备交付

**适合岗位：** 嵌入式系统、设备平台、BSP、工业设备软件。

**上游：** [rauc/rauc](https://github.com/rauc/rauc)。README 明确描述签名校验、冗余 slot、U-Boot 等引导器集成，以及应用分区/系统分区等更新方式。

**建议作品：** 为第 2 或第 3 个项目加入带版本、签名和健康检查的升级，展示“下载成功”之外的设备生命周期管理。

**实施顺序：** 先实现应用版本目录和健康检查，学习回退状态机；再在独立实验镜像中规划 A/B rootfs，接入 RAUC slot、bootchooser/bootloader 状态和成功启动确认。普通目录切换不能称为已完成系统 A/B。

**你应自己实现：** 升级状态展示、硬件/版本兼容检查、健康确认、应用数据迁移方案、升级日志和失败恢复测试。签名、镜像校验和 TLS 分别解决不同问题。

**完成证据：** 正常升级、错误签名、错误目标板、版本不兼容、下载中断、启动失败的测试矩阵；记录实际回退到哪个 slot、数据是否保留、恢复耗时。断电实验只在可恢复实验介质进行。

**面试追问：** 谁决定本次启动成功？bootcount 如何持久化？系统回退后应用数据库能否兼容？更新 bootloader 与更新 rootfs 的故障范围有何不同？

**当前限制：** 你的现有根分区布局未证明适合 A/B，不能为了做项目直接在当前系统上假设已有双系统分区。

## 7. 第 5 名：低延迟视频网关 / 小型 NVR

**适合岗位：** 音视频、安防、网络 C++、嵌入式应用。

**上游：** [ZLMediaKit](https://github.com/ZLMediaKit/ZLMediaKit)、[MPP](https://github.com/rockchip-linux/mpp)，以及官方 MPP README 指向的 [Gitee 开发仓库](https://gitee.com/hermanchen82/mpp)。

**建议作品：** 接入 RTSP，提供网页播放、分段录像、录像索引、按需拉流和断流恢复；再按需求加硬件转码。协议转封装不等于转码，只有必要时才解码重编码。

**你应自己实现：** 设备管理、录制索引、磁盘配额、清理策略、时间戳校正、重连状态机、HTTP API 和访问控制。单独运行 MediaServer 二进制只是部署练习。

**完成证据：** 同一源与播放器下的首帧和端到端延迟；并发连接、CPU/RSS、码率、磁盘写入；源断开后恢复；录像完整性。ZLMediaKit README 中的服务器级并发/带宽宣传不是 RK3568 的性能指标，不引用为自己的成果。

**面试追问：** RTP 时间戳与墙钟如何对应？B 帧对延迟有什么影响？慢客户端是否拖慢生产端？RTSP 断流后怎样处理旧帧和录像片段？

## 8. 第 6 名：EtherCAT 采集与实时性测量

**适合岗位：** 工控、运动控制、实时 Linux。没有真实从站时，不建议优先选它作为主项目。

**上游：** [OpenEtherCATsociety/SOEM](https://github.com/OpenEtherCATsociety/SOEM)，README 描述 EtherCAT 主站开发库及 Linux/Windows 支持；没有宣称对所有 RK3568 网卡做过实时认证。

**建议作品：** 使用有线网口连接从站，完成设备发现、PDO 数据交换、状态监控和故障恢复；分别测量普通调度、CPU 亲和、实时调度，以及条件允许时 PREEMPT_RT 下的周期抖动。

**完成证据：** 实际 NIC/驱动/从站型号、周期配置、分布式时钟设置、丢周期和 WKC 异常统计、空载/CPU/网络/存储压力下的延迟分布。普通 Linux 能通信不等于达到硬实时要求。

**面试追问：** SOEM 与从站状态机如何交互？DC 同步有什么作用？调度延迟和网络延迟怎么区分？实时线程为什么避免动态分配和阻塞日志？

**硬件边界：** 板卡是否有可用直连网口、是否需要为 SSH 保留其他通路，以及 MAC/驱动在目标周期下的行为，都要实测。不能把旧 K1A 快照中的接口配置当作当前 K1Mini 的验证结果。

## 9. 第 7 名：LVGL 工业 HMI

**适合岗位：** 嵌入式应用、工业 HMI、C/C++ 图形终端。

**上游：** [lvgl/lvgl](https://github.com/lvgl/lvgl)，README 明确支持 Linux MPU、显示和输入设备，并说明 GPU 不是必需条件；可结合 [libmodbus](https://github.com/stephane/libmodbus) 做真实采集。

**建议作品：** 实时曲线、设备页、告警确认、参数设置、本地历史查询和断线提示，后端采集与 UI 独立线程/进程。先做桌面窗口版，再选择独占 framebuffer/DRM 的产品运行方式。

**你应自己实现：** 数据模型、线程安全的数据传递、增量刷新、告警状态机、输入校验和配置持久化；不要只更换一个现成 dashboard 的图片。

**完成证据：** UI 刷新和输入响应耗时、采集阻塞时 UI 是否仍可用、长时间曲线内存是否有界、中文字体资源体积和触摸坐标校准。

**面试追问：** 为什么后台线程不能随意直接操作控件？图表无限增长如何控制？触摸坐标与显示缩放怎样对应？何时选 LVGL，何时选 Qt？

**本机注意：** GNOME 正使用 `/dev/fb0`，直接让另一个程序写同一个 framebuffer 会冲突；需要独占显示时应设计独立启动方式，不能将“覆盖桌面”误判成 LVGL 显示驱动故障。

## 10. 第 8 名：RK3568 + RT-Thread MCU 协同终端

**适合岗位：** 同时要求 MCU、RTOS 和 Linux 的嵌入式岗位。

**上游：** [RT-Thread GitHub](https://github.com/RT-Thread/rt-thread) 与实际读取的 [RT-Thread Gitee](https://gitee.com/rtthread/rt-thread)。本方案让 RT-Thread 跑在有明确 BSP 的 STM32 等 MCU 上，RK3568 继续运行 Linux，**不是声称已经核实 K1Mini 可直接替换为 RT-Thread**。

**建议作品：** MCU 负责定时采样/PWM/实时保护，RK3568 负责界面、存储、网络和升级。通过 UART/USB，或加收发器后的 RS485/CAN 连接；接口电平和板端支持需核对。

**你应自己实现：** 帧头、长度、序号、CRC、超时和重同步；Linux 侧设备服务；MCU 看门狗与失联策略；参数读写和协议版本兼容。

**完成证据：** 断线重连、乱序/损坏帧处理、Linux 重启时 MCU 的行为、采样周期抖动、协议抓取和两端联调日志。

**面试追问：** 哪些任务必须在 MCU 执行？为什么 CRC 通过仍需要序号？粘包/半包怎么处理？Linux 服务挂掉时怎样保持设备进入可预测状态？

## 11. 第 9 名：ROS 2 / Nav2 导航小车

**适合岗位：** 机器人软件、移动机器人、ROS 2 嵌入式平台。

**上游：** [ros-navigation/navigation2](https://github.com/ros-navigation/navigation2)，README 链接其 [官方入门与设置文档](https://docs.nav2.org/)。当前 Ubuntu 24.04 应优先核对对应 ROS 2 发行版（例如 Jazzy）的 ARM64 软件和依赖，不能照搬 Ubuntu 22.04/Humble 的安装步骤。

**建议作品：** 底盘驱动、编码器里程计、激光雷达、建图/定位、路径规划、避障和任务状态接口。只看仿真界面移动，不足以证明完成实车集成。

**个人贡献：** 优先做底盘驱动、时间同步、TF/里程计诊断、参数调优和异常恢复；不必一开始重写规划算法。

**完成证据：** rosbag、TF 树、重复路线定位误差、导航成功率的定义和原始次数、CPU/内存、传感器丢帧和失联测试。控制实验条件后再比较参数。

**面试追问：** TF 树为什么不能闭环？定位漂移是轮速、时间戳还是激光问题？DDS QoS 如何影响消息？Linux 平台和底盘 MCU 的控制边界如何划分？

**当前限制：** 4 GB 内存上同时运行 GNOME 软件渲染、仿真、建图和可视化压力大。可把 RViz/仿真放 PC，板端运行驱动与导航节点；完整机器人还需要额外硬件。

## 12. 第 10 名：Linux 语音交互终端

**适合岗位：** 智能终端、音频 Linux 应用、物联网交互。

**上游：** [Yinyifeng18/xiaozhi-linux-rk3568](https://github.com/Yinyifeng18/xiaozhi-linux-rk3568)，项目描述和 README 涉及 RK 平台、音频处理、WebSocket、LVGL 与交叉编译。快照最后推送为 2025-03-26，文档中带有旧 Buildroot 工具链路径和外部课程链接；推荐依据是公开代码与技术内容，不是课程宣传。

**建议作品：** 麦克风输入、语音交互、播放、状态 UI 与断网处理，再增加本地命令或设备控制。

**你应自己实现：** 音频采集/播放缓冲、打断与状态机、回声路径分析、网络恢复和离线行为。使用外部语音/大模型服务时应说明依赖及服务成本；不能把“调用云端聊天接口”写成“RK3568 本地部署大模型”。

**完成证据：** 录音到响应的分段延迟、丢音/欠载统计、噪声环境测试、网络异常时表现和内存稳定性。

**面试追问：** ALSA period/buffer 设置如何取舍？采样率转换在哪里发生？用户打断时怎样停止旧回复？回声和设备播放串音怎么区分？

## 13. 第 11 名：OpenWrt 网关与网络插件

**适合岗位：** 路由器、网络设备、嵌入式网络软件。

**上游：** [openwrt/openwrt](https://github.com/openwrt/openwrt)，README 描述用于嵌入式设备的 Linux 系统及构建流程。支持 Rockchip 生态不代表仓库存在当前 K1Mini 的现成固件，必须检查具体 target、设备 DTS、网卡和 Wi-Fi 支持。

**建议作品：** 基于匹配设备构建固件，并实现网络诊断/链路质量监控插件，提供 LuCI 或 API 界面、配置持久化和故障恢复。

**完成证据：** 构建配置、自研插件、路由/NAT/防火墙的数据路径说明、吞吐与 CPU 对照、丢包/断线恢复和版本升级行为。

**面试追问：** 路由和桥接有什么区别？netfilter/nftables 在路径中的位置？MTU、TCP 重传和 NAT 会怎样影响测试？

只刷入别人制作的固件并配置代理，工程贡献有限；不要把日常软路由使用经验直接列为驱动开发经历。

## 14. 第 12 名：Home Assistant 本地接入网关

**适合岗位：** 智能家居、IoT 平台接入、Python 设备集成。

**上游：** [home-assistant/core](https://github.com/home-assistant/core)，README 描述模块化架构及自定义设备集成；可结合 [Mosquitto](https://github.com/eclipse-mosquitto/mosquitto)。

**建议作品：** 接入你自己实现的 RS485/MQTT 设备，编写自定义 integration 或规范的设备发现、状态上报与本地自动化，提供离线工作路径。

**完成证据：** 集成源代码、重连和实体状态测试、设备离线显示、配置迁移和本地自动化演示。安装前核对当前发布版对 Python/容器及 ARM64 的要求，不将最新 Core 直接塞进不匹配的系统 Python。

**面试追问：** 设备状态和命令回执如何区分？离线时实体如何变化？异步事件循环为什么不能阻塞？配置升级怎样兼容旧用户？

单纯安装和添加现成设备适合入门；要提高简历价值，必须有自己维护的设备协议或集成代码。

## 15. 第 13 名：NAS、备份和存储监控

**适合岗位：** 存储运维、边缘服务器；作为嵌入式开发主项目的辨识度较低。

**上游：** [openmediavault/openmediavault](https://github.com/openmediavault/openmediavault)，README 明确基于 **Debian Linux**，提供 SMB/CIFS、rsync 等服务和插件扩展。

**建议作品：** 在单独的 Debian 实验系统中做备份策略、存储健康监控和恢复工具，并开发插件或自动化检查。**不建议直接把 OMV 安装脚本运行在目前配置好的 Ubuntu GNOME 系统上。**

**完成证据：** 大文件与小文件负载、网络/磁盘瓶颈分离、SMART/健康状态、恢复演练、校验与备份保留策略。USB 桥接器是否支持 SMART/休眠需实测。

**面试追问：** RAID 为什么不是备份？fsync 与缓存对性能和断电行为有什么影响？吞吐受磁盘、USB 总线还是网络限制？

仅做文件共享、下载器和网页管理，作为家用工具很好，但对 C/C++、驱动等研发岗的证明力低于前面的项目。

## 16. 仓库核查结果与平台覆盖

下表列出本次实际读取 README/项目资料的主要来源。“最近推送”来自 GitHub API 快照，仅表示仓库活动时间，不等于版本稳定或在 K1Mini 上通过测试；没有以 Star 数代替技术判断。

| 来源 | 最近推送/更新时间（日期） | 本次核实的关键点 |
|---|---|---|
| [RKNN-Toolkit2](https://github.com/airockchip/rknn-toolkit2) | 2026-10-20 | RK3568 支持；转换端/板端 Runtime/内核驱动分工 |
| [RKNN Model Zoo](https://github.com/airockchip/rknn_model_zoo) | 2026-10-20 | RK3568 示例与模型转换、C/Python 推理 |
| [MPP GitHub](https://github.com/rockchip-linux/mpp) | 2026-11-03 | RK3568 支持，并指向对应 Gitee 开发仓库 |
| [MPP Gitee](https://gitee.com/hermanchen82/mpp) | 2026-11-03（页面更新时间） | 公开项目资料、README、与官方 GitHub 的关联 |
| [librga](https://github.com/airockchip/librga) | 2026-06-10 | RK3568、Linux aarch64 库与平台支持 |
| [ZLMediaKit](https://github.com/ZLMediaKit/ZLMediaKit) | 2026-11-19 | C++、ARM、流媒体协议、C API |
| [Rockchip Linux](https://github.com/rockchip-linux/kernel) | 2026-08-28 | 仓库默认分支为 develop-6.1；不等于板厂精确 BSP |
| [Buildroot](https://github.com/buildroot/buildroot) | 2026-11-21 | 构建嵌入式 Linux 系统的源码基础 |
| [U-Boot](https://github.com/u-boot/u-boot) | 2026-11-20 | 引导器源码及官方托管入口 |
| [libmodbus](https://github.com/stephane/libmodbus) | 2026-07-02 | C、串口/以太网 Modbus、Linux 支持 |
| [Mosquitto](https://github.com/eclipse-mosquitto/mosquitto) | 2026-11-19 | MQTT broker 与客户端库 |
| [RAUC](https://github.com/rauc/rauc) | 2026-11-13 | 签名、slot、冗余更新及引导器集成 |
| [SOEM](https://github.com/OpenEtherCATsociety/SOEM) | 2026-10-15 | Linux EtherCAT 主站库 |
| [LVGL](https://github.com/lvgl/lvgl) | 2026-11-21 | Linux MPU/输入显示支持、软件渲染可行 |
| [RT-Thread GitHub](https://github.com/RT-Thread/rt-thread) | 2026-11-18 | RTOS、BSP、组件与开发工具 |
| [RT-Thread Gitee](https://gitee.com/rtthread/rt-thread) | 2026-11-21（页面更新时间） | 实际读取中文项目介绍及 README |
| [Navigation2](https://github.com/ros-navigation/navigation2) | 2026-11-21 | 导航框架及官方配置/入门文档入口 |
| [Linux 小智 RK3568](https://github.com/Yinyifeng18/xiaozhi-linux-rk3568) | 2025-03-26 | 社区语音项目和交叉编译说明 |
| [OpenWrt](https://github.com/openwrt/openwrt) | 2026-11-21 | 嵌入式 Linux 系统与构建基础 |
| [Home Assistant Core](https://github.com/home-assistant/core) | 2026-11-21 | 模块化设备集成框架 |
| [OpenMediaVault](https://github.com/openmediavault/openmediavault) | 2026-11-21 | Debian NAS 及插件框架 |
| [YoloV8-NPU 社区示例](https://github.com/Qengineering/YoloV8-NPU) | 2024-06-19 | 明确涉及 RK3566/68/88，适合作为入门参考 |

**覆盖限制：** Gitee 的 `openharmony/device_board_hihope` 与 `openharmony/device_soc_rockchip` 页面在本次读取中返回 HTTP 405，未取得有效正文。因此没有把 OpenHarmony 列入已验证推荐清单，更没有声称其镜像可直接运行于 K1Mini。Gitee 已有效覆盖的是 RT-Thread 和 MPP；报告主体资料来自 GitHub。检索搜索引擎时取得的无关结果没有作为项目证据。

**开源边界：** RKNN 等公开 SDK/示例可能配套二进制工具、Runtime 或模型文件，不能把“仓库可访问”理解为全栈均开放源码。不同仓库、子模块和模型的许可需要按所选版本核对；API 显示 `NOASSERTION`/空许可时，本报告不替它们补写一个许可证。克隆时应固定 tag/commit，并保留上游及个人代码的区别。

## 17. 针对你当前开发板的选择建议

### 17.1 按目标岗位调整排序

| 你要投的方向 | 优先顺序 | 最值得保留的作品材料 |
|---|---|---|
| Linux 驱动 / BSP | 3 → 4 → 8 | DTS/驱动补丁、串口日志、构建配置、回归与故障定位 |
| 嵌入式 C/C++ 应用 | 2 → 1 → 5 | 并发模型、协议实现、状态机、测试及性能报告 |
| 边缘 AI / 视觉部署 | 1 → 5 → 4 | 模型/驱动版本、精度与端到端性能、设备稳定性 |
| 工控 / 运动控制 | 6 → 2 → 8 | 周期抖动、真实设备通信、故障响应与实时边界 |
| HMI / 智能终端 | 7 → 2 → 10 | UI 与后端解耦、设备状态、输入响应与音频链路 |
| 机器人 | 9 → 8 → 3 | 实车数据、底盘驱动、TF/时间同步和可重复实验 |

### 17.2 不加硬件就能开始什么

现有 RK3568 + PC 足以开始：Modbus TCP/MQTT 网关、文件输入的视觉流水线、流媒体网关、桌面窗口版 HMI、Buildroot 构建和应用升级实验。选择 USB 摄像头通常比第一步适配 MIPI CSI 更易隔离问题；真正的传感器驱动和工业控制项目再按需要补硬件。

当前 GNOME 使用 fbdev 与 Mesa llvmpipe，桌面渲染会占用 CPU；NPU、MPP、RGA 是不同硬件/软件路径，不能因为 GNOME 未用 Mali 加速就断定它们不可用，也不能反过来认为它们已经通过验证。做性能实验时记录桌面/RDP 状态、温度、频率策略、供电和其他负载，确保前后实验条件一致。

本次仅调研与写文档，**没有安装这些项目、刷机或改变现有内核配置**。

### 17.3 推荐的实际推进顺序

如果你还没决定投哪个方向，建议先选 **第 2 名工业网关**：硬件依赖少，便于练习 C/C++、Linux I/O、协议和可靠性。完成之后，按兴趣走视觉/NPU或驱动/BSP，而不是立刻叠加机器人、语音、NAS 等全部方向。

| 阶段 | 工作 | 进入下一阶段的条件 |
|---|---|---|
| 1：跑通基础 | 固定版本、复现上游最小示例、记录工具链 | 能从干净环境重新编译和启动，能解释数据流 |
| 2：个人开发 | 自己实现协议/状态机/驱动或流水线模块 | 功能有明确接口与测试，提交记录可区分上游和自研 |
| 3：验证与定位 | 基线、异常恢复、资源和性能测量 | 有原始数据、可复现问题和修复前后对照 |
| 4：设备交付 | 打包、systemd、配置、升级、文档 | 别人按 README 可复现，有恢复路径与已知限制 |

不规定固定几周完成；阶段耗时取决于你的 C/Linux 基础、硬件和目标范围。尽早完成一个闭环，再扩展模块。

## 18. 怎样把项目做到值得写进简历

建议自己的仓库至少交付以下材料：

```text
README.md           目标、硬件、运行方式、实测结果、限制
docs/architecture   数据流、线程/进程、接口、故障状态
src/                个人实现的模块
configs/            构建、设备和运行配置（不含密钥）
tests/              正常、异常、重连、长稳和正确性验证
benchmarks/         脚本、原始数据、基线及图表
patches/            上游/板厂代码改动与适用提交号
deploy/             打包、systemd、升级与恢复说明
```

这只是交付结构建议，不要求为了目录数量写空文件。图形 demo 要有代码和数据，性能项目要同时说明正确性；自己没有做过的零拷贝、实时、精度提升、协议兼容不能写入成果。

简历描述可以采用下面的填空形式，**占位符必须换成你实际测得的数据**：

> 基于 RK3568 开发［设备/系统］，负责［具体模块］；针对［可复现问题］采用［设计/修复］，在［固定硬件、版本、负载］下将［指标］从［基线］改善至［结果］，完成［异常场景］与［持续时间］验证，并交付［代码/构建/部署材料］。

面试前准备好解释：为何选这套方案；代码中最难的一处在哪里；如何发现和证明瓶颈；做过哪些失败尝试；哪些部分来自上游；还有哪些限制。对当前板子而言，做到这些的一个工业网关或视觉设备，通常比只展示多个项目的启动截图更有说服力。
