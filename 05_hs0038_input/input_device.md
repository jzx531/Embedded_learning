# Linux input 输入设备：注册流程、evdev 与自定义 handler

本文整理前面对输入子系统注册图、HS0038 红外接收驱动，以及自定义 `input_handler` 的解析。代码用于说明接口和对象之间的关系，不代表已经在目标板内核上编译、验证。

## 1. 先区分设备、驱动与 handler

Linux 输入设备驱动通常负责三件事：初始化硬件、声明输入能力、上报输入事件。事件如何提供给应用程序，可以复用内核已有的通用处理器，例如 `evdev`。

| 对象 | 作用 | 例子 |
|---|---|---|
| `platform_device` | 描述平台上的硬件设备 | SoC 内部 I²C 控制器、设备树描述的 GPIO 红外接收设备 |
| `platform_driver` | 操作对应平台设备 | I²C 控制器驱动、HS0038 平台驱动 |
| `i2c_adapter` | 表示一条可用的 I²C 总线 | 控制器驱动注册的 I²C adapter |
| `i2c_client` | 表示总线上的一个 I²C 外设 | I²C 触摸屏芯片 |
| `i2c_driver` | 初始化并操作某种 I²C 外设 | Goodix 触摸屏驱动 |
| `input_dev` | 描述输入设备及其输入能力 | 触摸屏、键盘、红外遥控器对应的输入设备 |
| `input_handler` | 接收和处理输入事件 | `evdev`、控制台键盘处理器 `kbd`、自定义 handler |
| `input_handle` | 连接一个输入设备和一个 handler | 某个 `input_dev` 与 `evdev` 之间的连接 |

`input_dev` 回答“设备能上报什么”，`input_handler` 回答“谁来处理事件”。两者通常由不同模块注册。

一个输入设备可以连接多个匹配的 handler；一个 handler 也可以连接多个输入设备。它们之间通过各自的 `input_handle` 建立联系，不是固定的一对一绑定。

## 2. 注册图中的 I²C 触摸屏流程

### 2.1 平台层：初始化 I²C 控制器

在常见的设备树平台上，SoC 内部 I²C 控制器节点对应一个 `platform_device`。内核将它与对应的 `platform_driver` 匹配，成功后调用控制器驱动的 `probe()`。

控制器驱动通常会获取寄存器、时钟、中断等资源，初始化硬件，设置传输算法，然后注册 `i2c_adapter`：

```c
i2c_add_adapter(adapter);
/* 或者 */
i2c_add_numbered_adapter(adapter);
```

这一步让 Linux 能够通过该控制器执行 I²C 传输。控制器驱动负责“如何在总线上传输”，还不负责解释触摸坐标。

### 2.2 I²C 层：创建外设并匹配驱动

例如，设备树中有以下结构：

```dts
&i2c1 {
    status = "okay";

    touchscreen@5d {
        compatible = "goodix,gt911";
        reg = <0x5d>;
        /* 还需要按硬件填写中断、复位等属性。 */
    };
};
```

控制器对应 `platform_device`，其子节点描述的触摸屏则对应 `i2c_client`。注册 adapter 的过程中，I²C 核心会处理这些子节点并注册相应的 client。

触摸屏驱动注册自己的 `i2c_driver`。设备树场景下，I²C 核心主要通过节点的 `compatible` 与驱动的 `of_match_table` 进行匹配；也存在 ACPI 和传统 I²C ID 等匹配路径。

匹配成功后调用触摸屏驱动的 `probe()`，把实际外设对应的 `i2c_client` 传给它。驱动可以通过以下信息访问芯片：

```c
client->addr       /* 芯片的 I²C 地址 */
client->adapter    /* 芯片所在的 I²C 总线 */
client->dev        /* 通用设备对象 */
```

外设驱动通过 `i2c_transfer()` 等接口读写寄存器，解释芯片返回的数据，再转换为输入事件。

### 2.3 输入层：注册 input_dev

触摸屏驱动的 `probe()` 中，通常会分配、设置并注册输入设备：

```c
/* 示意代码，省略错误处理和实际多点触摸配置。 */
input = devm_input_allocate_device(&client->dev);
input->name = "goodix-touchscreen";

input_set_capability(input, EV_KEY, BTN_TOUCH);
input_set_abs_params(input, ABS_X, 0, max_x, 0, 0);
input_set_abs_params(input, ABS_Y, 0, max_y, 0, 0);

input_register_device(input);
```

这一步声明设备能够产生触摸状态、X/Y 坐标以及坐标范围。`i2c_client` 和 `input_dev` 描述同一个硬件的不同侧面，不能互相替代。

上述 I²C 路径不是所有输入设备都需要经过的路径。用户提供的 HS0038 代码直接使用 GPIO 中断，走的是平台驱动到输入设备的路径，不涉及 I²C adapter/client。

## 3. input_dev 如何与 handler 建立连接

输入核心维护已注册输入设备和 handler 的列表，常见名称是：

```c
input_dev_list
input_handler_list
```

设备一端调用：

```c
input_register_device(input);
```

handler 一端调用：

```c
input_register_handler(&handler);
```

两者注册时，输入核心会尝试连接已经存在的另一方，因此设备和 handler 的注册顺序不固定。

典型处理顺序为：

```text
根据 handler 的 id_table 检查设备能力
    → 如果提供了 match 回调，再进行额外筛选
    → 匹配成功后调用 connect
    → connect 中创建并注册 input_handle
    → 根据处理器的用途打开输入设备、建立相应接口
```

`connect()` 是匹配成功后的连接回调，不是执行匹配判断的函数。它的角色可以类比设备驱动匹配后的 `probe()`，但二者不是相同的接口。

输入子系统使用自己的匹配与连接机制，不能简单把它当成另一条与 `platform_bus_type` 或 `i2c_bus_type` 完全相同的总线。

## 4. 没有定义 handler，为什么仍然能工作

因为内核已经提供了通用的 `evdev` handler。硬件驱动只注册 `input_dev`，不需要重复实现它。

内核的 `drivers/input/evdev.c` 中有类似的定义，具体字段与实现细节以目标内核为准：

```c
static struct input_handler evdev_handler = {
    .event      = evdev_event,
    .events     = evdev_events,
    .connect    = evdev_connect,
    .disconnect = evdev_disconnect,
    .name       = "evdev",
    .id_table   = evdev_ids,
};
```

`evdev` 初始化时注册这个 handler。输入设备与它匹配后，`evdev_connect()` 建立连接，并注册供应用程序使用的字符设备接口。相应节点通常由 devtmpfs/udev 建立，例如 `/dev/input/event0`。

需要区分连接建立和事件接收的启用。`evdev` 通常在应用打开对应 event 节点后，通过 `input_open_device()` 打开其输入连接；注册设备不意味着后来才打开的应用可以读到此前所有历史事件。

使用这个接口需要内核启用 `CONFIG_INPUT_EVDEV`；若编译成模块，还需要模块已加载。即使没有 evdev，`input_dev` 仍然可能成功注册，但不会因此自动获得 eventX 接口。

### 4.1 evdev 不是键盘专用 handler

`evdev` 可以接收键盘、鼠标、触摸屏、遥控器等输入设备的事件。

```c
__set_bit(EV_KEY, input->evbit);
```

这行代码只是声明“设备支持按键事件”，不是选中了某个键盘专用 handler。

控制台键盘处理器 `kbd` 是另一个 handler。如果内核启用了它，设备又满足其匹配条件，也可能建立连接。因此，应准确声明设备支持的按键，不应为了省事把所有按键能力都打开。

## 5. HS0038 代码中的两套数据接口

用户提供的代码同时保留了自定义字符设备和标准输入设备，两条路径相互独立。

| 路径 | 注册方式 | 应用读取内容 | 读取逻辑由谁实现 |
|---|---|---|---|
| `/dev/myhs0038` | `register_chrdev()`、`device_create()` | 4 字节的原始红外组合码 | 驱动自己的 `hs0038_drv_read()` |
| `/dev/input/eventX` | `input_register_device()`，再由 evdev 接入 | 标准 `struct input_event` | 内核 evdev |

### 5.1 自定义字符设备路径

中断中执行：

```c
put_data(val);
wake_up(&hs0038_wq);
```

把红外码放进驱动自己的环形缓冲区，并唤醒等待者。应用读取 `/dev/myhs0038` 时，进入：

```c
hs0038_drv_read()
    → wait_event_interruptible()
    → get_data()
    → copy_to_user()
```

这一套机制不依赖 input handler。

### 5.2 输入子系统路径

同一个中断函数还执行：

```c
input_event(hs0038_input_dev, EV_KEY, val, 1);
input_event(hs0038_input_dev, EV_KEY, val, 0);
input_sync(hs0038_input_dev);
```

这条路径通过输入核心，把合法事件分发给已连接且处于接收状态的 handler。

应用读取 `eventX` 时，不会进入 `hs0038_drv_read()`，也不会使用驱动自己的 `hs0038_wq`。同样，驱动中尚未实现的自定义 `poll()`，不会影响 evdev 自己的 `poll()` 实现。

如果只需要标准输入事件，可以去掉自定义字符设备的注册、`file_operations`、原始码环形缓冲区和等待队列，保留硬件接收、解析、按键映射和 input 上报。

## 6. 事件类型、按键码与同步

一次输入事件包括类型、代码、数值：

```c
input_event(input, type, code, value);
```

| 参数或常量 | 含义 |
|---|---|
| `EV_KEY` | 按键或按钮事件类型 |
| `KEY_POWER`、`KEY_VOLUMEUP` | Linux 定义的按键码 |
| `value = 1` | 按下 |
| `value = 0` | 松开 |
| `value = 2` | 按键重复 |
| `input_sync()` | 上报 `EV_SYN / SYN_REPORT`，标记一批事件的边界 |

`input_report_key()` 是上报 `EV_KEY` 的便捷接口。若把一次瞬时按键表示为两个独立的状态帧，可以写成：

```c
input_report_key(input, keycode, 1);
input_sync(input);

input_report_key(input, keycode, 0);
input_sync(input);
```

立即上报按下和松开表示一次点击，不表示一直按住。即使声明了 `EV_REP`，这样上报也不能实现正常的持续按住自动重复。

### 6.1 红外原始码不能直接作为按键码

原代码得到的是：

```c
hs0038_data = (data[0] << 8) | data[2];
```

这是红外地址与命令的组合，不是 Linux 按键码。直接把它作为 `EV_KEY` 的 code，可能超过 `KEY_MAX` 而被输入核心过滤；即使未超出范围，也不保证对应正确的按键语义。

应该先建立映射，再上报，并只声明实际支持的按键：

```c
input_set_capability(input, EV_KEY, KEY_POWER);
input_set_capability(input, EV_KEY, KEY_VOLUMEUP);

/* 后续接收流程：raw_code → 映射表 → keycode → input_report_key()。 */
```

把整个 `keybit` 设置为 1，不能突破合法按键码范围。超范围事件在输入核心中被过滤后，自定义 handler 也接收不到。

如果还要通过输入接口提供原始扫描码，可以进一步研究 `EV_MSC / MSC_SCAN`，但仍需正确声明设备能力，并与标准按键事件区分。

## 7. 自定义 input_handler 示例

当确实需要在内核中接收输入事件时，可以注册自己的 handler。以下示例筛选支持 `EV_KEY`、且名称为 `hs0038` 的设备，接收按键后输出限速日志。

它只演示事件接收，不创建新的 `/dev/xxx`，也不会自动替换 evdev。

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/input.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/errno.h>

/* 按输入能力初步筛选。 */
static const struct input_device_id hs0038_ids[] = {
    {
        .flags = INPUT_DEVICE_ID_MATCH_EVBIT,
        .evbit = { BIT_MASK(EV_KEY) },
    },
    { }
};

/* 再按名称筛选。产品中也可以根据其他稳定属性筛选。 */
static bool hs0038_match(struct input_handler *handler,
                        struct input_dev *dev)
{
    return dev->name && !strcmp(dev->name, "hs0038");
}

/* 可能运行在原子上下文，不能执行会睡眠的操作。 */
static void hs0038_event(struct input_handle *handle,
                        unsigned int type,
                        unsigned int code,
                        int value)
{
    if (type != EV_KEY)
        return;

    pr_info_ratelimited("hs0038_handler: code=%u value=%d\n",
                        code, value);
}

static int hs0038_connect(struct input_handler *handler,
                         struct input_dev *dev,
                         const struct input_device_id *id)
{
    struct input_handle *handle;
    int ret;

    handle = kzalloc(sizeof(*handle), GFP_KERNEL);
    if (!handle)
        return -ENOMEM;

    handle->dev = dev;
    handle->handler = handler;
    handle->name = "hs0038_custom_handle";

    ret = input_register_handle(handle);
    if (ret)
        goto err_free;

    /* 打开连接，使这个 handler 能够接收事件。 */
    ret = input_open_device(handle);
    if (ret)
        goto err_unregister;

    pr_info("hs0038_handler: connected to %s\n", dev->name);
    return 0;

err_unregister:
    input_unregister_handle(handle);
err_free:
    kfree(handle);
    return ret;
}

static void hs0038_disconnect(struct input_handle *handle)
{
    input_close_device(handle);
    input_unregister_handle(handle);

    pr_info("hs0038_handler: disconnected\n");
    kfree(handle);
}

static struct input_handler hs0038_handler = {
    .event      = hs0038_event,
    .match      = hs0038_match,
    .connect    = hs0038_connect,
    .disconnect = hs0038_disconnect,
    .name       = "hs0038_custom",
    .id_table   = hs0038_ids,
};

static int __init hs0038_handler_init(void)
{
    return input_register_handler(&hs0038_handler);
}

static void __exit hs0038_handler_exit(void)
{
    /* 输入核心会调用 disconnect()，清理已建立的连接。 */
    input_unregister_handler(&hs0038_handler);
}

module_init(hs0038_handler_init);
module_exit(hs0038_handler_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Custom input handler for hs0038");
```

### 7.1 为什么要 input_open_device

`input_register_handle()` 建立连接，但不等于已经开启事件接收。示例在 connect 中主动调用 `input_open_device()`，必要时还会触发硬件驱动设置的 `input_dev->open()`。

示例选择连接后立即接收；evdev 则通常根据用户是否打开 event 节点来管理输入连接的打开和关闭。

### 7.2 自定义 handler 与 evdev 可以共存

上述示例没有独占输入设备，同一输入事件可以分别到达 evdev 和自定义 handler。若某个连接通过抓取机制独占设备，事件分发情况会不同；普通观察用途无需主动抓取设备。

如果自定义 handler 中需要执行耗时或可能睡眠的工作，应把数据转交给工作队列等合适的执行上下文，而不是直接在事件回调中处理。

如果要向应用程序提供新的节点、数据格式、read/poll 接口，还需要额外实现相应机制。只注册 handler 不会自动生成自定义字符设备接口。

## 8. 原 HS0038 示例需要注意的实现问题

### 8.1 中断启用过早

原代码先 `request_irq()`，后分配和注册 `hs0038_input_dev`。中断一旦提前接收到完整数据，就可能通过空指针上报事件。

应先准备好输入设备和中断处理依赖的状态，再允许中断上报。具体资源申请顺序和失败回滚需要配套设计。

### 8.2 卸载时先停止事件来源

原代码先 `input_unregister_device()`，后 `free_irq()`，中间存在中断访问已释放输入设备的风险。

应先停止硬件事件来源，释放或同步中断，并处理可能仍在运行的工作项、定时器，再注销输入设备、释放其他资源。

### 8.3 检查失败返回值

需要检查 GPIO 获取、GPIO 转 IRQ、IRQ 申请、input 分配与注册，以及字符设备创建等返回值。原代码在 GPIO 获取失败后仍继续执行，不能只打印日志。

### 8.4 自定义字符设备路径也需要完善

原代码没有检查 `wait_event_interruptible()` 被信号中断的返回值，也没有检查 `copy_to_user()` 的结果。环形缓冲区涉及中断与进程上下文之间的并发，需要结合读者数量和内存可见性设计同步。

原来的 `poll()` 直接返回 0，尚未接入等待队列和就绪状态。这个问题属于 `/dev/myhs0038` 路径，不影响 evdev 自己提供的 poll 机制。

## 9. 如何选择实现方式

| 需求 | 适合的方式 |
|---|---|
| 应用程序识别遥控器按键并执行动作 | 硬件驱动注册 input_dev，应用读取 evdev |
| 多种输入设备统一提供标准事件 | 复用 input 核心与 evdev |
| 在内核中接收并处理指定输入设备的事件 | 根据需要实现自定义 input_handler |
| 教学或调试时读取原始红外协议数据 | 单独的调试接口或自定义字符设备，并明确数据格式 |

对于当前 HS0038 学习代码，先完成原始红外码到 `KEY_*` 的正确映射，准确声明按键能力，修正初始化与卸载顺序，再通过 evdev 检查事件，比直接增加自定义 handler 更有助于验证硬件驱动是否正确。
