# 神经网络部署到 FPGA：开源项目、课程、书籍与实战路线

整理与在线核对日期：2026-11-18。

本文主要讨论**推理部署**：在 PC/GPU 上训练网络，再将模型转换为 FPGA 上的计算硬件或加速器可执行模型。FPGA 上训练神经网络属于另一类问题，不是这里的入门目标。

结合你已有的 Verilog、Zynq/RFSoC、PS/PL 协同和 AXI 开发经历，建议先选 **hls4ml 或 FINN 中的一条路线完成上板**，再深入算子和加速器架构。最值得补的是量化、定点数误差、神经网络数据流和端到端性能评估。

资料核对方式：读取项目官方文档、课程主页、出版社/作者页面，以及 GitHub API 返回的仓库信息和 README。GitHub 普通网页本次多次连接失败，已通过官方 API 核对主要仓库；不把搜索摘要当作项目实测结论。文中视频链接来自课程或项目主页，未逐段观看全部视频；本次没有实际综合或上板复现这些项目。

## 一、先选路线：你究竟想学哪种“部署”

| 路线 | 实际做什么 | 典型资源 | 优点 | 主要限制 |
|---|---|---|---|---|
| 模型生成专用硬件 | 将网络转换成逐层定制的数据通路 | hls4ml、FINN、fpgaConvNet、NNgen | 适合研究低延迟、量化、资源与并行度取舍 | 模型算子、形状、量化方式和接口受工具支持范围限制 |
| 在现成推理引擎上运行模型 | 在 PL 中集成 DPU，模型编译为其可执行形式 | Vitis AI | 较快建立图像推理应用，软硬件分工清楚 | 需要匹配 DPU 架构、模型编译工具、运行库和板级平台 |
| 自己编写算子/加速器 | 用 HLS 或 RTL 实现卷积、矩阵乘、激活和缓存 | AMD HLS 示例、UCSD BNN 实验、PipeCNN | 能真正理解瓶颈，适合形成自己的硬件设计成果 | 需要自己完成数值验证、存储设计、接口和系统集成 |
| 研究处理器与神经网络协同 | RISC-V 软核加指令或连接脉动阵列 | CFU Playground、Gemmini | 适合计算机体系结构与软硬件协同优化 | 不等于把一个 IP 直接接到 Zynq 的 Arm PS 上 |
| 阅读完整加速器 RTL | 研究卷积引擎、片上缓存、DMA 和控制器 | NVDLA | 架构与验证资料较完整 | 原始设计面向加速器 IP，移植到 FPGA 的工作量较大 |

对你最合适的顺序：

1. 用 hls4ml 的小 MLP/CNN 跑通浮点参考、定点仿真、综合和板端推理。
2. 用 FINN + Brevitas 理解 QAT、低比特计算和 PE/SIMD 并行度。
3. 自己实现一个 INT8 矩阵乘或卷积模块，与工具生成版本比较。
4. 将小型 1D CNN 接入 RFSoC 数据链路，做调制识别或信号分类。

这是一条建议路线，不需要先把下面所有项目学完。

## 二、优先推荐的开源项目

### 1. hls4ml：模型到 HLS 的首选入门路线

- [GitHub 仓库](https://github.com/fastmachinelearning/hls4ml)
- [官方文档](https://fastmachinelearning.org/hls4ml/)
- [功能支持矩阵](https://fastmachinelearning.org/hls4ml/intro/status.html)
- [安装与 Quick Start](https://fastmachinelearning.org/hls4ml/intro/setup.html)
- [官方教程仓库](https://github.com/fastmachinelearning/hls4ml-tutorial)

**它做什么：**读取支持的 Keras、PyTorch、ONNX/QONNX 等模型表示，生成 HLS 工程，再通过相应厂商工具得到 RTL/IP 和硬件实现。不同前端、后端的支持能力并不相同。

**为什么适合你：**你已经了解 PS/PL 和 AXI，可以把精力放在“网络怎样变成硬件”，而不必从全套 SoC 开发重新开始。小型 MLP、1D/2D CNN 更适合作为第一步。

重点学习：

- `Precision`：权重、激活、中间累加的位宽与整数位如何配置。
- `ReuseFactor`：如何通过复用计算资源，在吞吐、延迟和资源之间取舍。
- `io_parallel` 与 `io_stream`：接口组织及内部实现的差别。
- 浮点模型、C 仿真、RTL 协同仿真、板端结果如何逐级比较。
- FIFO 深度、层间速率不匹配和片上存储限制。

建议第一个实验：用一个小 MLP，分别修改精度和复用因子，输出“精度—延迟—DSP/LUT/BRAM”对比表。确认数值正确后再尝试 CNN。

**已核对的限制：**

- 本次文档显示为 hls4ml 1.3.0；它不是能直接处理任意 PyTorch 模型的通用编译器。
- [PyTorch 前端](https://fastmachinelearning.org/hls4ml/frontend/pytorch.html)依赖 FX 符号追踪，要求图可追踪、算子受支持；文档明确提示其能力尚未与 Keras 前端完全一致。
- Brevitas 量化模型目前不能直接从该前端导入，应按文档导出 ONNX/QONNX，再走对应流程。
- PyTorch 常见的 channels-first 与工具内部 channels-last 布局需要检查；流式接口的输入转置尤其不能忽略。
- 当前[状态页](https://fastmachinelearning.org/hls4ml/intro/status.html)以 Linux 为主要支持环境，Windows/macOS 不属于正式支持的综合环境。你可以在 Windows 上编辑代码，构建环境优先选项目验证过的 Linux。

**板级部署：**[VivadoAccelerator 文档](https://fastmachinelearning.org/hls4ml/backend/accelerator.html)列出了 PYNQ-Z2、ZCU102 等示例。支持某器件生成 IP，不等于已经为你的 RFSoC 板准备好完整工程和镜像。

推荐程度：第一梯队。适合快速建立完整部署认知。

### 2. FINN：低比特量化网络与定制数据流加速器

- [GitHub 仓库](https://github.com/Xilinx/finn)
- [项目主页](https://xilinx.github.io/finn/)
- [官方文档](https://finn.readthedocs.io/en/latest/)
- [入门与硬件支持](https://finn.readthedocs.io/en/latest/getting_started.html)
- [教程索引](https://finn.readthedocs.io/en/latest/tutorials.html)

**它做什么：**围绕量化神经网络，为各层生成定制的流式硬件组件，再连接成网络对应的数据流架构。重点是模型和硬件共同设计，而不是让所有现成网络不经调整地跑起来。

典型流程：

```text
PyTorch + Brevitas 训练量化网络
    → 导出 QONNX
    → 转换为 FINN 所需表示
    → 图变换与硬件层转换
    → 选择并行度、配置 FIFO
    → 生成并验证硬件
    → 集成 DMA/板级系统并上板
```

重点学习：

- 权重和激活位宽分别如何影响精度与资源。
- `PE`、`SIMD` 和 folding：如何控制同一层的并行度。
- 多层流水线中最慢的一层如何限制整体吞吐。
- Python 执行、C++ 仿真和 RTL 仿真的逐级验证。
- AXI-Stream 数据打包、DMA 和板端驱动。

**当前推荐的教程起点：**官方教程页目前将 `end2end_example/cybersecurity` 的量化 MLP 训练与部署列为搭建自定义加速器的推荐起点。`bnn-pynq` 系列更适合理解编译器中间步骤和调试，不应直接假定它就是当前最推荐的新工程模板。

**板卡和版本差异很重要：**

- 当前 Getting Started 文档说明：随工具迁移到 Vivado 2024.2，PYNQ-Z1/Z2 已退出官方测试与支持；列出的完整部署平台包括 AUP-ZU3、Kria SOM、Ultra96、ZCU102、ZCU104 和部分 Alveo 平台。
- 这与旧版 FINN 示例里仍列出 PYNQ-Z1 不矛盾：旧示例对应的是旧版本组合。
- 为其他 Xilinx/AMD 器件生成可集成的 AXI-Stream IP，与自动生成适配该板的完整 bitstream/驱动，是两种不同支持层次。
- Docker 仍是文档推荐的主要方式；最新文档也给出本地安装路径。不要只依据较旧 README 中的措辞判断当前全部安装能力。

推荐程度：第一梯队。与你的 Verilog、流水线、RFSoC 背景非常贴近。

### 3. FINN Examples：先看一个已经跑起来的系统

- [示例仓库](https://github.com/Xilinx/finn-examples)

仓库提供部分网络的预构建 bitstream、PYNQ Python 驱动、Notebook 和重建资料。

README 中列出的代表性示例包括：

| 示例 | 学习价值 | README 列出的部分平台 |
|---|---|---|
| MNIST 小型全连接网络 | 理解低比特输入、输出和基本部署 | PYNQ-Z1、ZCU104、Ultra96、U250 |
| CIFAR-10 CNV | 理解量化卷积网络和层间数据流 | PYNQ-Z1、ZCU104、Ultra96、U250 |
| ImageNet MobileNet-v1/ResNet-50 | 观察较大网络的实现组织 | U250 |
| RadioML 2018、1D CNN | 调制识别，与通信/RFSoC 项目相关 | ZCU104 |

**对你尤其值得关注的是 RadioML 示例。**可以先研究离线 IQ 样本如何打包、量化和分类，再考虑连接 RFSoC 实时采样链路。

注意：该仓库 README 当前展示的示例环境包括 FINN v0.10.1、PYNQ v3.0.1、Vivado/Vitis 2022.2。它不应与当前 FINN 主线的环境要求直接混用；复现前按所选示例锁定版本。ZCU104 示例的 bitstream 也不能直接下载到其他 RFSoC 器件上使用。

推荐程度：第一梯队中的辅助资源。适合先建立系统全貌，再回到 FINN 学构建流程。

### 4. Brevitas：为 FPGA 准备量化模型

- [GitHub 仓库](https://github.com/Xilinx/brevitas)
- [官方文档](https://xilinx.github.io/brevitas/)

Brevitas 是基于 PyTorch 的神经网络量化库，支持 PTQ 和 QAT。它负责模型侧的量化表达与训练，**本身不是从模型到 FPGA bitstream 的完整工具链**。

重点学习：

- PTQ：训练后使用代表性数据进行量化校准。
- QAT：在训练中模拟量化，使模型适应有限位宽。
- 权重、输入、输出和偏置可以有不同量化设置。
- scale、zero-point、舍入和饱和规则必须能由目标硬件表示。
- 能够导出 ONNX，不意味着后端一定支持其中所有量化算子和参数组合。

建议实验：对同一小网络比较浮点、8 bit、4 bit 等配置的测试集表现，再选择目标后端实际支持的方案进行部署。不要同时随意升级 Brevitas、QONNX 和 FINN，先使用对应版本验证过的组合。

推荐程度：准备深入 FINN 时必学。

### 5. fpgaConvNet：学习 CNN 加速器设计空间探索

- [官方项目主页](https://icidsl.github.io/fpgaconvnet-website/)
- [教程仓库](https://github.com/AlexMontgomerie/fpgaconvnet-tutorial)

它围绕“给定 CNN 和 FPGA 资源约束，如何找到较好的加速器结构”组织工具流程。

教程 README 将系统拆成模型、性能/资源建模、设计空间探索和 HLS 生成等模块，并链接到：

- [fpgaconvnet-model](https://github.com/AlexMontgomerie/fpgaconvnet-model)：模型解析、资源和性能估算。
- [fpgaconvnet-optimiser](https://github.com/AlexMontgomerie/fpgaconvnet-optimiser)：探索硬件配置。
- [fpgaconvnet-hls](https://github.com/AlexMontgomerie/fpgaconvnet-hls)：从配置生成实现。

上述子仓库链接已在教程 README 中核对；本次没有逐项复现其构建流程。

适合研究：不同层的计算量为何不均衡、片上缓存如何约束并行度、估算与综合实测为什么存在差距。推荐先做教程中的 `0_get_started` 和 `1_simple_end_to_end`，再阅读优化器。

**限制：**研究工具链不是任意 CNN 的一键转换器。需核对模型支持、平台配置、依赖版本，并用实际综合结果校验性能估算。

推荐程度：第二梯队。适合已经跑通一种部署流程后深入研究。

### 6. NNgen：从 Python/ONNX 生成 Verilog 加速器

- [GitHub 仓库](https://github.com/NNgen/nngen)

NNgen 为给定网络生成 Verilog HDL 和 IP-XACT 打包的 IP。后端基于 Veriloggen，生成的系统包含计算、片上存储、DMA 和控制部分。

你可以从小型全连接网络或 `matmul` 示例开始，观察：

- 网络算子怎样转成模块与控制逻辑。
- 权重和激活如何分配地址。
- 定点缩放、累加位宽和输出截断如何实现。
- 生成的 DMA/控制接口如何与 PS 交互。

**限制：**GitHub API 本次显示最近推送在 2023 年，README 中包含旧版本依赖和示例 API。它适合读源码、研究生成机制；若追求最快完成第一个部署，优先 hls4ml/FINN。

推荐程度：第二梯队，偏硬件生成与源码阅读。

### 7. PipeCNN：看懂传统 CNN 加速器的完整实现

- [GitHub 仓库](https://github.com/doonny/PipeCNN)

PipeCNN 是基于 OpenCL 的 FPGA CNN 加速器项目，README 列出了 Intel OpenCL SDK 和 Xilinx Vitis 两种流程，以及 VGG-16、ResNet-50 等模型资料。

适合学习：卷积的向量化、流水线组织、数据搬运、计算与访存重叠，以及资源参数对性能的影响。

README 列出的已测试平台包括 Arria-10、U50、ZCU102、ZC706 等；列出工具版本包括 Intel OpenCL SDK Pro 20.1、Vitis 2020.1。

**限制：**本次 API 显示最近推送在 2022 年；作者也在 README 中说明其定位主要是学习和尝试新想法，不应把历史性能当成当前最优结果。它的 OpenCL 工程也不是复制进 Vitis HLS 就能直接综合的普通 C++ 工程。

推荐程度：架构阅读优于作为第一条复现路线。

### 8. Vitis AI：使用现成 DPU 进行系统部署

- [GitHub 仓库](https://github.com/Xilinx/Vitis-AI)
- [官方版本入口](https://xilinx.github.io/Vitis-AI/)
- [5.0 文档](https://xilinx.github.io/Vitis-AI/5.0/html/index.html)
- [3.5 文档](https://xilinx.github.io/Vitis-AI/3.5/html/index.html)

典型思路是：在 PL 中集成 DPU，通过量化与编译工具得到目标模型，再由 PS 上的运行库提交任务。

```text
训练模型 → 量化 → 针对 DPU 架构编译
                       ↓
PS 应用/运行库 → PL 中的 DPU → 输出结果
```

适合你学习完整应用：图像预处理、模型输入输出张量、异步任务、CPU/DPU 分工和性能分析。相比自己设计卷积引擎，这条路线更偏部署与系统集成。

必须分清：

- 仓库中的开放软件、示例与厂商交付 DPU IP 的可获取源码范围、使用条件不是同一个问题，不能整体称为“所有硬件 RTL 全开源”。
- 模型编译目标必须和板上 DPU 架构一致，不能只看器件都属于 Zynq。
- 本次官方入口同时列出了 5.0、4.0、3.5、3.0 文档；不要因为旧教程使用 3.5 就判断当前只有 3.5，也不要将不同版本组件混装。
- 文档中的 Zynq UltraScale+、Kria、Versal、Alveo 支持，不代表你的具体 RFSoC 板已有可直接使用的平台。

推荐程度：若目标是尽快建立视觉推理系统，可作为主路线；若目标是研究加速器内部结构，则优先 FINN/HLS。

### 9. NVDLA：完整深度学习加速器 RTL 的进阶阅读

- [硬件仓库](https://github.com/nvdla/hw)
- [官方文档](https://nvdla.org/)

NVDLA 提供加速器硬件、C 模型、验证资料，以及相关软件栈文档。适合研究卷积流水线、片上缓冲、DMA、寄存器配置和系统集成。

建议阅读顺序：先看硬件架构和集成手册，再沿数据路径理解读入、计算、输出，最后查看 RTL 与验证环境。不要从上千个模块文件中随机挑一个开始。

**限制：**本次默认分支 README 描述的是 `nvdlav1` 固定配置版本；不同分支能力并不相同。原始 IP 不等于现成 FPGA overlay，上板仍需处理存储实现、接口、时钟复位、资源与软件栈。最近推送时间较早，优先当作成熟架构案例阅读。

推荐程度：进阶，不作为第一周的上板目标。

### 10. Gemmini：RISC-V + 脉动阵列的体系结构研究

- [GitHub 仓库](https://github.com/ucb-bar/gemmini)
- [仓库链接的 MLSys 2022 教程](https://sites.google.com/berkeley.edu/gemmini-tutorial-mlsys-2022)

Gemmini 是 Chipyard 生态中的 DNN 加速器生成器，使用 Chisel，典型系统通过 RISC-V RoCC 接口连接处理器，并使用脉动阵列执行矩阵运算。

适合研究：

- weight-stationary 和 output-stationary 数据流。
- 阵列大小、scratchpad、累加器和 DMA 之间的关系。
- 软件分块与硬件数据复用。
- 处理器、缓存、加速器和运行软件如何共同影响性能。

**限制：**它不是为现有 Zynq Arm PS 直接准备的通用 AXI 神经网络 IP。FireSim 上的 FPGA 加速仿真也不等于裸加速器在目标 FPGA 上的产品部署。先按仓库文档进行功能仿真，再决定是否深入。

教程链接来自仓库 README，但本次未能成功读取 Google Sites 页面；不将其具体课件内容视为已核实。

推荐程度：体系结构进阶。这里的 Gemmini 与你工程里的 Gemini 深度相机不是同一个东西。

### 11. CFU Playground：为软核 CPU 添加神经网络加速指令

- [GitHub 仓库](https://github.com/google/CFU-Playground)
- [官方教程](https://cfu-playground.readthedocs.io/en/latest/)

这条路线将 TensorFlow Lite Micro 算子的热点操作替换成自定义指令，由 FPGA 中的 CFU 硬件完成。

典型实验：

1. 运行量化模型并统计各层周期。
2. 选择热点算子，例如 INT8 点积。
3. 编写自定义硬件和指令接口。
4. 修改软件 kernel 调用它。
5. 比较正确性和实际周期变化。

README 列出了 Arty、Nexys Video、部分 Lattice 板等测试平台；无板卡时也可先使用 Renode 或 Verilator。

**限制：**项目不是 Google 正式支持产品；默认示例强调可控输入下的周期测量，不是已经具备摄像头采集和展示的完整终端应用。也不是默认使用 Zynq 的 Arm PS 运行模型。

推荐程度：适合想同时提高嵌入式软件、性能分析与 RTL 能力的人。

### 12. AMD Vitis HLS Introductory Examples：补足算子实现基本功

- [GitHub 仓库](https://github.com/Xilinx/Vitis-HLS-Introductory-Examples)

它不是完整神经网络框架，但很适合在遇到综合瓶颈时查阅。仓库提供源代码、testbench 和构建脚本，分类包括 Array、Interface、Modeling、Pipelining、Task-Level Parallelism 等。

对你建议优先做：

- 数组分块与 partition：理解存储端口如何限制并行计算。
- 流水循环：观察循环依赖与 II。
- 任意精度数据类型：建立定点数意识。
- AXI master、AXI-Lite、AXI-Stream：理解数据通道和控制通道。
- DATAFLOW、FIFO 和任务并行：理解阻塞和死锁。

推荐程度：配套必备。跟随所用工具版本选择对应 tag/分支，不要假定主线示例兼容所有旧版工具。

### 补充：PYNQ 是运行和集成框架，不是神经网络编译器

[PYNQ 官方文档](https://pynq.readthedocs.io/en/latest/)介绍了 overlay、Python API 和板端开发方式，并明确包含 Zynq、Zynq UltraScale+、RFSoC 等平台家族。

它可以帮助你加载已有硬件、配置寄存器和搬运数据，但不会自动将任意 Python/PyTorch 代码转换成 PL 电路。具体板卡仍需要匹配的镜像、板级支持与硬件设计。

## 三、仓库状态快照：选复现项目时参考

下表为本次 GitHub API 返回的 `pushed_at` 日期，按 UTC 日期记录。它表示仓库最近推送，不等于最近正式发布，也不能单独证明项目稳定性或停止维护。下表仓库本次均未标记为 archived。

| 仓库 | 最近推送日期 | 选用建议 |
|---|---|---|
| Xilinx/finn | 2026-11-17 | 重点跟踪当前文档与板卡支持变化 |
| fastmachinelearning/hls4ml | 2026-11-17 | 适合作为主路线，固定 release 与依赖 |
| fastmachinelearning/hls4ml-tutorial | 2026-11-16 | 优先使用教程自身的环境说明 |
| Xilinx/brevitas | 2026-11-18 | 量化训练与后端版本配套 |
| Xilinx/finn-examples | 2026-03-10 | 注意示例引用的是较旧工具组合 |
| AlexMontgomerie/fpgaconvnet-tutorial | 2024-09-20 | 研究设计空间探索，逐项核对依赖 |
| NNgen/nngen | 2023-10-17 | 偏源码与生成机制学习 |
| doonny/PipeCNN | 2022-02-14 | 偏经典架构案例和旧环境复现 |
| Xilinx/Vitis-AI | 2026-02-24 | 从官方版本入口确认工具与平台组合 |
| nvdla/hw | 2022-03-02 | 偏 RTL 架构阅读与验证 |
| ucb-bar/gemmini | 2026-11-14 | 适合 Chipyard/RISC-V 体系结构研究 |
| google/CFU-Playground | 2026-02-26 | 适合算子热点与自定义指令实验 |
| Xilinx/Vitis-HLS-Introductory-Examples | 2026-11-11 | 用与本机 HLS 匹配的版本 |

## 四、课程、视频和可操作实验

### 1. hls4ml 官方教程与入门讲解

- [教程 Notebook 仓库](https://github.com/fastmachinelearning/hls4ml-tutorial)
- [项目 README 推荐的入门视频](https://www.youtube.com/watch?v=2y3GNY4tf7A)

适合补齐从模型、量化到 HLS 的基本流程。教程 README 提供 `environment.yml` 和环境配置说明，并链接了配套 slides；优先以所选版本教程为准。

推荐做法：先完成最小模型转换和 C 仿真，再尝试精度与复用因子配置，最后进入板级集成。网页中出现 Binder 入口，不代表线上环境一定装有厂商综合工具和许可。

本次教程 README 链接的独立网页入口返回 404，因此这里保留已通过官方 API 核实的 GitHub 教程入口。

### 2. FINN 官方视频与 Notebook

- [官方主页链接的视频列表](https://www.youtube.com/channel/UC6lfcgPvcrXgaQl_lvVdbPw/playlists)
- [教程说明](https://finn.readthedocs.io/en/latest/tutorials.html)
- [Notebook 目录](https://github.com/Xilinx/finn/tree/main/notebooks)

建议顺序：ONNX 基础 → Brevitas/QONNX 导入 → cybersecurity 端到端示例 → 中间模型验证 → folding/高级 builder 设置。

学习产出：画出一个小网络的算子图，说明每次图变换和硬件化步骤做了什么，并能定位哪一层先出现数值不一致。

### 3. UCSD CSE 237C + Parallel Programming for FPGAs 实验

- [课程主页](https://kastner.ucsd.edu/ryan/cse237c/)
- [实验总目录](https://pp4fpgas.readthedocs.io/en/latest/)
- [BNN 神经网络实验](https://pp4fpgas.readthedocs.io/en/latest/project8.html)

这是与你已有项目经验很接近的一套材料：不仅有神经网络，也包含 FIR、FFT、OFDM、AXI 和 DMA 实验。

尤其推荐 BNN 项目：根据 Python golden model 编写 HLS 实现，用 XNOR/popcount 代替二值乘加，完成逐层测试，再研究流水化与展开。它提供的是教学任务与部分起始文件，不是所有功能都已完成的交钥匙工程。

该 BNN 页面当前标注 Vitis HLS 2022.2 推荐环境、Zynq-7020 目标。它与 FINN 当前主线的板卡支持是两套独立信息，不能混为一谈。

### 4. MIT 6.5940：TinyML and Efficient Deep Learning Computing

- [2024 年完整课程页面](https://hanlab.mit.edu/courses/2024-fall-65940)
- [课程总入口](https://hanlab.mit.edu/course)

推荐优先看 2024 页面中的：Pruning and Sparsity、Quantization、Neural Architecture Search，以及对应实验。课程页提供 slides、视频与实验链接；并非每个日程占位条目都有可用视频。

这门课主要教高效模型与系统方法，不是一门从 Vivado 建工程开始的 FPGA 上板课。对你最直接的帮助是理解如何把模型改得更适合有限资源硬件。

推荐作业产出：比较不同量化方案的模型精度、模型大小和算子支持情况，再判断哪一种值得进入硬件实现。

### 5. MIT Eyeriss：Hardware Accelerators for DNNs 教程

- [官方教程页](https://eyeriss.mit.edu/tutorial.html)

页面包含 DNN 计算、加速器架构、数据流、精度、稀疏性和评估指标等 slides，并提供相关录播入口。

建议重点看 DNN Kernel Computation、DNN Accelerators、precision、Benchmarking Metrics。适合在已经知道“卷积怎么算”之后，进一步理解“为什么这样存储和搬运数据”。

注意：Eyeriss 是架构研究案例，不应直接当作一个为你的 RFSoC 板准备好的 FPGA 工程。

### 6. CFU Playground 分步教程

- [教程首页](https://cfu-playground.readthedocs.io/en/latest/)

优先阅读 `Crash Course on Everything`、`The Step-by-Step Guide to Building an ML Accelerator` 等章节。它适合把“分析热点—写硬件—改软件—测周期”连成一次完整迭代。

### 7. AMD HLS 示例作为专项练习

- [官方示例仓库](https://github.com/Xilinx/Vitis-HLS-Introductory-Examples)

遇到 II 下不来、数组访问冲突、AXI 性能不足等问题时，回到这些小例子做对照实验，比直接修改一个大型 CNN 更容易找出原因。

### 8. 中文神经网络基础：动手学深度学习

- [中文在线教材与代码](https://zh.d2l.ai/)

推荐按需补多层感知机、卷积、填充与步幅、多输入输出通道、池化、LeNet、BatchNorm 和 ResNet。第一轮不必先学完大模型、分布式训练和全部优化算法。

学习标准：可以不依赖现成 `Conv2d`，用小矩阵解释一次卷积的输入、权重、输出尺寸与乘加过程。

### 中文视频检索入口

以下是方便继续找中文讲解的 **Bilibili 搜索入口**，不是已逐条核实的具体课程推荐，也不代表所有结果完整、免费或与最新工具兼容：

| 想补的内容 | 搜索入口 |
|---|---|
| 模型到 HLS | [hls4ml FPGA](https://search.bilibili.com/all?keyword=hls4ml%20FPGA) |
| 低比特网络与 FINN | [FINN FPGA 神经网络](https://search.bilibili.com/all?keyword=FINN%20FPGA%20%E7%A5%9E%E7%BB%8F%E7%BD%91%E7%BB%9C) |
| 算子与系统集成 | [Vitis HLS 卷积 AXI DMA](https://search.bilibili.com/all?keyword=Vitis%20HLS%20%E5%8D%B7%E7%A7%AF%20AXI%20DMA) |
| 量化与模型压缩 | [MIT 6.5940 量化](https://search.bilibili.com/all?keyword=MIT%206.5940%20%E9%87%8F%E5%8C%96) |

筛选时优先找提供代码、环境版本、C/RTL 验证和上板测量的材料。只有演示画面、没有模型/版本/工程的内容，适合了解方向，不宜作为主要复现依据。

## 五、书籍与长期参考资料

### 1. Parallel Programming for FPGAs

- 作者：Ryan Kastner、Janarshdan Matai、Stephen Neuendorffer。
- [作者页面](https://kastner.ucsd.edu/hls/)
- [开源书籍仓库](https://github.com/KastnerRG/pp4fpgas)
- [配套实验](https://pp4fpgas.readthedocs.io/en/latest/)

**优先级最高的 HLS 书。**作者页提供免费 PDF 和源文件，书籍采用 CC BY 4.0 许可。

重点读：硬件思维、循环优化、流水线、存储结构、并行计算以及接口设计；结合配套 FIR/FFT/OFDM/BNN 实验学习，与你已有通信项目能够衔接。

适合回答：“同一段 C++，为什么修改循环和数组组织后硬件性能会大幅变化？”

### 2. Efficient Processing of Deep Neural Networks

- 作者：Vivienne Sze、Yu-Hsin Chen、Tien-Ju Yang、Joel S. Emer。
- 出版年份：2020。
- [出版社页面](https://link.springer.com/book/10.1007/978-3-031-01766-7)
- [作者配套教程](https://eyeriss.mit.edu/tutorial.html)

**优先级最高的 DNN 加速器架构书。**重点读数据搬运、数据复用、存储层次、数据流、量化、稀疏性和评估方法。

它解释“为什么乘法器更多不一定更快”“为什么减少访存可能比提高计算峰值更有效”。它不是手把手的 FPGA 工程搭建教程，应与项目实验配合。

获取方式：出版社电子书/纸质书或机构订阅；作者公开的教程、slides 和节选可先阅读，不将全书描述为对所有人免费开放。

### 3. 动手学深度学习

- 作者：阿斯顿·张、李沐、扎卡里·C. 立顿、亚历山大·J. 斯莫拉。
- [中文在线版](https://zh.d2l.ai/)

用途是补模型侧基础。优先读第 4、6、7 章中与 MLP/CNN 有关的部分，以及参数管理、模型保存与加载等内容。在线内容和代码可公开阅读，注意按所选框架版本配置环境。

读完的目标不是记住全部网络，而是能解释模型每层的形状、参数量、计算量和推理行为。

### 4. The Zynq Book

- University of Strathclyde 团队编写，2014 年出版。
- [官网与中英文免费下载入口](https://www.zynqbook.com/)

它面向 Zynq-7000，适合巩固 PS/PL、硬件软件协同和基本系统集成。官网明确说明旧配套教程已不再维护，因此需要把概念和旧版本操作截图分开看。

它不是神经网络专著，也不能拿其中的器件配置直接替换 UltraScale+/RFSoC 配置。

### 5. Software Defined Radio with Zynq UltraScale+ RFSoC

- 常称 The RFSoC Book，StrathSDR 团队编写。
- [官网、免费下载与配套资源](https://www.rfsocbook.com/)

这本书与你的 RFSoC 通感平台关联很强。官网提供免费电子版，并链接 Jupyter Notebook、GitHub 和基于 PYNQ 的设计实例。

它主要讲 RFSoC、SDR 和 DSP，不是神经网络编译器教材。适合在你准备将 RadioML/1D CNN 接入真实 IQ 数据链路时，查阅采样、数据转换、数据通路和板级系统知识。

### 还应长期放在手边的手册

- [hls4ml 前端/后端与支持矩阵](https://fastmachinelearning.org/hls4ml/intro/status.html)
- [FINN Getting Started](https://finn.readthedocs.io/en/latest/getting_started.html)
- [PYNQ 文档](https://pynq.readthedocs.io/en/latest/)
- AMD Vitis HLS 用户指南 UG1399：通过 [AMD 文档入口](https://docs.amd.com/)查找与你安装版本相同的指南。

书籍帮助理解原理，版本手册决定某个配置在当前工具上能否工作。

## 六、最值得补的技术知识

### 1. 定点数与量化不是“把 float 强转成 int8”

常见仿射量化可写成：

```text
q = clip(round(x / scale) + zero_point, qmin, qmax)
x_hat = scale × (q - zero_point)
```

实际实现还涉及逐张量/逐通道 scale、舍入模式、饱和、偏置以及层间重新量化。并非所有工具都支持所有形式；要以目标后端约束为准。

INT8 输入、INT8 权重并不表示中间和输出都只需 8 位。多项乘积相加通常需要更宽的累加器，然后根据规则缩放和截断。`ap_fixed<W,I>` 表示总位宽 W、整数部分位宽 I，不能只看 W 而忽略数值范围。

### 2. 先建立计算量与存储量概念

普通卷积、不考虑分组时：

```text
MACs = H_out × W_out × C_out × K_h × K_w × C_in
权重元素数 = C_out × K_h × K_w × C_in
```

若使用 GOPS，需声明一个 MAC 计为一次运算还是乘法、加法各算一次。depthwise/group convolution 应使用相应分组公式。

除了权重，还要估算输入输出特征图、部分和与双缓冲所占空间。模型文件小，不代表推理时片上缓存一定放得下。

### 3. 分清延迟、II 和吞吐

- 延迟：一个样本从输入到对应输出所用的时间。
- II：某一级流水线接收相邻任务或数据的启动间隔，具体单位要结合接口与实现解释。
- 吞吐：稳定运行后每秒完成多少样本。

循环 II=1 不代表整个网络每周期完成一张图片。还要考虑一帧所需数据数、层间速率、FIFO 背压和 DMA。

### 4. 数据搬运常常是系统瓶颈

理解 line buffer、滑动窗口、tiling、权重/输入/输出驻留、双缓冲和 AXI burst。简单性能上界可以从下式思考：

```text
可达到的计算速率 ≤ min(计算峰值, 有效带宽 × 算术强度)
```

这里的有效带宽必须实测，算术强度需使用同一数据流和访存口径。不能直接拿 DDR 标称速率当成模型可用吞吐。

### 5. 学会逐层定位错误

优先排查：NCHW/NHWC、signed/unsigned、大小端与位打包、scale/zero-point、padding、累加溢出和舍入差异。

不要只比较最终分类标签。前面某层输出已经错误时，最终 top-1 偶尔仍可能相同。

## 七、给你的分阶段实战路线

以下以已有 FPGA/嵌入式经验、每周约 10～15 小时为规划假设。时间仅用于安排，不是完成保证；环境和板级适配可能占用较多时间。

| 阶段 | 建议投入 | 任务 | 可检查的产出 |
|---|---|---|---|
| 1. 模型与数值 | 约 1 周 | 小 MLP/CNN 浮点参考、固定测试集、量化尝试 | 原始精度、逐层输出、量化配置和依赖清单 |
| 2. 模型到硬件 | 约 1～2 周 | 用 hls4ml 跑 C 仿真与 HLS 综合 | 数值误差、资源/延迟报告、不同复用因子对比 |
| 3. 板级闭环 | 约 1～2 周 | IP 集成、DMA、板端应用、批量推理 | 同一测试集的上板结果、实测延迟/吞吐 |
| 4. 量化与并行优化 | 约 2 周 | 用 FINN/Brevitas，修改位宽及 PE/SIMD | 精度—资源—速度取舍，解释主要瓶颈 |
| 5. 结合已有项目 | 按需求追加 | IQ/图像数据源接入，小型实时推理链路 | 可复现工程、输入输出协议、稳定性与丢帧测试 |

### 第一个项目：小模型在 FPGA 上的完整推理与量化对比

不要把目标只定为“成功出现一个分类结果”。至少保留：

1. 同一批输入下的浮点模型、量化参考、HLS C 仿真与 FPGA 输出。
2. 模型结构、输入 shape、预处理和权重来源。
3. 若干有实际意义的位宽/复用配置对比。
4. Vivado 实现后的资源与时序报告。
5. batch=1 的端到端延迟，以及稳定运行的吞吐统计。

能否直接上板取决于你实际持有的 FPGA 型号、板级设计、内存和镜像；本文不假定当前 STM32 工程所在板上具有 FPGA 资源。STM32H7 与你另一个 RFSoC 平台是不同部署目标。

### 第二个项目：与 RFSoC 项目结合的调制识别

可参考 FINN Examples 的 RadioML 1D CNN，但第一阶段建议先用保存的 IQ 样本，避免把射频链路、预处理和模型实现的问题同时引入。

```text
离线 IQ 测试集 / RFSoC 数据源
    → 截取固定长度窗口
    → 与训练一致的归一化和量化
    → 输入缓存 / AXI-Stream
    → PL 中的 1D CNN
    → 类别与分数
    → PS 记录、显示或发送结果
```

进阶时再逐项处理：采样率与模型窗口长度匹配、重叠窗口、跨时钟 FIFO、训练/实测数据分布差异、频偏与 SNR、背压和丢样。

性能评估至少包含：不同 SNR 下的识别表现、板端与量化参考一致性、单窗口延迟、可持续窗口速率、资源占用。网络输出的分数不应未经校准就直接宣称为严格概率。

如果选择低延迟实时处理，也可以让 PL 直接接收预处理后的流；是否经过 DDR/DMA 应根据数据源和系统带宽设计，不能把示意链路当成唯一架构。

## 八、上板前最容易踩的坑

1. **模型算子不受支持。**先用官方小示例验证，再逐层增加自己的网络；导出 ONNX 成功只是中间一步。
2. **把不同项目的版本拼在一起。**FINN 当前主线、旧版 FINN Examples 和某个 hls4ml 教程可能依赖完全不同的工具组合。
3. **只改目标 part 就以为完成移植。**还需要检查 PS 配置、DDR、地址映射、时钟复位、约束、DMA、驱动和运行环境。
4. **下载其他板卡的 bitstream。**即使同属 Zynq 家族，也不代表器件和板级设计兼容。
5. **只看 HLS 估算。**HLS 延迟与资源估算不等于布局布线结果，更不等于端到端实测。
6. **过度展开。**乘法器增多可能造成 BRAM 端口不足、布线拥塞或时序下降，需要联合考虑存储结构。
7. **忽略 cache 一致性。**PS 与 DMA 共享内存时要按裸机/Linux/PYNQ 等实际环境使用正确的分配和同步接口。
8. **只计计算、不计搬运。**单独报告加速器时间和含预处理、传输、同步、后处理的端到端时间。
9. **把稀疏模型理解为自动省时。**非结构化零值只有被硬件/编译器有效利用时，才可能转化为加速。
10. **默认 RFSoC 都有 AI Engine。**RFSoC 的 PL 与 Versal 的 AI Engine 是不同资源，需按具体器件判断。
11. **一开始部署过大的模型。**先跑通 MLP/小 CNN，再考虑大网络；小板运行一个裁剪模型与完整大模型部署不是同一件事。

## 九、最终项目应该记录哪些数据

| 维度 | 建议记录 |
|---|---|
| 可复现环境 | 仓库 commit/tag、Python 依赖、Vivado/Vitis/HLS 版本、操作系统 |
| 硬件 | 完整器件型号、板卡、时钟、DDR/片上存储配置、实际使用的 IP |
| 模型 | 数据集与划分、权重来源、输入 shape、预处理、算子与量化参数 |
| 正确性 | 浮点和量化精度、逐层误差、C/RTL/板端一致性 |
| 资源与时序 | LUT、FF、DSP、BRAM/URAM、实现后时序与工作频率 |
| 延迟 | 计算模块延迟、端到端延迟、预热方式、重复次数、统计口径 |
| 吞吐 | batch、输入速率、稳定输出速率、是否丢帧/丢样、背压情况 |
| 能耗（可选） | 板卡还是芯片测量、空闲功耗、负载、仪器与采样方式 |

与 CPU 对比时，使用可说明的基线：同一模型任务、同一数据集与精度条件，记录 CPU 型号、线程数、推理库和计时范围。只有内核计时的 FPGA 结果，不能直接与含完整预处理的 CPU 结果计算“端到端加速倍数”。

## 十、如果现在只看六项资料

1. [Parallel Programming for FPGAs](https://kastner.ucsd.edu/hls/)：建立 HLS 硬件优化思维。
2. [hls4ml 官方教程](https://github.com/fastmachinelearning/hls4ml-tutorial)：跑通模型到硬件的最短实验。
3. [FINN 官方教程](https://finn.readthedocs.io/en/latest/tutorials.html)：理解量化网络和定制数据流。
4. [Brevitas](https://github.com/Xilinx/brevitas)：掌握模型侧量化。
5. [MIT DNN 加速器教程](https://eyeriss.mit.edu/tutorial.html)：理解存储、数据流与评估。
6. [FINN Examples](https://github.com/Xilinx/finn-examples)：重点研究 RadioML 示例，再结合你的 RFSoC 系统做适配。

初次实操先选 hls4ml 或 FINN 中一个，完成从测试数据到板端结果的闭环，再进入另一条路线做比较。完成一个能解释、可复现、有实测对比的小项目，比同时安装多套工具更有学习价值。
