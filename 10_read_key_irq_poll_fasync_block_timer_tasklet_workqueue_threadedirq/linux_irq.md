# Linux 中断上半部、下半部与多中断处理

## 1. 分析对象与结论

本文分析以下驱动：

```text
C:/Users/Jiang ZiXian/Desktop/github/Embedded_learning/
10_read_key_irq_poll_fasync_block_timer_tasklet_workqueue_threadedirq/
gpio_key_drv.c
```

这份代码是教学示例，它在同一个 GPIO 中断上同时演示了四种延后处理方式：

```text
GPIO 边沿
  -> gpio_key_isr()                 硬中断上半部
       |-> tasklet_schedule()       tasklet/softirq 上下文
       |-> mod_timer()              timer softirq 上下文，20 ms 去抖
       |-> schedule_work()          kworker 进程上下文
       `-> return IRQ_WAKE_THREAD
             `-> gpio_key_thread_func()  IRQ 内核线程上下文
```

真正向应用程序提交按键事件的路径只有：

```text
gpio_key_isr()
  -> mod_timer(..., jiffies + HZ/50)
  -> key_timer_expire()
  -> put_key()
  -> wake_up_interruptible()
  -> kill_fasync(SIGIO)
  -> 应用的 read/poll/SIGIO
```

tasklet、workqueue 和 threaded IRQ 在当前代码中只读取 GPIO 并打印日志，没有把按键值
送入缓冲区。因此，这四种机制不是依次组成一条处理流水线，而是由同一个上半部并行
触发的四条演示路径，彼此没有确定的执行顺序。

“Linux 禁止中断嵌套”也不能理解成系统一次只能处理一个中断。更准确的说法是：

- 现代 Linux 的普通硬中断处理函数通常在当前 CPU 本地 IRQ 关闭的 hardirq 上下文中
  执行，因此普通 IRQ 不会在同一个 CPU 上任意嵌套执行；
- 中断控制器会把其他到达的 IRQ 记录为 pending，当前 hardirq 返回并重新允许 IRQ 后，
  CPU 继续处理 pending IRQ；
- 其他 CPU 仍然可以同时处理自己的中断，所以多核系统中不同中断处理函数可以并发；
- NMI、SError 等更高异常级别不属于普通 IRQ，仍可能打断普通 hardirq；
- threaded IRQ 和 workqueue 已经是线程上下文，可以被硬中断打断，也可以按调度优先级
  与其他线程并发。

## 2. 为什么要区分上半部和下半部

外设发生中断时，CPU 暂停当前执行流，进入内核异常入口。硬中断期间通常不能调度、
不能睡眠，而且可能阻塞当前 CPU 对其他普通 IRQ 的响应。如果把耗时操作全部放在中断
处理函数中，会产生以下问题：

- 增大其他设备的中断响应延迟；
- 增大系统调度抖动；
- 长时间占用 CPU，影响实时性；
- 在不能睡眠的上下文中调用可能睡眠的 API，引发告警、死锁或崩溃。

因此常把处理拆成两部分：

### 2.1 上半部

上半部是注册给 IRQ core 的硬中断处理函数，例如本文件中的：

```c
static irqreturn_t gpio_key_isr(int irq, void *dev_id)
```

它应该只完成必须立即处理的工作：

- 判断是不是本设备产生的中断，共享 IRQ 时尤其重要；
- 读取并保存会被硬件覆盖的状态；
- 对需要驱动确认的设备清除/确认中断源；
- 必要时屏蔽设备中断；
- 调度延后处理；
- 尽快返回 `IRQ_HANDLED`、`IRQ_NONE` 或 `IRQ_WAKE_THREAD`。

本驱动的 GPIO IRQ 由 GPIO/中断控制器的通用 flow handler 完成控制器级确认，驱动上半部
主要调度延后工作。若换成具有自己中断状态寄存器的外设，则通常还必须在上半部读取并
清除该外设状态，否则电平中断可能持续有效，造成中断风暴。

### 2.2 下半部

“下半部”不是某一个固定 API，而是延后执行工作的统称。Linux 中常见机制包括：

- softirq；
- tasklet，构建在 softirq 上，现代内核已不建议新驱动继续使用；
- timer，回调通常运行在 timer softirq 上下文；
- workqueue，运行在 `kworker` 进程上下文；
- threaded IRQ，运行在该 IRQ 对应的内核线程中；
- 驱动自己创建的 kthread。

下半部不一定都能睡眠。tasklet 和 timer 仍属于原子/softirq 上下文；workqueue 和
threaded IRQ 才是可调度的进程上下文。

## 3. 各种执行上下文对比

| 机制 | 本文件函数 | 执行上下文 | 能否睡眠 | 是否可能被普通硬 IRQ 打断 | 典型用途 |
|---|---|---|---|---|---|
| 硬中断上半部 | `gpio_key_isr` | hardirq | 不能 | 同 CPU 通常不能被普通 IRQ 嵌套；可被 NMI 等打断 | 确认硬件、保存状态、调度后续 |
| tasklet | `key_tasklet_func` | softirq | 不能 | 可以 | 很短的原子延后处理；新代码不推荐 |
| timer | `key_timer_expire` | timer softirq | 不能 | 可以 | 延时触发、超时、简单去抖 |
| workqueue | `key_work_func` | `kworker` 进程上下文 | 可以 | 可以 | 可能睡眠或相对耗时的处理 |
| threaded IRQ | `gpio_key_thread_func` | `irq/<n>-name` 内核线程 | 可以 | 可以 | 设备主要处理、可睡眠总线访问 |
| 字符设备 read | `gpio_key_drv_read` | 用户进程的系统调用上下文 | 可以 | 可以 | 等待数据、复制到用户空间 |

“可以睡眠”只表示上下文允许调度，不表示所有被调用 API 都适合无限期阻塞。IRQ thread
和 workqueue 仍应控制执行时间，避免持续积压。

## 4. Linux 禁止普通 IRQ 嵌套时如何处理多个中断

### 4.1 单 CPU 上的基本过程

假设 IRQ A 正在执行时 IRQ B 到达：

```text
时间 ->

CPU 正常执行
    |
    +-- IRQ A 到达
          |
          +-- CPU 进入异常入口，本地普通 IRQ 被屏蔽
          +-- 中断控制器确认 IRQ A
          +-- 执行 A 的 hardirq handler
          |
          +-- IRQ B 到达
          |     `-- 中断控制器把 B 标为 pending
          |
          +-- A 返回，irq_exit，恢复本地 IRQ
                `-- CPU 接收并处理 pending 的 IRQ B
```

因此，B 通常不是丢失，而是延后。具体先处理哪个 pending IRQ，由中断控制器优先级、
CPU 路由/亲和性以及内核的 IRQ flow handler 决定。

### 4.2 边沿中断与电平中断的区别

本驱动使用：

```c
IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING
```

表示 GPIO 上升沿和下降沿都触发，属于边沿事件。中断控制器通常锁存边沿并设置 pending。
但如果同一 IRQ 在被屏蔽期间发生多个边沿，硬件可能只保留“至少发生过一次”，不保证
保存每个边沿的计数。按键抖动本来就不应被逐个上报，因此本驱动用定时器主动合并这些
边沿。

电平中断只要设备保持有效电平，解除屏蔽后仍会再次触发。驱动必须清除产生该电平的
设备状态，然后再允许 IRQ，否则会反复进入处理函数。

### 4.3 多核系统不是全局禁止中断

`local_irq_disable()` 或异常入口的 IRQ 屏蔽只作用于当前 CPU，不会关闭其他 CPU。
例如：

```text
CPU0: 正在处理 key0 的 IRQ
CPU1: 可以同时处理网卡 IRQ 或 key1 的 IRQ
```

IRQ affinity 决定某个 IRQ 可以发送到哪些 CPU。不同 IRQ handler 可以在不同 CPU 上
同时执行，所以共享数据仍然需要 SMP 同步。不能因为“本地中断关闭”就认为全局变量
天然安全。

### 4.4 同一个 IRQ 的再次到达

IRQ core 和中断控制器会对同一 IRQ 描述符进行状态管理、确认和必要的 mask，避免同一
IRQ action 在同一 CPU 上无控制地递归进入。再次到达通常变成 pending，稍后重新处理。
对于线程化中断，pending/wake 标志也可能把短时间内的多次事件合并，而不是为每个边沿
创建一个新线程。

如果业务必须精确统计每一个高速事件，不能只依赖普通 GPIO IRQ 加日志或 tasklet；应
使用硬件计数器、FIFO、时间戳单元或在上半部读取不会丢失的设备事件计数。

### 4.5 仍然可能发生的“嵌套”

- NMI 等高优先级异常可以打断普通 hardirq；
- hardirq 可以打断 softirq、timer、workqueue、IRQ thread 和用户进程；
- 不同 CPU 可以并行执行 hardirq；
- PREEMPT_RT 内核会尽可能把普通 IRQ 强制线程化，执行模型与普通内核不同，但极短的
  硬件确认部分仍需在不可睡眠上下文完成；
- 使用 `IRQF_NO_THREAD` 的特殊 IRQ 不会被强制线程化。

因此“Linux 完全没有中断嵌套”是不准确的；应说“现代普通内核避免同一 CPU 上普通
hardirq 的任意嵌套，把其他 IRQ 暂存为 pending，同时仍允许跨 CPU 并行和更高异常级别
抢占”。

## 5. 本驱动从注册到中断发生的完整过程

### 5.1 probe 阶段

设备树匹配 `compatible = "100ask,gpio_key"` 后，platform core 调用：

```c
gpio_key_probe(struct platform_device *pdev)
```

对每个 GPIO，代码完成：

1. `of_get_gpio_flags()`：取得旧式 GPIO 编号和设备树标志；
2. `gpio_to_desc()`：转换成 `gpio_desc`；
3. `gpio_to_irq()`：取得 Linux 虚拟 IRQ 号；
4. `setup_timer()`/`add_timer()`：创建每个按键独立的去抖定时器；
5. `tasklet_init()`：创建每个按键独立的 tasklet；
6. `INIT_WORK()`：创建每个按键独立的 work；
7. `request_threaded_irq()`：注册硬中断 handler 和线程 handler。

实际注册调用是：

```c
request_threaded_irq(
    gpio_keys_100ask[i].irq,
    gpio_key_isr,
    gpio_key_thread_func,
    IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
    "100ask_gpio_key",
    &gpio_keys_100ask[i]);
```

参数含义：

- `irq`：Linux IRQ 号；
- `gpio_key_isr`：primary handler，在 hardirq 上下文执行；
- `gpio_key_thread_func`：thread_fn，在 IRQ 内核线程中执行；
- flags：上升沿、下降沿都触发；
- name：显示在 `/proc/interrupts` 和线程名中；
- `dev_id`：传回 handler 的按键对象，也是 `free_irq()` 匹配该 action 的身份。

这里没有 `IRQF_SHARED`，所以不是共享 IRQ 注册。即使不共享，使用每个按键唯一的
`dev_id` 仍然是正确做法。

### 5.2 一个边沿到来时

假设按键对应 GPIO 从高变低：

1. GPIO 控制器检测下降沿，向中断控制器置 pending；
2. 中断控制器把 IRQ 送到目标 CPU；
3. CPU 进入 IRQ 异常入口；
4. Linux 根据硬件 IRQ 映射找到 `irq_desc`；
5. GPIO/IRQ chip flow handler 完成控制器级 ack/mask；
6. generic IRQ core 调用 `gpio_key_isr(irq, dev_id)`；
7. `dev_id` 被还原成当前 `struct gpio_key`；
8. 上半部分别调度 tasklet、重设 timer、调度 work；
9. 上半部返回 `IRQ_WAKE_THREAD`；
10. IRQ core 标记并唤醒该 action 的 IRQ thread；
11. hardirq 退出，恢复 CPU 执行并处理后续 pending IRQ/softirq；
12. 四条延后路径按各自调度条件运行。

### 5.3 上半部逐行分析

原函数：

```c
static irqreturn_t gpio_key_isr(int irq, void *dev_id)
{
    struct gpio_key *gpio_key = dev_id;
    tasklet_schedule(&gpio_key->tasklet);
    mod_timer(&gpio_key->key_timer, jiffies + HZ/50);
    schedule_work(&gpio_key->work);
    return IRQ_WAKE_THREAD;
}
```

#### `tasklet_schedule()`

把该 tasklet 标为待运行，并触发 `TASKLET_SOFTIRQ`。它不会在这一行同步调用
`key_tasklet_func()`。同一个 tasklet 在已经 pending 时再次 schedule 通常会合并，
不会按调用次数无限排队。

同一个 tasklet 实例不会与自身并发运行，但不同按键有不同 tasklet，在 SMP 上仍可能
并行。tasklet 回调不能睡眠。

#### `mod_timer(..., jiffies + HZ/50)`

把该按键定时器的到期时间设置为当前时间后约 20 ms：

```text
HZ/50 秒 = 20 ms
```

如果定时器已经 pending，`mod_timer()` 会修改原定时器，而不是新增一个定时器。因此每次
抖动边沿都会把到期时间推迟到“最后一个边沿之后约 20 ms”。这就是当前代码真正的按键
去抖逻辑。

定时器回调运行在 softirq/原子上下文，不能睡眠。`mod_timer()` 可从 hardirq 调用。

#### `schedule_work()`

把 `gpio_key->work` 提交到系统 workqueue，稍后由 `kworker` 执行
`key_work_func()`。同一个 work 已经 pending 时，再次 `schedule_work()` 通常返回 false
并合并请求。workqueue 回调是进程上下文，可以使用可能睡眠的接口。

#### `return IRQ_WAKE_THREAD`

因为 `request_threaded_irq()` 注册了 `gpio_key_thread_func`，返回 `IRQ_WAKE_THREAD`
通知 IRQ core 唤醒对应的 IRQ thread。若注册的是普通 `request_irq()`，或者 thread_fn
为 NULL，则不能靠这个返回值获得线程处理。

### 5.4 四条延后路径的执行顺序

不存在下面这种固定顺序：

```text
tasklet -> timer -> work -> IRQ thread
```

更可能的情况是：

- tasklet 在 hardirq 返回后的 softirq 阶段很快运行；
- IRQ thread 被调度器唤醒后运行；
- `kworker` 获得 CPU 后运行 work；
- timer 至少等到约 20 ms 后才运行；
- 但 CPU 负载、IRQ affinity、内核配置和 PREEMPT_RT 都可能改变前三者的先后关系；
- 不同 CPU 上甚至可能并行。

因此不能用四个 `printk()` 的偶然顺序推导内核保证的顺序。

## 6. 真正的按键数据路径

### 6.1 去抖定时器

20 ms 内不再有新边沿后，`key_timer_expire()` 执行：

```c
val = gpiod_get_value(gpio_key->gpiod);
key = (gpio_key->gpio << 8) | val;
put_key(key);
wake_up_interruptible(&gpio_key_wait);
kill_fasync(&button_fasync, SIGIO, POLL_IN);
```

它读取稳定后的 GPIO 电平，把 GPIO 号放在高 8 位、电平放在低 8 位，然后：

- 写入全局环形缓冲区；
- 唤醒阻塞在 `read()` 中的进程；
- 让 `poll/select` 重新检查设备可读状态；
- 向启用 `FASYNC` 的应用发送 `SIGIO`。

因为上下两个边沿都触发，稳定的按下和释放都可能形成事件。代码保存了
`OF_GPIO_ACTIVE_LOW` 到 `flag`，但后续没有用 `flag` 归一化按下/释放语义，因此目前
提交的是读取到的电平，而不是明确的 `pressed=true/false`。

### 6.2 阻塞 read

当环形缓冲为空时：

```c
wait_event_interruptible(gpio_key_wait, !is_key_buf_empty());
```

当前用户线程进入可中断睡眠。定时器调用 `wake_up_interruptible()` 后，等待宏重新检查
条件；条件为真才继续 `get_key()` 和 `copy_to_user()`。

### 6.3 poll/select

```c
poll_wait(fp, &gpio_key_wait, wait);
return is_key_buf_empty() ? 0 : POLLIN | POLLRDNORM;
```

`poll_wait()` 的含义不是把驱动线程放进 workqueue，也不会在此处直接睡眠。它把当前
poll 调用所使用的等待项登记到 `gpio_key_wait`；真正是否睡眠由 VFS poll/select 核心在
所有 fd 都检查完成后决定。

### 6.4 fasync/SIGIO

应用通过 `fcntl(F_SETOWN)` 和 `fcntl(F_SETFL, O_ASYNC)` 建立异步通知关系，VFS 调用：

```c
gpio_key_drv_fasync()
  -> fasync_helper(..., &button_fasync)
```

定时器回调中的 `kill_fasync()` 向已登记进程发送 `SIGIO`。SIGIO 只表示“状态可能变化”，
应用仍应通过 `read()` 取走缓冲区数据，不能把一个信号严格等同于一个按键边沿。

## 7. 多按键和按键抖动时会发生什么

### 7.1 两个不同按键同时触发

每个按键有自己的：

- IRQ 号；
- timer；
- tasklet；
- work；
- threaded IRQ action/thread。

如果两个 IRQ 被路由到同一 CPU，它们的 hardirq 上半部通常依次执行，第二个保持
pending。如果 IRQ affinity 允许它们发送到不同 CPU，则两个上半部可以同时执行。

两者最终都向全局 `g_keys/r/w` 环形缓冲写数据。当前代码没有 spinlock，因此多核上两个
timer 回调并发 `put_key()`，或者 timer 写入时用户进程执行 `get_key()`，存在数据竞争。

### 7.2 同一个按键快速抖动

假设 10 ms 内出现多个升降沿：

- `gpio_key_isr()` 可能被执行多次；
- tasklet schedule 可能合并；
- 同一个 work pending 时 schedule 可能合并；
- IRQ thread 的重复唤醒也可能合并；
- 每次 `mod_timer()` 都把 20 ms 到期点向后推；
- 最终 timer 通常只在最后一个边沿稳定 20 ms 后执行一次；
- timer 读取的是最终电平，而不是依次回放全部抖动边沿。

这正适合机械按键去抖，但说明日志中四种回调的次数不应被当作按键次数。

### 7.3 环形缓冲满

```c
if (!is_key_buf_full())
    ...
```

缓冲满时新按键被静默丢弃，没有计数或错误状态。中断仍然已经处理，应用无法知道发生
过溢出。正式驱动应至少记录 overflow 计数，必要时定义丢旧数据还是丢新数据的策略。

## 8. 为什么不同下半部的限制不同

### 8.1 tasklet 和 timer 不能睡眠

它们运行在 softirq 上下文，没有可供阻塞后恢复的普通进程语义。以下操作不应在其中
使用：

- `mutex_lock()`；
- `msleep()`；
- 可能阻塞的 I2C/SPI 传输；
- `GFP_KERNEL` 内存分配；
- `copy_to_user()`。

应使用自旋锁、原子操作和不会睡眠的 API，并保持回调很短。

### 8.2 workqueue 和 threaded IRQ 可以睡眠

两者都有 `current` 对应的内核线程，所以示例能打印：

```c
current->comm, current->pid
```

如果 GPIO 来自 I2C/SPI GPIO 扩展器，读取电平可能睡眠，应在 workqueue 或 threaded IRQ
中使用：

```c
gpiod_get_value_cansleep()
```

不能在 hardirq、tasklet 或 timer 中调用它。当前代码使用 `gpiod_get_value()`，只适用于
不需要睡眠的 SoC 本地 GPIO controller。可通过 `gpiod_cansleep()` 判断该 descriptor
是否允许在原子上下文读取。

## 9. 这份示例代码需要注意的问题

这些问题不影响理解教学目的，但不能直接忽略后用于生产驱动。

### 9.1 同时使用四种下半部是重复演示

一个按键中断通常选择一种主要策略即可：

- 简单本地 GPIO 去抖：上半部 + timer；
- GPIO 读取可能睡眠：threaded IRQ 或 delayed work；
- 复杂设备处理：上半部保存状态 + workqueue/threaded IRQ。

当前代码同时触发 tasklet、timer、work 和 IRQ thread，只适合对比执行上下文，会产生
重复 GPIO 读取和大量日志。

### 9.2 全局环形缓冲缺少同步

`g_keys`、`r`、`w` 被 timer/softirq 和进程上下文访问，多按键、多 CPU 下存在竞争。
可使用 `spin_lock_irqsave()` 保护 put/get/empty/full，或者采用带 spinlock 的 kfifo。

等待条件检查也必须与缓冲同步方式一致，避免编译器/CPU 内存顺序造成可见性问题。

### 9.3 卸载时没有同步取消 work 和 timer

当前 remove 使用：

```c
free_irq(...);
del_timer(...);
tasklet_kill(...);
kfree(gpio_keys_100ask);
```

风险包括：

- `del_timer()` 不保证正在另一个 CPU 执行的 timer callback 已结束；
- 没有 `cancel_work_sync()`，work 可能在 `kfree()` 后访问 `gpio_key`；
- 正在运行的回调可能形成 use-after-free。

典型安全顺序是先阻止新 IRQ，再同步取消所有延后工作：

```c
free_irq(key->irq, key);        /* 等待该 IRQ action/线程退出 */
del_timer_sync(&key->key_timer);
tasklet_kill(&key->tasklet);
cancel_work_sync(&key->work);
```

然后才能释放 `gpio_key`。具体顺序还应结合回调是否会互相重新调度。

### 9.4 threaded IRQ 没有 `IRQF_ONESHOT`

当前是边沿 GPIO，primary handler 又很短，未必立即造成错误。但如果 thread_fn 需要在
处理期间保持该 IRQ line 屏蔽，通常要使用 `IRQF_ONESHOT`：

```c
request_threaded_irq(irq, handler, thread_fn,
    IRQF_ONESHOT | IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
    name, dev_id);
```

如果 primary handler 返回 `IRQ_WAKE_THREAD` 而没有可靠地清除/屏蔽持续有效的设备中断，
电平触发设备可能在 IRQ thread 尚未处理完时再次触发。

### 9.5 `printk()` 不适合高频中断路径

大量 printk 会显著改变时序，甚至让本来不存在的延迟和合并现象出现。调试时应使用
限频日志、tracepoint、ftrace 或计数器。不要用日志先后顺序证明调度保证。

### 9.6 API 具有旧内核版本特征

代码中的：

```c
setup_timer(timer, callback, unsigned_long_data);
tasklet_init(tasklet, callback, unsigned_long_data);
```

属于较旧接口。现代内核通常使用 `timer_setup()` 和 `from_timer()`；tasklet 也处于逐步
淘汰方向，新驱动优先 threaded IRQ、workqueue 或其他明确所有权的机制。分析旧教学
代码时要以其目标内核版本为准，不能直接复制到新内核树。

### 9.7 其他健壮性问题

- `request_threaded_irq()` 循环只保留最后一次 `err`，没有逐个检查和回滚；
- probe 中途失败时已分配 GPIO key、timer、IRQ 可能泄漏；
- `wait_event_interruptible()` 返回值没有检查，信号唤醒后仍可能继续读；
- read 没检查 `size >= sizeof(key)`，也没有处理 `copy_to_user()` 失败；
- 缺少 `.release` 中的 `fasync_helper(..., 0, ...)` 清理；
- ACTIVE_LOW 标志保存后没有用于按键语义转换；
- 缓冲满时没有 overflow 统计。

## 10. 更清晰的实现方式示例

以下代码只是帮助理解设计，不是对原文件的实际修改。

### 10.1 方案 A：硬中断只重设去抖定时器

适用于 `gpiod_cansleep() == false` 的本地 GPIO：

```c
static irqreturn_t gpio_key_isr(int irq, void *dev_id)
{
    struct gpio_key *key = dev_id;

    mod_timer(&key->key_timer, jiffies + msecs_to_jiffies(20));
    return IRQ_HANDLED;
}
```

20 ms 后 timer 读取稳定电平并提交事件。它已经完成当前代码的实际功能，不需要再同时
调度 tasklet、work 和 IRQ thread。

### 10.2 方案 B：使用 threaded IRQ 去抖

适合 GPIO 读取可能睡眠，或者希望处理逻辑都放在线程上下文：

```c
static irqreturn_t gpio_key_isr(int irq, void *dev_id)
{
    return IRQ_WAKE_THREAD;
}

static irqreturn_t gpio_key_thread(int irq, void *dev_id)
{
    struct gpio_key *key = dev_id;
    int value;

    msleep(20);
    value = gpiod_get_value_cansleep(key->gpiod);
    if (value < 0)
        return IRQ_HANDLED;

    /* 加锁写入 FIFO，然后唤醒 read/poll/fasync */
    return IRQ_HANDLED;
}

request_threaded_irq(irq, gpio_key_isr, gpio_key_thread,
    IRQF_ONESHOT | IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
    "gpio-key", key);
```

`IRQF_ONESHOT` 使 IRQ thread 完成前该 IRQ 保持屏蔽。对于机械按键，屏蔽期间丢弃抖动
边沿通常正是期望行为。是否适合具体 GPIO controller 仍需结合设备树和硬件测试。

### 10.3 方案 C：delayed work

如果去抖后还要执行可能睡眠的操作，可从上半部调度 delayed work：

```c
static irqreturn_t gpio_key_isr(int irq, void *dev_id)
{
    struct gpio_key *key = dev_id;

    mod_delayed_work(system_wq, &key->debounce_work,
                     msecs_to_jiffies(20));
    return IRQ_HANDLED;
}
```

重复边沿会把 delayed work 推迟到最后一个边沿后 20 ms，回调在 kworker 中运行，可以
调用 `gpiod_get_value_cansleep()`。

## 11. 如何观察实际执行过程

### 11.1 查看中断计数和 CPU 分布

```bash
cat /proc/interrupts
watch -n 0.5 cat /proc/interrupts
```

找到 `100ask_gpio_key` 行，可以看到每个 CPU 处理的次数。按下一次出现多个计数通常是
机械抖动以及同时监听上下沿造成的，不等于用户应该收到多个有效按键事件。

### 11.2 查看 IRQ thread 和 kworker

```bash
ps -eLo pid,tid,psr,cls,rtprio,pri,comm | grep -E 'irq/|kworker'
```

`gpio_key_thread_func()` 中的 `current->comm` 通常类似 `irq/<irq>-100ask_gpio_key`，
`key_work_func()` 则运行在某个 `kworker/...` 中。

### 11.3 使用 ftrace 观察 IRQ，而不是依赖 printk

挂载 debugfs 后：

```bash
mount -t debugfs none /sys/kernel/debug
cd /sys/kernel/debug/tracing
echo 0 > tracing_on
echo > trace
echo 1 > events/irq/irq_handler_entry/enable
echo 1 > events/irq/irq_handler_exit/enable
echo 1 > events/irq/softirq_entry/enable
echo 1 > events/irq/softirq_exit/enable
echo 1 > tracing_on
cat trace_pipe
```

按键后可以看到 hardirq 和 softirq 的时间关系。若内核启用了对应 tracepoint，还可以
启用 timer、workqueue 和 sched 事件观察 timer 到期、work 执行及 IRQ thread 调度。

调试结束后关闭事件，避免长期产生跟踪开销：

```bash
echo 0 > tracing_on
echo 0 > events/irq/irq_handler_entry/enable
echo 0 > events/irq/irq_handler_exit/enable
echo 0 > events/irq/softirq_entry/enable
echo 0 > events/irq/softirq_exit/enable
```

### 11.4 验证 20 ms 去抖

应分别记录：

- GPIO IRQ 第一次和最后一次边沿时间；
- `key_timer_expire()` 执行时间；
- 用户 read/poll/SIGIO 收到通知的时间；
- 定时器是否约在最后一个边沿 20 ms 后执行；
- 一次稳定按下/释放分别产生多少应用事件；
- 两个按键同时操作时缓冲是否丢失或乱序。

由于普通 Linux timer 以 jiffies/调度时机运行，`HZ/50` 表示“不早于目标 tick 附近到期”，
不保证严格等于 20.000 ms。高负载时回调可以更晚。

## 12. 一次按键的完整时序示意

```text
用户按键，GPIO 下降沿
        |
        v
GPIO/IRQ controller 设置 pending
        |
        v
CPU IRQ exception entry（当前 CPU 普通 IRQ 屏蔽）
        |
        v
generic IRQ core -> gpio_key_isr()                 [hardirq，不能睡眠]
        |              |              |
        |              |              +-> schedule_work()
        |              +-> mod_timer(now + 20 ms)
        +-> tasklet_schedule()
        |
        `-> IRQ_WAKE_THREAD
        |
        v
hardirq 返回，其他 pending IRQ 可以继续处理
        |
        +-> key_tasklet_func()                     [softirq，只打印]
        +-> gpio_key_thread_func()                 [IRQ thread，只打印]
        +-> key_work_func()                        [kworker，只打印]
        |
        `-> 期间若继续抖动：再次进 ISR，timer 到期点后移

最后一个边沿后约 20 ms
        |
        v
key_timer_expire()                                 [timer softirq]
        |
        +-> 读取稳定 GPIO 电平
        +-> put_key() 写环形缓冲
        +-> wake_up_interruptible() 唤醒 read/poll
        `-> kill_fasync() 发送 SIGIO
```

## 13. 最终理解

1. 上半部的本质是“处理不能推迟的最小工作”，不是所有中断逻辑都放在 ISR。
2. 下半部的本质是“延后执行”，但 tasklet/timer 仍不能睡眠，workqueue/threaded IRQ
   才是进程上下文。
3. 当前 CPU 禁止普通 IRQ 嵌套时，其他 IRQ 由控制器保持 pending，稍后继续处理；
   多核 CPU 仍可并发处理其他 IRQ。
4. 本文件的一次 IRQ 同时演示四条延后路径，它们没有固定顺序，也不保证每个抖动边沿
   都对应一次回调。
5. 当前驱动真正产生用户按键事件的是“ISR -> 20 ms timer -> 环形缓冲/等待队列/SIGIO”。
6. 生产代码通常只选择一种合适的延后策略，并补齐 SMP 锁、同步卸载、错误回滚和
   缓冲溢出统计。

