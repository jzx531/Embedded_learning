# 与 RK3568 边缘视觉告警路线相似的已有项目

核查日期：2026-11-23。对应本工作区 `learning_route.md` 中的视频输入、RKNN 推理、有界队列、区域告警、截图/事件存储、管理界面和设备交付路线。

**最值得你读的完整 C++ 参考是 `3355-del/rk3588-multi-stream-alarm`；与你芯片和触屏终端形态最接近的是 `1559359542/-rk3568-safety-terminal-public`；希望先体验成熟完整产品，则看 Frigate。** 三者分别解决工程实现、板级终端与产品功能的问题，适配成本不同。

本次实际检索 GitHub 仓库、公开搜索页面，并读取候选的 README、完整目录树及部分关键源码；没有在你的 K1Mini 上安装、编译或运行它们。下文“作者验证”指其仓库提供的说明或材料，不代表我独立复现过板端结果。“已有项目”也不等于所有功能、精度和异常场景已经充分验证。

## 1. 筛选结果

推荐顺序按“与你的 C++ 嵌入式求职项目和现有板卡的相关性”排列，不按 Star 或作者性能数字排名。

| 顺序 | 项目 | 已有实现与价值 | 平台/语言 | 对当前开发板的限制 | 主仓库许可 |
|---:|---|---|---|---|---|
| 1 | [RK3588 多路检测告警](https://github.com/3355-del/rk3588-multi-stream-alarm) | 有界流水线、区域告警、截图、可靠事件投递、SQLite 接收器、交互控制台 | RK3588S；C++17＋Python 工具 | 作者验证为 Orange Pi 5，需迁到 RK3568 | MIT |
| 2 | [RK3568 工业安全监测终端](https://github.com/1559359542/-rk3568-safety-terminal-public) | 摄像头/RKNN/ROI、传感器、GPIO/PWM 告警、Qt/QML、SQLite、MQTT | RK3568；C/C++、QML | 原项目 Linux 4.19/Buildroot，与你的 6.1/Ubuntu 不同 | 尚未声明 |
| 3 | [Frigate](https://github.com/blakeblackshear/frigate) | 完整本地 NVR、检测、区域/停留规则、事件、录像、快照、Web 与 MQTT | 官方列出 RK3568；Python/TypeScript 等 | 需要 Rockchip BSP 驱动和对应容器配置；体量较大 | MIT |
| 4 | [rknn-yolo-deploy](https://github.com/jyy629/rknn-yolo-deploy) | RK3568 RTSP→MPP→RGA→RKNN→MJPEG、有界环形缓存、后处理优化 | RK3568；C++17 | 是视频检测管线，尚缺本路线完整告警与数据库应用 | 尚未声明 |
| 5 | [Qt_YOLOv5_RTSP_RK3566](https://github.com/trgue/Qt_YOLOv5_RTSP_RK3566) | 摄像头检测、Qt 界面、UDP/RTSP 输出、板端显示 | RK3566；C++/Qt | 需换成 RK3568 模型/依赖；缺告警闭环 | MIT |
| 6 | [rknn-surveillance](https://github.com/philipvh/rknn-surveillance) | 事件录像、持续性判定、通知、PTZ/PIR、Web 面板、健康检查 | RK3588；Python | RK3568 尚无本次可核实的运行记录；不是 C++ 主线 | Apache-2.0 |
| 补充 | [edge-security-kit](https://github.com/suharvest/edge-security-kit) | 入侵/越线/停留、MQTT、SQLite、REST/WS、规则编辑工作台 | RK3588/RK3576 等；Python/JS | 未见 RK3568 验证，系统比第一版复杂 | 未识别到主仓库许可证 |
| 补充 | [Surveillance-Camera](https://github.com/xigua-tree/Surveillance-Camera) | RK3568 采集、人体检测、MPP 编码、ZLMediaKit 推流、LCD 预览 | RK3568；C++ | 直接 DRM 显示与现有桌面存在集成问题，缺告警闭环 | 未识别到主仓库许可证 |

“尚未声明许可”的仓库应称为**源码公开参考项目**，不能默认具有 MIT/Apache 那样的复用授权。阅读架构可以作为学习资料；计划复制代码并公开自己的派生作品前，需要明确对应许可。模型、SDK 和第三方文件另按各自许可处理。

## 2. 最推荐的 C++ 完整参考：rk3588-multi-stream-alarm

链接：[3355-del/rk3588-multi-stream-alarm](https://github.com/3355-del/rk3588-multi-stream-alarm)。

### 已经做了什么

作者在 Orange Pi 5 / RK3588S / 8 GB 上组织了以下链路：

```text
USB / 文件 / RTSP
→ 采集 → 有界队列 → RGA → 有界队列 → RKNN/后处理
→ 区域判定与冷却 → 独立 IO 线程
→ PNG 截图 + 本地 outbox → TCP JSON + ACK
→ Python 接收端 SQLite 入库
```

配有浏览器实时控制台，可冻结显示、调整多边形区域、保存规则和查看事件。作者 README 提供板卡运行记录、路径等价性测试以及摄像头＋文件双路约一小时运行说明；这些是作者提供的实验结果，不能转用为你的 RK3568 指标。

### 这次核实到的真实代码

- [`include/msad/RingBuffer.h`](https://github.com/3355-del/rk3588-multi-stream-alarm/blob/d91ea0b8465cee5ced1bc2d44147e9e65d286eaa/include/msad/RingBuffer.h)：有界缓存、丢弃计数、关闭与条件变量；视频帧与事件队列采用不同满队列语义。
- [`src/pipeline/VideoPipeline.cpp`](https://github.com/3355-del/rk3588-multi-stream-alarm/blob/d91ea0b8465cee5ced1bc2d44147e9e65d286eaa/src/pipeline/VideoPipeline.cpp)：采集、预处理、推理线程与队列，选择真实/模拟后端，构造告警任务通道。
- [`src/pipeline/VideoPipelineAlarm.cpp`](https://github.com/3355-del/rk3588-multi-stream-alarm/blob/d91ea0b8465cee5ced1bc2d44147e9e65d286eaa/src/pipeline/VideoPipelineAlarm.cpp)：简单目标关联、多边形中心点判定、按目标/区域冷却、截图和投递。事件队列满时拒绝新任务且不更新冷却，让后续检测帧有机会再尝试。
- [`src/hal/DurableAlarmNotifier.cpp`](https://github.com/3355-del/rk3588-multi-stream-alarm/blob/d91ea0b8465cee5ced1bc2d44147e9e65d286eaa/src/hal/DurableAlarmNotifier.cpp)：本地 outbox、持久化、独占锁、容量限制与后台发送。
- [`tools/alarm_receiver.py`](https://github.com/3355-del/rk3588-multi-stream-alarm/blob/d91ea0b8465cee5ced1bc2d44147e9e65d286eaa/tools/alarm_receiver.py)：SQLite 的 `event_id UNIQUE`、重复事件处理，以及入库事务结束后发送 ACK。
- [`src/hal/RealInferenceEngine.cpp`](https://github.com/3355-del/rk3588-multi-stream-alarm/blob/d91ea0b8465cee5ced1bc2d44147e9e65d286eaa/src/hal/RealInferenceEngine.cpp)：模型 context、`rknn_dup_context`、SDK 版本查询、张量检查与推理适配。
- [`docs/live-console.md`](https://github.com/3355-del/rk3588-multi-stream-alarm/blob/d91ea0b8465cee5ced1bc2d44147e9e65d286eaa/docs/live-console.md)：模拟/硬件实时控制台入口和运行边界。

### 为什么适合你

它能直接对应你已有的 C++ 并发、网络、缓冲管理能力，同时补上嵌入式视觉应用的生命周期与可靠性。比只把单图 demo 改成 `while` 循环更能帮助你理解工程组织。

其中“视频过载丢旧帧”与“告警事件持久化重试”的区别尤其值得学：视频帧可以为了新鲜度主动舍弃；已经接纳的告警不能按同样方式随意覆盖。

### 迁移与尚缺功能

1. 从单路开始，使用重新面向 RK3568 转换的模型。当前推理源码明确检查一个输入和九个输出，不能塞入任意 YOLO ONNX/RKNN。
2. 核对 RK3568 的 Runtime/驱动是否支持所用 context 与内存 API；RGA/MPP/DMA-BUF 路径按当前 BSP 验证。
3. 作者验证环境为 Ubuntu 22.04.5 / 6.1.99 / 驱动 0.9.8 / Runtime 2.3.0，不是你的当前镜像。
4. 当前核心区域逻辑是中心点进入＋冷却。刚才路线里的“持续停留 dwell 状态机”仍可作为你自己的新增功能，不能把已有冷却等同于停留判断。
5. 高 FPS 材料来自指定文件源，RTSP 只说明验证过回环；不是多路真实摄像头全部同速的证明。

**建议用途：作为你的主要工程阅读参考。** 保留已下载的官方 Model Zoo 来建立 RK3568 推理基线，逐模块借鉴该项目的架构。

## 3. 与你的板子和终端形态最像：RK3568 工业安全监测与 HMI 告警终端

链接：[1559359542/-rk3568-safety-terminal-public](https://github.com/1559359542/-rk3568-safety-terminal-public)。

### 已经做了什么

```text
摄像头 → RKNN YOLOv5 → 人员脚点 ROI 判断
                         ↓
门磁 / 雷达 / 温湿度 → safety_alarmd
                         ↓
GPIO/PWM 告警 → 状态快照 → SQLite / MQTT / Qt-QML HMI
```

包含 `safety_event` 字符设备、设备树、用户态告警服务、SQLite 服务、MQTT 上报和 Qt/QML 页面。仓库有现场照片、AI 进入/清除、门磁及历史记录等文本/JSON 材料，完整程度超过单模型示例。

### 已核实的源码入口

- [`userspace/ai_yolov5/src/main.cc`](https://github.com/1559359542/-rk3568-safety-terminal-public/blob/1f2c6ebb59a14a376b73b9ebf3611a791af3e913/userspace/ai_yolov5/src/main.cc)：摄像头与推理主链路、归一化 ROI、人员进入事件和连续漏检后的清除状态。
- [`userspace/safety_alarmd/safety_alarmd.c`](https://github.com/1559359542/-rk3568-safety-terminal-public/blob/1f2c6ebb59a14a376b73b9ebf3611a791af3e913/userspace/safety_alarmd/safety_alarmd.c)：合并 AI/雷达等告警状态和用户态控制接口。
- [`userspace/sqlite_eventd/sqlite_eventd.c`](https://github.com/1559359542/-rk3568-safety-terminal-public/blob/1f2c6ebb59a14a376b73b9ebf3611a791af3e913/userspace/sqlite_eventd/sqlite_eventd.c)：SQLite 事件服务、状态变化跟踪等实现。
- [`userspace/hmi_qml/src/history_model.cpp`](https://github.com/1559359542/-rk3568-safety-terminal-public/blob/1f2c6ebb59a14a376b73b9ebf3611a791af3e913/userspace/hmi_qml/src/history_model.cpp)：通过 Qt SQL 查询事件表，向 HMI 提供历史告警。

### 对你有什么用

如果你想把 DSI 屏做成“实时监控＋告警中心＋历史事件＋设备状态”，这个参考比单纯浏览器画框更贴近目标。它还展示了如何把 AI 事件放进统一设备告警模型。

### 为什么不能原封不动部署

- 作者使用 Linux 4.19.232/Buildroot，而你此前记录为 Ubuntu 24.04/Linux 6.1.141；工具链文件也包含作者本机 SDK/sysroot 路径。
- GPIO、I²C、UART、PWM、DTB 和屏幕时序均依赖板级设计。即使同为 RK3568、屏幕同为 800×1280，也不能直接替换 K1Mini 的 DTB。
- 文档出现的约 29.99 FPS 是 H.264 **预览链路**记录，不能说它证明 YOLO 推理也是 30 FPS。
- 目前 README 的许可部分写明“待补充”，应作为源码公开的参考，不直接视为可自由复用的开源底座。

**建议用途：阅读系统拆分、HMI、事件与外设整合。** 第一轮只在现有桌面上开发用户态功能；新增内核驱动与设备树另立验证任务。

## 4. 完整产品参考：Frigate

链接：[blakeblackshear/frigate](https://github.com/blakeblackshear/frigate)。

这是完整的本地 AI NVR，已有摄像头输入、目标检测、对象跟踪、区域/停留规则、录像保留、快照、事件回看、Web 管理与 MQTT 对接。它更接近最终用户可以操作的软件产品。

### RK3568 支持是有明确依据的

读取到的官方仓库文档：

- [`object_detectors.md` 的 Rockchip 部分](https://github.com/blakeblackshear/frigate/blob/8c887546647619451431a74f139cd80b24ff53d8/docs/docs/configuration/object_detectors.md#rockchip-platform)：明确列出 RK3568，所述实现使用 Toolkit2 v2.3.2。
- [`installation.md` 的 Rockchip 部分](https://github.com/blakeblackshear/frigate/blob/8c887546647619451431a74f139cd80b24ff53d8/docs/docs/frigate/installation.md#rockchip-platform)：要求 Rockchip BSP 5.10/6.1 及对应媒体/NPU 驱动，示例检查 RKNPU v0.9.2 或更新，并使用 `stable-rk` 镜像。
- [`frigate/detectors/plugins/rknn.py`](https://github.com/blakeblackshear/frigate/blob/8c887546647619451431a74f139cd80b24ff53d8/frigate/detectors/plugins/rknn.py)：实际 RKNN 检测器和模型处理代码。
- [`zones.md`](https://github.com/blakeblackshear/frigate/blob/8c887546647619451431a74f139cd80b24ff53d8/docs/docs/configuration/zones.md)：区域编辑、`loitering_time` 与 `inertia`，可参考停留和边界抖动处理。

容器不能补齐宿主机缺少的驱动。你的内核是 6.1 只能说明版本系列相近，仍需检查实际 BSP 能力、设备节点和驱动；不能仅因 `uname` 没有文档示例的后缀就判断失败。

### 怎么用于你的项目

- 看它的区域编辑、事件回看、保留策略与 MQTT 接口，明确自己的第一版应该给用户什么功能。
- 部署体验有价值，但它的主要应用层是 Python/TypeScript；只把容器跑起来，难以体现你的 C++ 并发与系统工程贡献。
- 约 4 GB 内存、32 GB eMMC 与现有桌面下，应先单路、限制录像和留存，再评估资源，不能把大型多摄像头配置直接搬过来。
- 本次读取的是 `dev` 分支快照。真正部署应选择稳定 release，并使用该 release 对应文档，不把开发分支配置和稳定镜像任意混用。

**建议用途：成熟产品行为和系统设计的对照；若首要目标是尽快得到可操作的成品，优先评估它。**

## 5. 同芯片视频性能参考：rknn-yolo-deploy

链接：[jyy629/rknn-yolo-deploy](https://github.com/jyy629/rknn-yolo-deploy)。

作者说明完成 RK3568 单路 `RTSP→GStreamer→MPP→RGA→RKNN→HTTP MJPEG` 验证，并提供多路结构、NEON/LUT 后处理及模型裁剪分析材料。

核实到 [`any_include/strategy.hh`](https://github.com/jyy629/rknn-yolo-deploy/blob/9db419da1eac8e29511a71f8df552aa7053fc6a8/any_include/strategy.hh) 的 `circular_list`、丢帧释放回调和各级缓存，以及 [`yolo8_1.1.0/run.cc`](https://github.com/jyy629/rknn-yolo-deploy/blob/9db419da1eac8e29511a71f8df552aa7053fc6a8/yolo8_1.1.0/run.cc) 的管线组装。

对刚才学习路线的价值集中在“有界缓存”和“后期 MPP/RGA/后处理优化”。当前公开主线没有完整区域告警、事件库和管理业务，因此不列为完整告警成品。

需注意：README 自己写明多路未压测、未完成标准 mAP 评测；构建脚本依赖作者路径；自动配网脚本会修改网络设置，不应在你当前 SSH 会话下直接照跑。其“全程零拷贝”和性能表属于作者表述，本次未完成缓冲路径与计时口径审计，不据此作性能保证。当前未声明主仓库许可证。

## 6. 简单可读的界面起步：Qt_YOLOv5_RTSP_RK3566

链接：[trgue/Qt_YOLOv5_RTSP_RK3566](https://github.com/trgue/Qt_YOLOv5_RTSP_RK3566)。

基于官方 Model Zoo YOLOv5，OpenCV 读取摄像头、Qt 显示检测画面，支持 UDP 输出，README 还给出了 MPP/FFmpeg RTSP 输出说明。作者平台为 RK3566 泰山派，Qt 5.12.10、OpenCV 3.4.1，并有实际效果图片。

实际读取 [`mainwindow.cpp`](https://github.com/trgue/Qt_YOLOv5_RTSP_RK3566/blob/51328ef9b8d00cd96a591492b1aab71d29c9d6a9/mainwindow.cpp)，可以看到 QTimer 驱动刷新、摄像头打开、`yolo_detect` 和 UDP 发送。学习入口短，适合先理解“检测结果如何进入 Qt”。

它不是完整告警系统；当前界面代码中有固定 `/dev/video9`，迁移时需要设备配置化。推理也出现在刷新回调路径，后续应考虑工作线程与 UI 隔离，避免你刚解决的触屏流畅性再次被检测阻塞。

**建议用途：Qt 入门与显示集成参考。** 不建议为了匹配作者环境，把你现有桌面整体降级到旧 Qt/OpenCV。

## 7. 完整离线事件录像参考：rknn-surveillance

链接：[philipvh/rknn-surveillance](https://github.com/philipvh/rknn-surveillance)。

作者说明在 RK3588/Radxa Rock 5B 上用于网球俱乐部监控，包含 YOLOv10、事件触发录像、预录片段合并、告警持续性/日程判断、PTZ、PIR、Web 面板、通知和健康检查。主仓库 Apache-2.0。

本次读取了 `yolov10.py`、`alerts.py`、`health.py`。其中 `AlertPolicy` 和基于帧持续到达的 systemd watchdog 设计，适合你后期参考：仅进程活着不等于视频链路健康。

它主要是 Python，业务规则不是本路线同样的多边形 ROI 系统。作者的“Rockchip 通用”描述不等于已有 RK3568 实测；模型需要为 RK3568 重新转换，GPIO/PTZ 与输入依赖按需裁减。

**建议用途：学习事件录像、误报控制和长期运行维护，不作为你的 C++ 主工程起点。**

## 8. 另外两个相关实现

### edge-security-kit

[仓库](https://github.com/suharvest/edge-security-kit) 将检测器与规则引擎通过 MQTT 契约分离；已有 `zone_enter`、`loitering`、`line_cross`，SQLite、REST/WebSocket、规则编辑和事件工作台。

本次读取的 `hub/edge_hub/rules/zone.py` 确实包含单调时间下的停留计算，`hub/edge_hub/storage.py` 有事件、设备和规则等表。它比前面两个 C++ 项目更接近“人员停留/越线规则平台”，但主要使用 Python/JS，已说明的 Rockchip 验证平台是 RK3588/RK3576 等，未见 RK3568 记录，也未识别到主仓库许可证。

### Surveillance-Camera

[仓库](https://github.com/xigua-tree/Surveillance-Camera) 的 README 和源码目录覆盖 RK3568 V4L2→RKNN→MPP→ZLMediaKit 与 LCD 预览，具备采集/推理/编码线程组织。此项本次只核对了 README 和目录，未深入审计核心实现。

它更适合参考“检测＋编码推流”，不满足完整告警/SQLite/管理系统。LCD 使用 DRM＋RGA 路径；与当前 XFCE 并存需要处理 DRM 资源和显示会话，不能直接把它当普通桌面窗口运行。未识别到主仓库许可证。

## 9. 给你的明确选型

**继续保留官方 Model Zoo 作为 RK3568 推理基线，把 `3355-del/rk3588-multi-stream-alarm` 作为主要 C++ 工程参考，RK3568 综合终端作为 HMI/外设参考。**

推荐阅读顺序：

1. 官方 Model Zoo 的普通单图推理，确认你板子的 Runtime/驱动/模型组合。
2. C++ 告警项目的 `RingBuffer.h`、`VideoPipeline.cpp`，理解如何管理帧、线程和退出。
3. `VideoPipelineAlarm.cpp`、`DurableAlarmNotifier.cpp`、`alarm_receiver.py`，理解事件生成、持久化与确认语义。
4. 同芯片终端的 AI 状态、`safety_alarmd`、SQLite 和 HMI，设计适合自己板子的界面与执行端。
5. 看 Frigate 的区域停留、事件和保留策略，再决定自己的功能边界。

你的个人增量可以定为：**RK3568 单路适配、明确的停留状态机、HTTP 配置接口、资源与故障可观测性、与前两个项目相关的 STM32 串口联动。** 这些都需要自己实现并验收，不把上游的功能直接计入个人贡献。

如果只选一个“完整系统先体验”，优先评估 Frigate；如果只选一个“适合 C++ 源码学习的成品参考”，优先看第 1 项；如果只想看“RK3568 触屏＋外设告警成品长什么样”，看第 2 项。

## 10. 版本与证据记录

以下为本次读取的 GitHub 分支提交，后续 upstream 可能变化：

| 项目 | 分支 | 本次快照 |
|---|---|---|
| rk3588-multi-stream-alarm | main | `d91ea0b8465cee5ced1bc2d44147e9e65d286eaa` |
| rk3568-safety-terminal-public | main | `1f2c6ebb59a14a376b73b9ebf3611a791af3e913` |
| Frigate | dev | `8c887546647619451431a74f139cd80b24ff53d8` |
| rknn-yolo-deploy | main | `9db419da1eac8e29511a71f8df552aa7053fc6a8` |
| Qt_YOLOv5_RTSP_RK3566 | main | `51328ef9b8d00cd96a591492b1aab71d29c9d6a9` |
| rknn-surveillance | main | `ca0d8485dd713bd65694e2887430c99b517c572f` |
| edge-security-kit | main | `8575796d82322e9b0e11a1cfd55557963a104b68` |
| Surveillance-Camera | main | `3da7f1286e9653a6e0b588095f8a5addba5b827d` |

本地证据在 `work/completed-vision-projects/`：GitHub 元数据、README、目录树，以及 `source/` 中的关键文件快照。检索词覆盖 RK3568/RK3588、RTSP、Qt、RKNN、告警、入侵和 surveillance。

覆盖边界：公开网页搜索的一些结果相关性不足，Google 和 Frigate 文档站点读取超时；Frigate 的结论改由官方仓库内文档与插件源码核实。Gitee 查询本次没有得到可据以推荐的相关完整仓库，不将其列为已核实来源。此报告是筛选后的候选清单，不是全网穷尽列表，也不是板端部署认证。
