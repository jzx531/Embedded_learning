# GPIO 按键驱动结构与运行逻辑

> 对应源码：`gpio_key_drv.c`
> 这是一个综合演示 Linux 驱动机制的示例：**字符设备 + platform 总线 + 中断（线程化）+ 定时器去抖 + tasklet + workqueue + 阻塞读 + poll + fasync**。

---

## 一、驱动整体结构

### 1.1 数据与资源结构

```text
+---------------------------------------------------------------+
| struct gpio_key                                               |
|   .gpio       GPIO 编号                                        |
|   .gpiod      GPIO 描述符                                       |
|   .flag       GPIO 标志（是否低电平有效）                          |
|   .irq        中断号                                            |
|   .key_timer  去抖定时器 (timer_list)                           |
|   .tasklet    tasklet 下半部                                    |
|   .work       workqueue 下半部                                  |
+---------------------------------------------------------------+
         ^
         | 按 GPIO 数量分配数组
         |
+---------------------------------------------------------------+
| static struct gpio_key *gpio_keys_100ask;   // 设备数组          |
| static int major;                           // 主设备号          |
| static struct class *gpio_key_class;        // 设备类            |
| static int g_keys[BUF_LEN]; static int r, w;// 环形缓冲区        |
| struct fasync_struct *button_fasync;        // 异步通知队列      |
| DECLARE_WAIT_QUEUE_HEAD(gpio_key_wait);     // 读等待队列        |
+---------------------------------------------------------------+
```

### 1.2 关键函数一览

| 函数 | 角色 |
|------|------|
| `gpio_key_isr` | 中断上半部：调度 tasklet / 定时器 / workqueue，返回 `IRQ_WAKE_THREAD` |
| `gpio_key_thread_func` | 线程化中断的处理线程 |
| `key_timer_expire` | 定时器回调：去抖后读取按键、写缓冲区、唤醒等待、发异步通知 |
| `key_tasklet_func` | tasklet 下半部 |
| `key_work_func` | workqueue 下半部 |
| `gpio_key_drv_read` | 阻塞读按键值 |
| `gpio_key_drv_poll` | 支持 select/poll |
| `gpio_key_drv_fasync` | 支持异步通知 |
| `gpio_key_probe` / `gpio_key_remove` | 设备匹配/卸载 |

### 1.3 文件操作接口

```text
file_operations gpio_key_drv
  .owner   = THIS_MODULE
  .read    = gpio_key_drv_read
  .poll    = gpio_key_drv_poll
  .fasync  = gpio_key_drv_fasync
```

### 1.4 下半部机制对比（为什么 tasklet 和 workqueue 都有）

本驱动是**教学示例**，故意同时演示几种下半部机制，而不是实际需要两者都上。二者的区别：

| | tasklet | workqueue |
|---|---|---|
| 运行上下文 | 软中断上下文（原子，不能休眠） | 进程上下文（可休眠） |
| 能否睡眠/阻塞 | 不能 | 能 |
| 典型用途 | 极简短、不能睡觉的操作 | 较耗时、可能睡眠的操作 |

所以 `gpio_key_isr` 里同时调度了 tasklet、workqueue、定时器、线程化中断四种下半部，纯粹是为了在一段代码里把「用一个程序总结驱动机制」都演示出来。实际工程里按键去抖用**定时器**就够，根本不需要 tasklet 和 workqueue 同时存在。

---

## 二、驱动注册流程（platform 总线）

```text
module_init(gpio_key_init)
        |
        v
platform_driver_register(&gpio_keys_driver)
        |
        |  (驱动名 / compatible 与设备树匹配)
        v
gpio_key_probe(pdev)
        |
        |-- of_gpio_count(node)           得到 GPIO 数量
        |-- kzalloc                        分配 gpio_key 数组
        |-- 循环初始化每个按键:
        |     of_get_gpio_flags            获取 GPIO 编号与标志
        |     gpio_to_desc / gpio_to_irq   得到描述符与中断号
        |     setup_timer + add_timer       去抖定时器
        |     tasklet_init                  tasklet
        |     INIT_WORK                    workqueue
        |
        |-- request_threaded_irq           注册线程化中断(双边沿触发)
        |
        |-- register_chrdev               注册字符设备
        |-- class_create                  创建设备类
        |-- device_create                 创建设备节点 /dev/100ask_gpio_key
        |
        v
     return 0
```

### 2.1 request_threaded_irq 说明

```c
request_threaded_irq(irq, handler, thread_fn, flags, name, dev_id)
```

注册一个**线程化中断**，把中断处理分成两部分：

- `handler`（此处为 `gpio_key_isr`）：中断**上半部**（硬中断上下文），中断一发生立即执行，必须极快。它返回 `IRQ_WAKE_THREAD`，通知内核「唤醒线程处理剩余工作」。
- `thread_fn`（此处为 `gpio_key_thread_func`）：中断**下半部线程**（内核线程、进程上下文），由内核唤醒后执行，可以睡眠、做耗时操作。

本调用里：

- `IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING`：上升沿和下降沿都触发（按下、松开都会进中断）。
- `"100ask_gpio_key"`：中断名（`/proc/interrupts` 里可见）。
- `&gpio_keys_100ask[i]`：作为 `dev_id` 传给处理函数。

对比普通 `request_irq`：它只有一个 handler，全部在硬中断上下文完成；而 `request_threaded_irq` 把「快速响应」和「耗时处理」分开，减少中断响应延迟。

---

## 三、运行逻辑流程

### 3.1 按键按下 → 数据到达应用层

```text
硬件按键按下/松开
        |
        v
中断触发(上升沿/下降沿) --> gpio_key_isr  (中断上半部)
        |
        +-- tasklet_schedule()   --> key_tasklet_func   (下半部: tasklet)
        |
        +-- mod_timer(jiffies+HZ/50)                      (重新定时去抖)
        |
        +-- schedule_work()      --> key_work_func       (下半部: workqueue)
        |
        +-- return IRQ_WAKE_THREAD
                |
                v
        gpio_key_thread_func      (内核线程, 线程化中断处理)
                |
                | 打印电平值, return IRQ_HANDLED
                v
        定时器到期 key_timer_expire  (去抖完成)
                |
                |-- gpiod_get_value()        读取稳定电平
                |-- key = (gpio<<8) | val     打包按键值
                |-- put_key(key)              写入环形缓冲区
                |-- wake_up_interruptible()   唤醒阻塞的 read 进程
                |-- kill_fasync(SIGIO)        向应用层发异步信号
```

> **注意**：`gpio_key_isr` 里不是「调用」tasklet/workqueue 回调，而是**调度（排入队列）**，都是异步、延迟执行的：
>
> - `tasklet_schedule()`：把 tasklet 标记为待执行，稍后在**软中断**上下文执行 `key_tasklet_func`。
> - `schedule_work()`：把 work 加入工作队列，由**内核工作线程**稍后执行 `key_work_func`。
>
> 所以 `gpio_key_isr` 本身并没有同步运行这两个回调，只是「登记」任务后立刻 `return IRQ_WAKE_THREAD`，真正的回调在 isr 返回后由不同上下文异步触发。

### 3.1.1 一次中断的打印结果

假设 GPIO 编号为 `115`，按下去抖动后的电平 `val=0`，典型打印顺序：

```text
key_tasklet_func key 115 0                          ← tasklet：软中断，中断返回后几乎立刻执行
gpio_key_thread_func: the process is irq/xxx-100ask_gpio_key pid 123    ← 线程化中断线程
gpio_key_thread_func key 115 0
key_work_func: the process is kworker/u8:1 pid 45   ← 工作队列线程
key_work_func key 115 0
key_timer_expire key 115 0                          ← 定时器约 20ms 后到期(去抖完成)
```

要点：

1. `gpio_key_isr` 里的 `printk` 被注释了，所以**硬中断本身不打印**。
2. **tasklet 最先**：它跑在软中断上下文，硬中断返回时几乎立即执行。
3. 线程化中断线程 `irq/xxx-100ask_gpio_key` 和 `kworker` 工作线程的执行顺序**不固定**，由调度器决定，可能互换。
4. **定时器最后**：`mod_timer(..., jiffies + HZ/50)` 是在约 20ms 之后才到期，这是去抖等待期。

注意：`tasklet_func` 和 `work_func` 里只是读了电平打印，并没有写入缓冲区；真正把按键值送出去的是 `key_timer_expire`，最终能唤醒 read 的也是定时器这条路径。

### 3.2 应用层读取按键值（三种方式）

**方式一：阻塞读（read）**

```text
app 调用 read()
      |
      v
gpio_key_drv_read
      |-- 缓冲区空且 O_NONBLOCK?  --> 返回 -EAGAIN
      |-- wait_event_interruptible(gpio_key_wait, !empty)  阻塞休眠
      |     (被 key_timer_expire 的 wake_up 唤醒)
      |-- get_key()                    从环形缓冲区取键值
      |-- copy_to_user()               拷贝到用户空间
      v
返回 4 字节按键值
```

**方式二：多路复用（poll）**

```text
app 调用 select/poll
      |
      v
gpio_key_drv_poll
      |-- poll_wait()                   挂到等待队列
      |-- 缓冲区非空? 返回 POLLIN|POLLRDNORM : 返回 0
```

**方式三：异步通知（fasync）**

```text
app 调用 fcntl(F_SETFL, O_ASYNC)
      |
      v
gpio_key_drv_fasync --> fasync_helper()  登记异步通知
      |
      | 当有按键数据时:
      v
key_timer_expire --> kill_fasync(SIGIO, POLL_IN)  发送 SIGIO 信号给应用层
```

---

## 四、数据流总结

```text
       硬件中断
          |
          v
  +-------------------+
  |  中断上半部 isr    |  --- 调度 --->  tasklet / workqueue / 定时器 / 线程化中断
  +-------------------+
          |
          v
  +-------------------+      +------------------+
  |  定时器去抖回调     | ---> | 环形缓冲区        |
  |  key_timer_expire  |      |  g_keys[]        |
  +-------------------+      +------------------+
          |                        |
          | wake_up / kill_fasync  | read/poll/fasync
          v                        v
   等待队列/异步通知             应用层进程
```

---

## 五、卸载流程

```text
module_exit(gpio_key_exit)
        |
        v
platform_driver_unregister(&gpio_keys_driver)
        |
        v
gpio_key_remove(pdev)
        |-- device_destroy / class_destroy / unregister_chrdev
        |-- free_irq / del_timer / tasklet_kill
        |-- kfree(gpio_keys_100ask)
```
