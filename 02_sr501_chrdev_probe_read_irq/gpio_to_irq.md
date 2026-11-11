因为这段驱动不是从 SR501 设备节点读取中断，而是先获取 GPIO，再让 GPIO 子系统把这个 GPIO 转换成中断号：

```c
sr501_gpio = gpiod_get(&pdev->dev, NULL, 0);
irq = gpiod_to_irq(sr501_gpio);
```

调用链可以理解为：

```text
设备树 gpios 属性
        ↓
获得 GPIO4_IO19 的 gpio_desc
        ↓
gpiod_to_irq()
        ↓
GPIO4 控制器的 irq_domain
        ↓
得到 GPIO4_IO19 对应的 Linux IRQ
        ↓
request_irq()
```

真正的中断拓扑已经在 GPIO4 控制器节点中描述了。简化后类似：

```dts
gpio4: gpio@... {
    gpio-controller;
    #gpio-cells = <2>;

    interrupt-controller;
    #interrupt-cells = <2>;

    interrupts = <...>;
};
```

GPIO 控制器驱动注册时会建立 GPIO 引脚到 Linux IRQ 的映射。`gpiod_to_irq()` 根据 `sr501_gpio` 找到 GPIO4 控制器，再找到第 19 根 GPIO 对应的中断号。

因此 SR501 节点只写：

```dts
sr501 {
    compatible = "100ask,sr501";
    gpios = <&gpio4 19 GPIO_ACTIVE_HIGH>;
};
```

就足够了。

中断触发方式则由驱动明确指定：

```c
request_irq(irq, sr501_isr,
            IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
            "sr501", NULL);
```

也就是物理信号的上升沿和下降沿都会产生中断。由于驱动没有调用：

```c
platform_get_irq(pdev, 0);
```

或：

```c
of_irq_get(np, 0);
```

所以即使 SR501 节点写了 `interrupts`，当前驱动也不会读取它。

另外，代码建议写成带错误处理和自动资源释放的形式：

```c
sr501_gpio = devm_gpiod_get(&pdev->dev, NULL, GPIOD_IN);
if (IS_ERR(sr501_gpio))
    return PTR_ERR(sr501_gpio);

irq = gpiod_to_irq(sr501_gpio);
if (irq < 0)
    return irq;

ret = devm_request_irq(&pdev->dev, irq, sr501_isr,
                       IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
                       "sr501", pdev);
if (ret)
    return ret;
```

前提是该 GPIO 控制器支持中断。如果不支持，`gpiod_to_irq()` 会返回负错误码。还要注意，`GPIO_ACTIVE_HIGH` 描述 GPIO 的逻辑有效电平，而 `IRQF_TRIGGER_RISING/FALLING` 描述物理中断触发边沿，两者不是同一个配置。