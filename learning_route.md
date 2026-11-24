# RK3568 边缘视觉检测与告警终端：项目选择与学习路线

编写日期：2026-11-23。依据：你的《江梓贤-嵌软简历》、当前工作区的板端维护记录，以及本次实际克隆和阅读的 Rockchip 官方源码。默认求职方向为嵌入式 Linux C/C++ 应用、边缘 AI 部署；如果目标是内核驱动/BSP，这个项目主要提供用户态工程证据，需要另补设备树、驱动和系统构建成果。

推荐以 **Rockchip 官方 RKNN Model Zoo 的 YOLOv8 C++ 示例**为基础，自己实现一个“基于 RK3568 NPU 的区域入侵检测与联动告警终端”。第一版使用固定视频，无需先购买摄像头。完成视频推理、并发控制、告警、存储和设备服务后，再接摄像头与 STM32。

## 1. 已为你下载的项目

| 项目 | 本次核实结果 |
|---|---|
| GitHub | [airockchip/rknn_model_zoo](https://github.com/airockchip/rknn_model_zoo) |
| 本地目录 | `C:\Users\Jiang ZiXian\Desktop\github\Embedded_learning\third_party\rknn_model_zoo` |
| 克隆方式 | `git clone --depth 1`，保留当前提交，未下载完整历史 |
| 分支 | `main` |
| 固定提交 | `837db8e992815ff8647eadb709f07067f4bc3a71` |
| 提交日期/说明 | 2026-10-13；`Update rknn_model_zoo to V2.5.0` |
| 学习入口 | `examples/yolov8/README.md`、`examples/yolov8/cpp/` |
| 芯片支持证据 | 根 README 与 YOLOv8 README 均明确列出 RK3568 |
| 主仓库许可证 | Apache-2.0；第三方库、模型和数据各自核对来源与许可证 |
| 本次已完成 | 本地克隆、源码与构建配置核对、学习路线编写 |
| 后续待做 | 下载模型、安装转换工具、编译、板端兼容验证、应用开发与性能测试 |

这是模型部署示例库，提供模型转换、C/Python 推理及后处理。当前选定的 `cpp/main.cc` 接受一个模型和一张图片，输出 `out.png`；它没有现成的视频采集、区域告警、事件数据库或设备管理后台。下文这些功能是你的二次开发目标。

主仓库代码开源不表示所有模型权重和依赖都自动采用同一许可证。复用时保留版权与许可证，记录修改来源；公开自己的代码前分别核对模型、数据和第三方组件的授权。

## 2. 为什么适合替换你简历里的第三个项目

你简历已有 RFSoC ISAC 原型和 STM32H7 多传感器时钟同步，分别能够承载 FPGA/高速链路与 MCU/实时外设的技术讨论。第三个 `Cpp-AI 应用 Http 服务框架` 更偏通用网络应用。建议保留前两个项目，将第三个升级为实际运行在 ARM 开发板上的设备项目。

| 你已有的能力 | 在新项目中如何复用 | 需要新增的证据 |
|---|---|---|
| C++11/17、Linux/GDB | RKNN 封装、RAII、线程生命周期、故障定位 | ARM64 可复现构建、资源释放与异常测试 |
| 共享内存、UDP、缓冲处理 | 视频帧所有权、生产消费队列、背压设计 | 队列长度和帧龄的实测曲线 |
| Reactor HTTP 服务 | 配置、状态、告警记录查询 API | 慢请求不阻塞推理、并发配置一致性 |
| STM32 UART/SPI/I2C、定时器/DMA | 后期告警执行端、串口协议、心跳 | 双端日志、超时重试和重复命令处理 |
| PyTorch 使用经历 | 理解模型输入输出、量化精度对照 | ONNX→RKNN 转换清单及精度回归 |

你不需要从 C++ 语法或目标检测论文开始重学。学习重心是：**把模型变成可维护的嵌入式应用，并解释正确性、时延、资源与可靠性的取舍。**

这属于结合你简历的工程建议，不是面试官偏好调查或录用概率结论。面试展示价值取决于你亲自实现并能解释的部分。

## 3. 项目范围与完成标准

### 3.1 第一版必须完成

1. 官方单张图片推理通过，保存版本、日志与输出。
2. 固定视频逐帧检测 `person`，检测框回映射正确。
3. 采集/推理通过有界队列解耦，可统计丢帧和排队时间。
4. 用户设置一个 ROI，人员持续进入区域后产生一条告警事件。
5. 保存截图和 SQLite 事件记录，提供状态与事件查询 HTTP API。
6. 能无预览运行，通过 systemd 启停，处理退出、输入故障和存储异常。
7. 提交可复现的功能、精度、性能与故障测试报告。

### 3.2 第一版之后再选择

- USB UVC 摄像头与拔插恢复。
- 800×1280 DSI 本地触控页面。
- STM32 串口 LED/蜂鸣器联动。
- RGA 预处理、MPP 硬件解码，以及有依据的缓冲共享优化。
- RTSP 输入、跟踪/越线统计、多路视频。

优先交付一条完整链路。WebRTC、多路模型、重新训练网络、大型前端和系统 OTA 不应同时成为第一版前置任务。

### 3.3 建议数据流

```text
固定视频 / 后期 UVC 摄像头
        │
        ▼
采集解码线程 ──► 有界帧队列 ──► 单推理线程
                                  │
                         CPU letterbox → RKNN → 后处理
                                  │
                           ROI 告警状态机
                                  │
                       有界事件队列 → SQLite / 截图
                                  │
                           HTTP API / 可选串口

预览：从结果中取最新帧，低频刷新；业务检测可独立于预览运行。
```

第一版一个 RKNN context 由一个推理线程持有。不要在没核实 API 并发约束之前让多个线程共享 context，也不要套用 RK3588 多核 NPU 调度示例。

## 4. 当前板卡约束与环境分工

### 4.1 已有记录与尚未核实的边界

当前维护记录指向 KICKPI K1Mini、RK3568、ARM64、约 4 GB RAM、Ubuntu 24.04.4、Linux 6.1.141，DSI 屏为 800×1280。近期已保留 GNOME，并将本地会话切换为 XFCE；用户确认触摸流畅，默认终端已改为 xfce4-terminal。详见工作区 `gnome.md` 第 13、14 节。

这些来自此前板端采集与维护记录，本次没有重新登录开发板；**尚未确认当前 NPU 内核驱动版本、Runtime 版本和所选模型能否组合运行**。根目录旧 `Rk3568.md` 中有另一时期的 Ubuntu 20/5.10 系统信息，不能直接当作当前 K1Mini 的软件栈。

上游明确支持 RK3568，是选择依据；是否适配你的镜像，必须以阶段 0/1 的实测为准。

### 4.2 三个环境各做什么

| 环境 | 用途 | 注意事项 |
|---|---|---|
| Windows | 编辑、Git、报告、SSH/SCP | 不能直接执行 Linux ARM64 ELF 或 `build-linux.sh` |
| x86_64 Linux / WSL2 Linux | RKNN-Toolkit2 模型转换、ONNX 对照、ARM64 交叉编译 | 先检查所选 Toolkit2 版本支持的 Linux/Python/wheel；WSL 也要实际验证安装与转换 |
| RK3568 Ubuntu | C++ Runtime 推理、视频输入、告警与服务 | 优先使用应用私有库，不全局覆盖板厂 Runtime 或图形库 |

不要因为板端 Ubuntu 24.04 自带 Python 3.12 就默认有匹配的 Lite2 wheel。第一版选 C++ 推理，把 Python 转换放在受支持的 PC 环境，减少板端 Python 依赖。

现有桌面是经过兼容性处理的 fbdev 显示路径，GNOME 曾受软件渲染开销影响。开发 AI 应用时保留现有 XFCE/Xorg/Mesa/Mali 配置，先无 GUI 验证。仅按需求安装缺少的包，不执行全量 `apt upgrade` 或用其他板卡固件替换当前系统。

### 4.3 第一道兼容性检查

在板端执行以下只读命令，保存输出到后续报告：

```bash
uname -a
cat /etc/os-release
uname -m
free -h
df -h
ldconfig -p | grep -E 'rknn|rga|mpp'
ls -l /dev/dri
ls /sys/class/devfreq
sudo dmesg | grep -Ei 'rknpu|rknn|iommu|rga'
```

按系统实际暴露的 sysfs/debugfs 路径补采驱动信息；未启用 debugfs 或工具缺失要如实记录。NPU 可能通过 DRM render 节点等接口暴露，不能以“没有 `/dev/rknpu`”单独判定 NPU 不可用。

在自己的诊断程序中通过 `rknn_query(..., RKNN_QUERY_SDK_VERSION, ...)` 记录 Runtime 与驱动版本；结合 `rknn_init`、模型加载日志和官方对应版本文档判断兼容性。当前单图示例会打印 tensor 信息，但没有主动查询 SDK 版本，需要你补充。

版本清单至少包含：SoC/板型、内核、驱动、Toolkit2、Runtime 实际加载路径和 SHA256、模型 SHA256、源码提交、编译器、输入尺寸及量化方式。模型、Toolkit2、Runtime、驱动是一组兼容关系，不能只比较“大版本数字是否一样”。

## 5. 源码按什么顺序读

以下路径均相对于本地 `third_party/rknn_model_zoo`，已经核对到本次固定提交。先读普通推理路径，再读优化路径。

| 顺序 | 文件 / 函数 | 阅读任务与产出 |
|---:|---|---|
| 1 | `examples/yolov8/README.md` | 写清模型来源、支持平台、输入输出、运行方法；注意 README 的 RK3588 命令只是示例 |
| 2 | `examples/yolov8/cpp/main.cc` | 画出参数→初始化→读图→推理→画框→保存→释放的调用图；当前 `argc` 必须为 3 |
| 3 | `examples/yolov8/cpp/yolov8.h`、`postprocess.h` | 列出 context、输入输出属性和检测结果结构；标记指针所有权 |
| 4 | `examples/yolov8/cpp/rknpu2/yolov8.cc` | 逐句读 `init_yolov8_model`、`inference_yolov8_model`、`release_yolov8_model` |
| 5 | `utils/image_utils.c`、`utils/common.h` | 读 `convert_image_with_letterbox`、`convert_image`，理解 RGB、padding、scale、图像缓冲格式 |
| 6 | `examples/yolov8/cpp/postprocess.cc` | 顺序读 `post_process`→`process_i8`/`process_fp32`→`compute_dfl`→`nms`→坐标还原 |
| 7 | `examples/yolov8/python/convert.py` | 理解 `rknn.config/load_onnx/build/export_rknn` 与校准集路径 |
| 8 | `examples/yolov8/python/yolov8.py` | 用 Python/ONNX 结果辅助核对预处理、输出解释与 C++ 检测结果 |
| 9 | `examples/yolov8/cpp/CMakeLists.txt`、`3rdparty/CMakeLists.txt`、`utils/CMakeLists.txt`、`build-linux.sh` | 追踪 RK3568 实际选中的源码、库路径、平台映射和安装目录 |
| 10 | `3rdparty/rknpu2/include/rknn_api.h` | 按需查 query、输入输出、错误码与内存 API，不必一开始通读全部接口 |
| 11 | `examples/yolov8/cpp/rknpu2/yolov8_zero_copy.cc` | 普通路径验收后比较内存分配、绑定与同步，记录实际减少了哪些拷贝 |

需要能口头复述的普通推理顺序：

```text
rknn_init
→ rknn_query 输入输出属性
→ RGB letterbox
→ rknn_inputs_set
→ rknn_run
→ rknn_outputs_get
→ post_process
→ rknn_outputs_release
→ 最终 rknn_destroy
```

### 5.1 读源码时做的三个小练习

1. 给模型加载、预处理、提交输入、执行、取输出、后处理分别加计时，说明哪些计时包含数据转换或同步等待。
2. 画资源表：模型文件缓冲、context、输入输出属性、预处理图像、RKNN 输出分别由谁申请、何时释放。
3. 在自己的封装中验证错误路径。当前 `inference_yolov8_model` 的若干早退分支发生在预处理缓冲分配后；当前 `main.cc` 多个失败分支最终仍走到 `return 0`。把这些当作检查资源释放、退出码和 RAII 的练习，不能因为是官方 demo 就跳过应用层错误处理。

本次保留上游源码原样，未代替你完成这些练习。

## 6. 第一次跑通：命令和容易踩的坑

以下是后续学习时执行的步骤，本次没有安装工具、下载权重或在板端运行。

### 6.1 Windows 查看固定版本

```powershell
Set-Location 'C:\Users\Jiang ZiXian\Desktop\github\Embedded_learning'
git -C third_party/rknn_model_zoo remote -v
git -C third_party/rknn_model_zoo log -1 --format='%H %cs %s'
git -C third_party/rknn_model_zoo status --short
```

仓库当前是独立的嵌套 Git 仓库，没有自动添加为父项目 submodule。不要直接对父项目执行 `git add .` 将它误当普通目录提交。后续自己开发时另建应用目录，通过依赖说明记录上游 URL/固定提交，或在明确需要时配置正式 submodule。

### 6.2 PC Linux 下载并转换模型

先按 [RKNN-Toolkit2 官方文档](https://github.com/airockchip/rknn-toolkit2/tree/master/doc) 安装与驱动/Runtime 配套的转换工具，核对 Python wheel 和依赖；本地 Model Zoo 的 V2.5.0 不等于你板上的软件已经是 V2.5.0。若板厂只支持较旧驱动，应选择对应 SDK 组合，并重新记录源码版本，而非直接覆盖系统库。

在已配置好的 Linux/WSL Python 环境中，进入本仓库根目录：

```bash
cd examples/yolov8/model
bash download_model.sh
cd ../python
python convert.py ../model/yolov8n.onnx rk3568 i8 ../model/yolov8n-rk3568-i8.rknn
```

该下载脚本当前只下载 `yolov8n.onnx`。下载地址来自上游脚本，未来可能变化；出现网络/下载失败应检查文件有效性，不要继续转换空文件。下载后记录模型哈希。

关键点：

- 选择 **rk3568**，第一版用较小的 YOLOv8n。
- RK3568 使用 `i8` 或 `fp` 路线；该脚本对 RK3568 的帮助提示并不是 `u8`。
- 默认校准列表为 `datasets/COCO/coco_subset_20.txt`，代码用相对路径，所以应在 `examples/yolov8/python` 下执行。
- 20 张示例图用于起步，不足以证明目标场景的量化精度；后续用独立采集、覆盖真实光照/距离的校准集，并与测试集隔离。
- `convert.py` 配置了 mean=0、std=255；理解归一化发生的位置，避免输入端再除一次 255。
- 上游提供的是经过调整的 YOLOv8 导出图，输出与原始 Ultralytics 模型有区别。不要随便下载一个同名 ONNX 就套用此后处理。
- `fp` 表示不启用该转换脚本的量化，具体执行精度以工具报告为准，不直接宣称所有算子 FP32。

### 6.3 PC Linux / WSL 交叉编译

先核对工具存在：`cmake --version`、`aarch64-linux-gnu-gcc --version`、`aarch64-linux-gnu-g++ --version`。相关子目录实际要求 CMake ≥3.15。可以使用上游文档推荐工具链，或与板端 sysroot/ABI 匹配且经过验证的交叉工具链；自行更换编译器后保留构建日志。

**建议第一次用显式 CMake 命令**。在仓库根目录执行以下 Bash 命令，可避免 Windows 用户名中的空格触发脚本未引用路径的问题：

```bash
cmake -S examples/yolov8/cpp -B build/yolov8-rk3568-cpu \
  -DCMAKE_SYSTEM_NAME=Linux \
  -DCMAKE_SYSTEM_PROCESSOR=aarch64 \
  -DCMAKE_C_COMPILER=aarch64-linux-gnu-gcc \
  -DCMAKE_CXX_COMPILER=aarch64-linux-gnu-g++ \
  -DTARGET_SOC=rk356x \
  -DCMAKE_BUILD_TYPE=Release \
  -DDISABLE_RGA=ON \
  -DDISABLE_LIBJPEG=ON \
  -DCMAKE_INSTALL_PREFIX="$PWD/install/rk356x_linux_aarch64/rknn_yolov8_demo"
cmake --build build/yolov8-rk3568-cpu --parallel 4
cmake --install build/yolov8-rk3568-cpu
```

说明：

- 模型转换目标是 `rk3568`，这里 CMake 的库选择条件使用 **rk356x**。官方 `build-linux.sh -t rk3568` 也会执行同样的映射。
- `DISABLE_RGA=ON` 选择 CPU 图像转换路径，先减少 RGA 驱动耦合；当前 CMake 仍会链接/安装 RGA 相关库，不能据此声称完全不依赖 RGA 包。
- `DISABLE_LIBJPEG=ON` 使用相应替代图像读写路径，减少后续与 OpenCV JPEG 库混用的冲突；它不是禁用读取所有 JPEG。
- CMake 配置时通过 glob 查找 `.rknn` 并生成安装规则，先转换再配置；模型后补时重新配置或明确复制模型到安装目录。
- 构建会同时生成普通和 zero-copy 可执行文件，第一轮只运行普通版本。

如果使用没有空格的 Linux 工作路径，也可参考官方脚本：

```bash
export GCC_COMPILER=aarch64-linux-gnu
bash build-linux.sh -t rk3568 -a aarch64 -d yolov8 -b Release -r ON -j
```

本次源码中 `getopts` 为 `:t:a:d:b:m:r:j`，所以 `-r` 实际需要一个参数，示例明确传 `ON`；`-j` 不带参数，含义是禁用 libjpeg，**不是 make 并行度**。`-m` 也有帮助与解析不一致的问题，ASan 可直接通过 CMake 配置。脚本会清理本次 demo 对应的既有安装目录，执行前确认里面没有自己手工存放的成果。

### 6.4 板端运行

构建产物位于 `install/rk356x_linux_aarch64/rknn_yolov8_demo`。将完整目录通过 SCP 复制到板端用户目录，例如 `/home/kickpi/apps/rknn_yolov8_demo`；源路径和当前 IP 根据实际环境填写。之前出现过多个网段，不能默认 `192.168.3.1` 就是板子。

先检查 ELF 架构、依赖和应用私有 Runtime 与驱动的兼容性，再执行：

```bash
cd /home/kickpi/apps/rknn_yolov8_demo
file ./rknn_yolov8_demo
LD_LIBRARY_PATH="$PWD/lib" ldd ./rknn_yolov8_demo
LD_LIBRARY_PATH="$PWD/lib" ./rknn_yolov8_demo \
  model/yolov8n-rk3568-i8.rknn model/bus.jpg
```

期望得到 tensor 属性、检测结果和 `out.png`。README 中示例分数不是验收要求，不同版本可能略有差异；应检查框的位置、类别及与对照结果的差别。此命令使用进程级私有库，不复制到 `/usr/lib` 或 `/usr/local/lib`。

随仓库带的 ARM64 Runtime 路径为 `3rdparty/rknpu2/Linux/aarch64/librknnrt.so`；本次 SHA256 为 `4B6CC575BEDF8952B13DB4B1190FA3B3D2AC213F00BE774FF6CCD19D651970C0`。这个哈希用于复现来源，不能证明与板端驱动兼容。

失败时先按日志分层：ELF/动态库→驱动初始化→模型兼容→输入格式→后处理；保留原始错误码。NPU 初始化未通过前，暂停视频集成，优先解决版本组合。

## 7. 按验收推进的详细路线

以下工时是针对你已有 C++/Linux/MCU 基础的粗略规划，单位为专注小时，不是保证工期。兼容性与新外设可能显著增加时间；每阶段通过验收后再推进。阶段 0–6 合计约 56–90 小时，系统化测试与报告还需另留时间，性能优化和额外外设另计。

### 阶段 0：固定环境与输入材料（4–8 小时）

**先决条件：** 能 SSH 访问当前板端，有可用 PC Linux/WSL 环境。

任务：完成第 4 节检查，建立版本清单；准备一段可合法使用的固定视频，记录 SHA256、时长、分辨率、编码、帧率，选出有人/无人/遮挡/边界场景；确认当前桌面和磁盘空间。

交付：`docs/environment.md`、输入清单、模型来源清单。不要将账号口令或个人网络认证信息写进仓库。

验收：明确 PC 和板端各装什么；能定位实际 Runtime；将未核实项单列。NPU 不可用时先做 PC 上的队列、状态机和存储开发，RK3568 推理里程碑仍保持未完成。

### 阶段 1：单张图片基线（6–10 小时）

**先决条件：** 环境与软件版本组合已确定。

任务：下载/转换 YOLOv8n，交叉编译普通 demo；保存构建命令、tensor 属性、检测输出和 `out.png`；读完源码顺序 1–4，补 SDK 版本查询与返回码记录。

交付：`reports/baseline-image/`，包含输入/模型哈希、日志、输出、复现步骤。

验收：不用桌面预览也能推理；重复运行结果在预先定义的允许差异内；错误模型/不存在图片能被识别为失败，不能仅凭进程退出码 0 判成功。能解释 context 初始化一次、每张图只提交输入的原因。

### 阶段 2：输入输出与精度核对（8–12 小时）

**先决条件：** 单图结果正确，有 PC ONNX 对照环境。

任务：读完预处理、后处理、转换脚本；记录 tensor 的维度、布局、类型、scale 和 zero-point；手算一次 letterbox 和坐标还原；对同一批图比较 ONNX 与 RKNN。

建议练习：对 1280×720 图像输入 640×640，理想几何下 scale=0.5，缩放为 640×360，垂直补边总量 280；结合当前实现的对齐与取整核对实际 padding。还原通常为 `x=(x_model-x_pad)/scale`、`y=(y_model-y_pad)/scale`，最后按原图范围处理边界。

量化基础：反量化可写为 `real=(q-zp)*scale`。理解模型量化类型与 API 输入 `UINT8/NHWC` 是不同层面的概念，不能看到 INT8 模型就强行把所有输入缓冲改为 int8。

交付：`docs/tensor-contract.md`、`reports/accuracy-baseline.md`，保留代表图、错误案例和匹配方法。

验收：通道不颠倒、画框不整体偏移；可以说明 DFL、置信度过滤和按类别 NMS 的作用。若比较精度下降，先分离预处理差异、导出图差异、量化差异，不直接归因于 NPU。

### 阶段 3：固定视频单线程应用（8–12 小时）

**先决条件：** 单图和坐标契约已通过。

任务：在自己的应用中用 OpenCV `VideoCapture` 接文件，先串行读帧→RGB 转换→推理→叠框；模型只初始化一次。封装 `Detector`，资源通过 RAII 管理；定义统一 `Frame` 和 `Detection`。

文件输入支持两种模式：离线逐帧完整分析；按文件 PTS 节奏回放模拟实时源。两者分开测，不能拿离线读取速度当摄像头实时表现。

交付：一个命令行程序，支持 `--input`、`--model`、`--headless`、结果输出和日志级别。OpenCV 是本阶段新增依赖，原始单图 demo 没有要求你先装完整 OpenCV。

验收：短视频处理到 EOF 正常退出；保存叠框结果验证边界；SIGINT 能释放资源；无显示环境照常运行。空文件、损坏文件、模型路径错误有明确日志和非零退出码。

### 阶段 4：有界并发与时延控制（10–16 小时）

**先决条件：** 串行视频功能稳定，已有阶段计时。

任务：实现采集线程＋单推理线程，使用 `std::mutex`、`std::condition_variable` 和有上限的队列；定义关闭语义，区分 EOF、主动停止、输入故障。持有帧数据直到消费者结束，防止 `cv::Mat` 复用导致画面串帧。

默认实时模式队列容量可从 2 开始实验，满时丢最旧待处理帧以保留新鲜度；离线模式改为阻塞生产者以完整处理。两种策略都要能解释业务代价。

每帧至少有 `frame_id`、源 PTS（如有）、接收时间、出入队时间、推理/后处理完成时间。耗时用 monotonic/`steady_clock`，事件显示时间另存 wall clock。

交付：队列实现与行为说明、串行/并行对照 CSV、正常退出和故障退出日志。

验收：人为把消费者变慢，队列仍不超过上限；实时帧龄不随运行时长不断增长；离线计数完整。阻塞等待者能在关闭时唤醒，线程 `join` 不挂死；生产、消费、丢弃、在队及在途帧按定义对账。不要在持锁时执行推理或磁盘写入。

### 阶段 5：ROI 告警与事件存储（10–16 小时）

**先决条件：** 帧时间戳、坐标和队列语义稳定。

第一版定义为“区域占用告警”：只判断是否有 person 检测框的底边中心点进入归一化 ROI。明确这不是带身份的多目标跟踪，也不承诺每个人独立停留时间。

实现状态机：

```text
IDLE --区域内检测到人--> CANDIDATE
CANDIDATE --持续满足 dwell_ms--> ACTIVE（创建一次事件）
CANDIDATE --超出允许漏检时间--> IDLE
ACTIVE --持续无人达到 clear_ms--> COOLDOWN
COOLDOWN --冷却结束且区域清空--> IDLE
```

漏检容忍、最大帧间隔、超时和重新布防条件写进配置。若输入断开，不得继续以旧结果累计停留时长；进入 source-lost 状态并重置或暂停计时，恢复策略要明确。

SQLite 保存 event_id、起止时间、ROI、规则版本、类别、置信度、截图引用、源信息。SQLite 写入和截图放到有界事件通道中；持续占用只创建一次，避免每帧写库。

交付：规则配置、状态机说明、测试视频的预期事件时间段、数据库 schema 与容量保留策略。

验收：使用注入的检测结果和可控时钟验证短暂路过、持续入侵、抖动漏检、多人、断流、重新进入、跨冷却时间等场景；将规则测试与模型误检分开。磁盘写满时服务有明确降级/丢弃计数，不能无限堆积内存。数据库记录与截图的先后顺序、失败补偿和遗留文件清理有约定。

### 阶段 6：复用 HTTP 服务与设备交付（10–16 小时）

**先决条件：** 后台检测与事件存储不依赖 UI 能运行。

优先把已有 C++ HTTP 框架中稳定的路由、日志和连接管理复用为设备接口：

| 建议接口 | 作用 | 关键设计 |
|---|---|---|
| `GET /api/status` | 版本、输入状态、已处理/丢帧、队列深度、近期错误 | 状态快照，不阻塞推理 |
| `GET /api/events?after_id=...&limit=...` | 事件分页 | limit 上限、固定排序、参数校验 |
| `GET /api/events/{id}/snapshot` | 查看截图 | 从数据库查文件，避免任意文件路径访问 |
| `GET /api/config` | 查看生效配置和版本 | 与日志中的规则版本一致 |
| `PUT /api/config` | 修改 ROI/阈值/停留时间 | 校验成功后整体替换，失败保持原配置 |

第一版不实现运行中热换 RKNN 模型；先让配置热更新只覆盖 ROI/阈值等业务参数。HTTP 请求线程写入新配置快照，推理/规则线程在明确边界采纳，事件记录配置版本。

提供 systemd unit、运行用户、工作目录、私有库加载、日志与数据路径说明。GUI 作为独立客户端，800×1280 页面大按钮、低频预览，避免拖慢后台；用户服务或显示会话绑定由实际部署决定。

交付：API 文档、部署包、配置示例、安装/回退说明、systemd 文件。

验收：SSH 下可独立启动；终止进程可按策略恢复；SIGTERM 能结束线程；非法配置不破坏当前运行；慢 HTTP 客户端不造成检测队列无限增长。接口对外开放前增加必要认证和访问限制，测试先使用回环/受控局域网。

### 阶段 7：摄像头与真实设备可靠性（8–16 小时，可在第一版之后）

**先决条件：** 文件源完整验收，实际拥有 USB UVC 摄像头。

先用 `v4l2-ctl --list-devices` 和设备格式枚举确认摄像头，核对分辨率、帧率、MJPEG/YUYV 和后端，不默认任意 `/dev/video0` 都是采集设备。

为视频源定义 `OPENING/RUNNING/RECONNECTING/STOPPED`，采用有上限的退避重连；摄像头拔插后旧结果不能继续触发告警。阻塞读取要有退出办法，必要时把故障采集隔离成可重启工作进程。

交付：插拔与恢复日志、设备重新编号策略、长稳原始数据。

验收：多次插拔能恢复，服务无僵尸线程；没有摄像头时仍能用固定文件完成可重复演示。DSI 预览开启/关闭分别测量资源，证明交互不影响主链路的边界。

### 阶段 8：只选一到两个有证据的优化（12–24 小时，可选）

**先决条件：** 已经有稳定基线和逐阶段耗时，知道瓶颈在哪里。

按测量结果选择，而非同时堆组件：

1. CPU 预处理占比较高：比较当前 CPU 路径与 RGA，核对 RGB/NV12、stride、对齐、插值与 padding；允许像素差异时也要验证检测精度。
2. 解码占比较高：对同一压缩视频比较 CPU 解码与 MPP，保留解码缓冲的格式与生命周期说明；MPP 是单独媒体组件，不是 RKNN 的自动功能。
3. 分配/拷贝显著：复用输入缓冲，再阅读 zero-copy 示例；说明哪些边界仍复制、缓存同步如何完成。应用层内存绑定不等于解码→预处理→NPU→显示全部零拷贝。
4. GUI 占比较高：降低预览尺寸/刷新频率，业务保持原频率；单独量化 GUI 成本。

交付：同条件 A/B 报告、输出一致性/精度结果、瓶颈解释。优化无收益也能形成有效结论，保留原因与退回方案。

### 阶段 9：STM32 告警执行端（8–16 小时，可选）

**先决条件：** Linux 告警已经稳定，有空闲 MCU 与匹配电平的串口连接。

建议先复用你熟悉的 UART，而不是重写时钟同步项目。协议包含版本、类型、长度、sequence、payload、CRC；Linux 发送告警、解除、心跳，STM32 应答并驱动 LED/蜂鸣器。

定义重试、应答超时、断连状态、重复命令幂等。保证 CRC 错误帧、截断帧、粘包、乱序/重复应答有可解释行为。Linux 推理线程不等待串口 ACK，用独立有界命令通道。

交付：协议文档、双端代码、逻辑分析仪/串口日志、故障注入记录。

验收：串口断开不阻塞推理；重试不重复鸣叫；MCU 复位后可重新同步状态。只有实际实现并测试后，项目标题才写“硬件联动”。

## 8. 建议自己的工程如何组织

上游保留为对照，个人应用建议另放工作区 `projects/rk3568-vision-alarm/`。以下是目标结构，本次尚未创建这些业务文件：

```text
projects/rk3568-vision-alarm/
├── CMakeLists.txt
├── cmake/                  # 工具链、依赖版本和路径
├── src/
│   ├── detector/           # RKNN context / 预后处理适配
│   ├── pipeline/           # Frame、队列、时间戳、退出协调
│   ├── source/             # 文件/UVC，后期 RTSP
│   ├── rules/              # ROI 与告警状态机
│   ├── storage/            # SQLite、截图、保留策略
│   ├── api/                # 复用已有 HTTP 模块
│   └── device/             # 后期串口执行端
├── configs/
├── deploy/                 # systemd、启动与回退
├── tests/                  # 队列/状态机/配置及故障场景
├── tools/                  # 测量、采样、结果汇总
├── docs/                   # 架构、协议、环境、依赖来源
└── reports/                # 原始 CSV、精度、性能、长稳
```

不要把大型权重、测试视频、数据库、构建目录和密码直接提交到代码仓库。通过来源、哈希和获取说明复现大文件；保存上游固定提交及自己修改的 patch/提交历史。若搬入上游源文件，保留来源和版权声明。

## 9. 性能、正确性与可靠性怎么测

### 9.1 每个实验都记录的条件

模型/视频哈希、输入尺寸、编译优化级别、Toolkit2/Runtime/驱动、CPU/NPU 频率策略、散热、温度、预热方式、预览开关、输入节奏、队列策略、日志级别、实验时长。多轮实验保存原始数据，报告样本数与失败/丢弃比例。

| 指标 | 建议定义 | 防止误读 |
|---|---|---|
| 推理耗时 | 单独记录 `rknn_run` 调用耗时，必要时补 SDK profiling | API 边界可能包含同步等待，不能直接当纯硬件执行时间 |
| 检测链路时延 | `t_postprocess_done - t_frame_received` | 包含排队/预处理；接收前的传感器、编码、网络延迟不在此定义内 |
| 告警响应时延 | 条件达到 dwell 门槛至事件提交完成 | 与检测耗时和业务停留时间分别报告 |
| P50/P95 | 按同一指标、有效样本排序求分位数 | 只统计处理帧会隐藏丢帧，必须同时给丢帧率和帧龄 |
| 吞吐 | 完成推理帧数 / 实际测量时间 | 摄像头输入 FPS、推理 FPS、预览 FPS 分开 |
| 资源 | 进程 CPU、RSS、温度、队列深度、存储增长 | 多核 CPU 可能超过 100%，报告工具和口径 |
| 检测精度 | 标注集上的 precision/recall；需要时规范计算 mAP | 几张示例图不能宣称获得 COCO mAP |
| 事件正确性 | 预期事件与实际事件的匹配、漏报/误报/重复数 | 模型准确率和规则准确性分开评价 |

同一进程内时间差用单调时钟。文件 PTS、设备采集时间、程序接收时间和屏幕实际呈现时间不能混为一个时间戳。如果没有测到显示完成或物理采集时刻，就把指标写成“接收到后处理完成时延”，不要直接叫完整物理端到端延迟。

### 9.2 建议对照顺序

1. 串行视频 vs 有界队列视频：相同模型和源节奏，比较帧龄、丢帧及吞吐。
2. CPU letterbox vs RGA：保持模型、输入、后处理和采样条件一致，检查精度与性能。
3. 不显示 vs 低频预览：量化当前板端桌面的额外开销。
4. RKNN INT8 vs PC/可用 CPU 基线：区分跨设备对照和同板对照，解释模型图、精度与软件差异，不能把 PC ONNX 吞吐直接称为板端 CPU 性能。

先证明正确，再比较速度。上游 README 的模型 benchmark 只能作背景参考，不是你的端到端成绩。

### 9.3 必做故障场景

- 输入 EOF、文件损坏、摄像头掉线；恢复后不沿用过期检测结果。
- 推理消费者变慢；队列和内存有上限。
- SQLite 锁/写入失败、截图失败、磁盘配额耗尽；故障可见且不无限重试堆积。
- 请求参数异常、配置格式错误、并发修改；保留已生效配置。
- SIGINT/SIGTERM、进程异常退出、服务重启；状态可解释、重复事件有策略。
- 长时间运行；观察 RSS、温度、帧龄和事件计数，不只截取一次 `top`。

先短测定位问题，再按自己的演示/部署目标选取例如 8 小时、24 小时长稳实验。这些是后续实验计划，不是已完成成绩。不要为了测试磁盘写满而写满系统根分区，使用受限测试目录/配额或可注入的存储失败接口。

## 10. 工期取舍与每阶段的停点

| 可用投入 | 优先完成 | 暂缓 |
|---|---|---|
| 近期时间很少 | 阶段 0–3，形成可靠单图/文件推理与源码理解 | GUI、硬件联动、多媒体优化 |
| 希望形成可写简历的第一版 | 阶段 0–6，并完成相关测试与报告 | 多路、RTSP、MPP、跟踪 |
| 希望强化嵌入式特征 | 第一版后增加阶段 7，再按条件加阶段 9 | 大型 Web 前端 |
| 希望强化性能方向 | 第一版后按瓶颈做阶段 8 | 没有测量支持的“零拷贝”改造 |

每次学习按“读一个模块→做一个小实验→保存证据→写一页解释”推进。某阶段验收未通过时先缩小范围定位问题，不用不断叠加新库掩盖旧问题。

## 11. 面试时应该能回答什么

| 问题 | 你应该拿出的说明或证据 |
|---|---|
| 单次 NPU 推理快，为什么画面仍延迟？ | 分段计时、帧龄曲线、队列与 GUI/解码开销 |
| 为什么队列容量选 2，为什么丢旧帧？ | 容量对照、实时和离线模式差异；承认短暂事件可能因丢帧漏掉 |
| INT8 精度变差怎么定位？ | 同图预处理核对、校准集/测试集隔离、FP/INT8 对照 |
| 模型输出为何不能直接当框坐标？ | tensor contract、DFL、stride、NMS、letterbox 还原 |
| 为什么没先做零拷贝？ | 瓶颈测量、缓冲所有权图、同步与正确性成本 |
| 图像为什么会花屏/颜色异常？ | BGR/RGB、NV12/NV21、stride/对齐和生命周期的排查顺序 |
| 多人停留怎么算？ | 第一版是区域占用；个人停留需要跟踪身份与丢失策略 |
| 设备断流、HTTP 很慢、磁盘满怎么办？ | 状态机、隔离通道、有界队列和故障注入日志 |
| 你与官方 demo 的区别是什么？ | 自己的提交、模块、测试与报告；明确模型和推理 SDK 来自上游 |
| 与前两个简历项目有什么联系？ | Linux 帧管线与 RFSoC 缓冲经验，串口联动与 MCU 能力；避免重复包装同一工作 |

## 12. 简历如何写：完成后再填写

建议标题：**基于 RK3568 NPU 的边缘视觉检测与告警终端**。若硬件联动尚未完成，标题先不加“硬件联动”。

以下是未来完成后的写法模板，方括号均须由实际证据替换，不能原样当成已完成经历：

> 基于 Rockchip RKNN Model Zoo 完成 YOLOv8n 在 RK3568 上的 C++ 部署，设计采集/推理/存储解耦管线和有界帧队列，实现区域入侵判断、事件持久化及 HTTP 配置/状态接口。
>
> 对固定模型与视频建立分段计时和精度回归，比较 [实际实现的方案]；在 [输入分辨率/节奏、预览开关] 条件下，测得 [按定义的时延 P50/P95]、[吞吐/丢帧] 和 [资源占用]，并解释优化代价。
>
> 实现 [实际完成的掉线恢复、容量限制、systemd 部署或串口协议]，完成 [实际时长] 稳定性及 [具体故障] 测试，保留日志、原始数据和复现脚本。

不要写尚未实测的 FPS、24 小时稳定、准确率提升或全链路零拷贝。求职时可以写“进行中”，准确列出已完成的里程碑。

## 13. 今天从哪里开始

1. 打开本地 `examples/yolov8/cpp/main.cc` 和 `rknpu2/yolov8.cc`，画一张初始化/推理/释放流程图。
2. 确认当前板 IP，完成第 4.3 节的只读检查，优先补齐驱动/Runtime 信息。
3. 对照支持矩阵选择 PC Toolkit2 环境，固定模型和版本组合。
4. 按第 6 节跑通单图，收集第一份环境、日志和输出；还没跑通时先不接 UI 和摄像头。
5. 单图通过后另建个人应用，按阶段 3 开始文件视频，再逐步替换简历第三个项目。

## 14. 对照资料

本次核心结论来自已克隆提交的源码与文档；下面的固定提交链接可避免未来 main 变化导致阅读不一致。

- [固定版本仓库](https://github.com/airockchip/rknn_model_zoo/tree/837db8e992815ff8647eadb709f07067f4bc3a71)
- [YOLOv8 说明与模型输出差异](https://github.com/airockchip/rknn_model_zoo/blob/837db8e992815ff8647eadb709f07067f4bc3a71/examples/yolov8/README.md)
- [C++ 主程序](https://github.com/airockchip/rknn_model_zoo/blob/837db8e992815ff8647eadb709f07067f4bc3a71/examples/yolov8/cpp/main.cc)
- [普通 RKNPU2 推理实现](https://github.com/airockchip/rknn_model_zoo/blob/837db8e992815ff8647eadb709f07067f4bc3a71/examples/yolov8/cpp/rknpu2/yolov8.cc)
- [后处理](https://github.com/airockchip/rknn_model_zoo/blob/837db8e992815ff8647eadb709f07067f4bc3a71/examples/yolov8/cpp/postprocess.cc)
- [转换脚本](https://github.com/airockchip/rknn_model_zoo/blob/837db8e992815ff8647eadb709f07067f4bc3a71/examples/yolov8/python/convert.py)
- [官方交叉编译说明](https://github.com/airockchip/rknn_model_zoo/blob/837db8e992815ff8647eadb709f07067f4bc3a71/docs/Compilation_Environment_Setup_Guide.md)
- [构建脚本](https://github.com/airockchip/rknn_model_zoo/blob/837db8e992815ff8647eadb709f07067f4bc3a71/build-linux.sh)
- [许可证](https://github.com/airockchip/rknn_model_zoo/blob/837db8e992815ff8647eadb709f07067f4bc3a71/LICENSE)
- [RKNN-Toolkit2](https://github.com/airockchip/rknn-toolkit2)：安装、版本配套与 API 资料入口，实际使用前选择相应版本文档。
- [Rockchip 调整的 YOLOv8 导出来源](https://github.com/airockchip/ultralytics_yolov8)：由已读上游 README 指向，训练/导出属于后续任务。
- [MPP](https://github.com/rockchip-linux/mpp)、[librga](https://github.com/airockchip/librga)：后续优化的官方组件入口，本次未为它们执行克隆或板端兼容测试。

