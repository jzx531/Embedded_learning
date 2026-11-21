# RK3568 运行时设备树与设备完整索引

数据来源：`rk3568-inventory.json`。节点未写 status 时按规范解释为 okay；父节点禁用会使子节点不可用。okay 只表示配置允许，驱动链接及启动日志才反映枚举/探测情况。

## 设备树全部节点

| 节点路径 | compatible | 本节点 status | 按祖先判断的 status | sysfs 设备 / 驱动 |
|---|---|---|---|---|
| / | rockchip,rk3568-kickpi-k1a, rockchip,rk3568 | 未声明 | okay |  |
| /adc-keys | adc-keys | 未声明 | okay | platform:adc-keys -> adc_keys |
| /adc-keys/vol-up-key |  | 未声明 | okay |  |
| /aliases |  | 未声明 | okay |  |
| /arm-pmu | arm,cortex-a55-pmu, arm,armv8-pmuv3 | 未声明 | okay | platform:arm-pmu -> armv8-pmu |
| /audiopwmout-diff | simple-audio-card | disabled | disabled @ /audiopwmout-diff |  |
| /audiopwmout-diff/simple-audio-card,codec |  | 未声明 | disabled @ /audiopwmout-diff |  |
| /audiopwmout-diff/simple-audio-card,cpu |  | 未声明 | disabled @ /audiopwmout-diff |  |
| /audpwm@fe470000 | rockchip,rk3568-audio-pwm, rockchip,audio-pwm-v1 | disabled | disabled @ /audpwm@fe470000 |  |
| /backlight-dsi0 | pwm-backlight | 未声明 | okay | platform:backlight-dsi0 -> pwm-backlight |
| /bus-npu | rockchip,rk3568-bus | okay | okay | platform:bus-npu -> rockchip,bus |
| /bus-npu-opp-table | operating-points-v2 | 未声明 | okay |  |
| /bus-npu-opp-table/opp-1000000000 |  | 未声明 | okay |  |
| /bus-npu-opp-table/opp-700000000 |  | 未声明 | okay |  |
| /bus-npu-opp-table/opp-900000000 |  | 未声明 | okay |  |
| /can@fe570000 | rockchip,rk3568-can-2.0 | disabled | disabled @ /can@fe570000 |  |
| /can@fe580000 | rockchip,rk3568-can-2.0 | disabled | disabled @ /can@fe580000 |  |
| /can@fe590000 | rockchip,rk3568-can-2.0 | disabled | disabled @ /can@fe590000 |  |
| /chosen |  | 未声明 | okay |  |
| /clock-controller@fdd00000 | rockchip,rk3568-pmucru | 未声明 | okay |  |
| /clock-controller@fdd20000 | rockchip,rk3568-cru | 未声明 | okay |  |
| /codec-digital@fe478000 | rockchip,rk3568-codec-digital, rockchip,codec-digital-v1 | disabled | disabled @ /codec-digital@fe478000 |  |
| /cpu0-opp-table | operating-points-v2 | 未声明 | okay |  |
| /cpu0-opp-table/opp-1104000000 |  | 未声明 | okay |  |
| /cpu0-opp-table/opp-1416000000 |  | 未声明 | okay |  |
| /cpu0-opp-table/opp-1608000000 |  | 未声明 | okay |  |
| /cpu0-opp-table/opp-1800000000 |  | 未声明 | okay |  |
| /cpu0-opp-table/opp-1992000000 |  | 未声明 | okay |  |
| /cpu0-opp-table/opp-408000000 |  | 未声明 | okay |  |
| /cpu0-opp-table/opp-600000000 |  | 未声明 | okay |  |
| /cpu0-opp-table/opp-816000000 |  | 未声明 | okay |  |
| /cpu0-opp-table/opp-j-1008000000 |  | 未声明 | okay |  |
| /cpu0-opp-table/opp-j-1416000000 |  | 未声明 | okay |  |
| /cpu0-opp-table/opp-m-1608000000 |  | 未声明 | okay |  |
| /cpuinfo | rockchip,cpuinfo | 未声明 | okay | platform:cpuinfo -> rockchip-cpuinfo |
| /cpus |  | 未声明 | okay |  |
| /cpus/cpu@0 | arm,cortex-a55 | 未声明 | okay | cpu:cpu0 (no driver link) |
| /cpus/cpu@100 | arm,cortex-a55 | 未声明 | okay | cpu:cpu1 (no driver link) |
| /cpus/cpu@200 | arm,cortex-a55 | 未声明 | okay | cpu:cpu2 (no driver link) |
| /cpus/cpu@300 | arm,cortex-a55 | 未声明 | okay | cpu:cpu3 (no driver link) |
| /cpus/idle-states |  | 未声明 | okay |  |
| /cpus/idle-states/cpu-sleep | arm,idle-state | 未声明 | okay |  |
| /crypto@fe380000 | rockchip,rk3568-crypto | disabled | disabled @ /crypto@fe380000 |  |
| /csi2-dphy-hw@fe870000 | rockchip,rk3568-csi2-dphy-hw | okay | okay | platform:fe870000.csi2-dphy-hw -> rockchip-csi2-dphy-hw |
| /csi2-dphy0 | rockchip,rk3568-csi2-dphy | okay | okay | platform:csi2-dphy0 -> rockchip-csi2-dphy |
| /csi2-dphy0/ports |  | 未声明 | okay |  |
| /csi2-dphy0/ports/port@0 |  | 未声明 | okay |  |
| /csi2-dphy0/ports/port@0/endpoint@1 |  | 未声明 | okay |  |
| /csi2-dphy0/ports/port@0/endpoint@2 |  | 未声明 | okay |  |
| /csi2-dphy0/ports/port@1 |  | 未声明 | okay |  |
| /csi2-dphy0/ports/port@1/endpoint@0 |  | 未声明 | okay |  |
| /csi2-dphy1 | rockchip,rk3568-csi2-dphy | disabled | disabled @ /csi2-dphy1 |  |
| /csi2-dphy2 | rockchip,rk3568-csi2-dphy | disabled | disabled @ /csi2-dphy2 |  |
| /cspmu@fd90c000 | rockchip,cspmu | 未声明 | okay | platform:fd90c000.cspmu (no driver link) |
| /dc-12v | regulator-fixed | 未声明 | okay | platform:dc-12v -> reg-fixed-voltage |
| /ddr3-params |  | 未声明 | okay |  |
| /ddr4-params |  | 未声明 | okay |  |
| /debug@fd904000 | rockchip,debug | 未声明 | okay | platform:fd904000.debug (no driver link) |
| /dfi@fe230000 | rockchip,rk3568-dfi | okay | okay | platform:fe230000.dfi -> rockchip-dfi |
| /display-subsystem | rockchip,display-subsystem | 未声明 | okay | platform:display-subsystem -> rockchip-drm |
| /display-subsystem/route |  | 未声明 | okay |  |
| /display-subsystem/route/route-dsi0 |  | okay | okay |  |
| /display-subsystem/route/route-dsi1 |  | disabled | disabled @ /display-subsystem/route/route-dsi1 |  |
| /display-subsystem/route/route-edp |  | disabled | disabled @ /display-subsystem/route/route-edp |  |
| /display-subsystem/route/route-hdmi |  | okay | okay |  |
| /display-subsystem/route/route-lvds |  | disabled | disabled @ /display-subsystem/route/route-lvds |  |
| /display-subsystem/route/route-lvds1 |  | disabled | disabled @ /display-subsystem/route/route-lvds1 |  |
| /display-subsystem/route/route-rgb |  | disabled | disabled @ /display-subsystem/route/route-rgb |  |
| /dmac@fe530000 | arm,pl330, arm,primecell | 未声明 | okay | amba:fe530000.dmac -> dma-pl330 |
| /dmac@fe550000 | arm,pl330, arm,primecell | 未声明 | okay | amba:fe550000.dmac -> dma-pl330 |
| /dmc | rockchip,rk3568-dmc | okay | okay | platform:dmc -> rockchip-dmc |
| /dmc-fsp | rockchip,rk3568-dmc-fsp | okay | okay | platform:dmc-fsp (no driver link) |
| /dmc-opp-table | operating-points-v2 | 未声明 | okay |  |
| /dmc-opp-table/opp-1560000000 |  | 未声明 | okay |  |
| /dmc-opp-table/opp-j-m-1560000000 |  | 未声明 | okay |  |
| /dsi@fe060000 | rockchip,rk3568-mipi-dsi | okay | okay | platform:fe060000.dsi -> dw-mipi-dsi-rockchip |
| /dsi@fe060000/panel@0 | simple-panel-dsi | okay | okay | mipi-dsi:fe060000.dsi.0 -> panel-simple-dsi |
| /dsi@fe060000/panel@0/display-timings |  | 未声明 | okay |  |
| /dsi@fe060000/panel@0/display-timings/timing0 |  | 未声明 | okay |  |
| /dsi@fe060000/panel@0/ports |  | 未声明 | okay |  |
| /dsi@fe060000/panel@0/ports/port@0 |  | 未声明 | okay |  |
| /dsi@fe060000/panel@0/ports/port@0/endpoint |  | 未声明 | okay |  |
| /dsi@fe060000/ports |  | 未声明 | okay |  |
| /dsi@fe060000/ports/port@0 |  | 未声明 | okay |  |
| /dsi@fe060000/ports/port@0/endpoint@0 |  | disabled | disabled @ /dsi@fe060000/ports/port@0/endpoint@0 |  |
| /dsi@fe060000/ports/port@0/endpoint@1 |  | okay | okay |  |
| /dsi@fe060000/ports/port@1 |  | 未声明 | okay |  |
| /dsi@fe060000/ports/port@1/endpoint |  | 未声明 | okay |  |
| /dsi@fe070000 | rockchip,rk3568-mipi-dsi | disabled | disabled @ /dsi@fe070000 |  |
| /dsi@fe070000/ports |  | 未声明 | disabled @ /dsi@fe070000 |  |
| /dsi@fe070000/ports/port@0 |  | 未声明 | disabled @ /dsi@fe070000 |  |
| /dsi@fe070000/ports/port@0/endpoint@0 |  | disabled | disabled @ /dsi@fe070000 |  |
| /dsi@fe070000/ports/port@0/endpoint@1 |  | disabled | disabled @ /dsi@fe070000 |  |
| /dummy-codec | rockchip,dummy-codec | disabled | disabled @ /dummy-codec |  |
| /dwmmc@fe000000 | rockchip,rk3568-dw-mshc, rockchip,rk3288-dw-mshc | okay | okay | platform:fe000000.dwmmc -> dwmmc_rockchip |
| /dwmmc@fe2b0000 | rockchip,rk3568-dw-mshc, rockchip,rk3288-dw-mshc | okay | okay | platform:fe2b0000.dwmmc -> dwmmc_rockchip |
| /dwmmc@fe2c0000 | rockchip,rk3568-dw-mshc, rockchip,rk3288-dw-mshc | disabled | disabled @ /dwmmc@fe2c0000 |  |
| /ebc@fdec0000 | rockchip,rk3568-ebc-tcon | disabled | disabled @ /ebc@fdec0000 |  |
| /edac | rockchip,rk3568-edac | disabled | disabled @ /edac |  |
| /edp@fe0c0000 | rockchip,rk3568-edp | disabled | disabled @ /edp@fe0c0000 |  |
| /edp@fe0c0000/ports |  | 未声明 | disabled @ /edp@fe0c0000 |  |
| /edp@fe0c0000/ports/port@0 |  | 未声明 | disabled @ /edp@fe0c0000 |  |
| /edp@fe0c0000/ports/port@0/endpoint@0 |  | disabled | disabled @ /edp@fe0c0000 |  |
| /edp@fe0c0000/ports/port@0/endpoint@1 |  | disabled | disabled @ /edp@fe0c0000 |  |
| /eink@fdf00000 | rockchip,rk3568-eink-tcon | disabled | disabled @ /eink@fdf00000 |  |
| /ethernet@fe010000 | rockchip,rk3568-gmac, snps,dwmac-4.20a | okay | okay | platform:fe010000.ethernet -> rk_gmac-dwmac |
| /ethernet@fe010000/mdio | snps,dwmac-mdio | 未声明 | okay |  |
| /ethernet@fe010000/mdio/phy@0 | ethernet-phy-ieee802.3-c22 | 未声明 | okay | mdio_bus:stmmac-1:00 -> MAE0621A-Q2C Gigabit Ethernet |
| /ethernet@fe010000/rx-queues-config |  | 未声明 | okay |  |
| /ethernet@fe010000/rx-queues-config/queue0 |  | 未声明 | okay |  |
| /ethernet@fe010000/stmmac-axi-config |  | 未声明 | okay |  |
| /ethernet@fe010000/tx-queues-config |  | 未声明 | okay |  |
| /ethernet@fe010000/tx-queues-config/queue0 |  | 未声明 | okay |  |
| /ethernet@fe2a0000 | rockchip,rk3568-gmac, snps,dwmac-4.20a | okay | okay | platform:fe2a0000.ethernet -> rk_gmac-dwmac |
| /ethernet@fe2a0000/mdio | snps,dwmac-mdio | 未声明 | okay |  |
| /ethernet@fe2a0000/mdio/phy@0 | ethernet-phy-ieee802.3-c22 | 未声明 | okay | mdio_bus:stmmac-0:00 -> MAE0621A-Q2C Gigabit Ethernet |
| /ethernet@fe2a0000/rx-queues-config |  | 未声明 | okay |  |
| /ethernet@fe2a0000/rx-queues-config/queue0 |  | 未声明 | okay |  |
| /ethernet@fe2a0000/stmmac-axi-config |  | 未声明 | okay |  |
| /ethernet@fe2a0000/tx-queues-config |  | 未声明 | okay |  |
| /ethernet@fe2a0000/tx-queues-config/queue0 |  | 未声明 | okay |  |
| /external-camera-25m-clock | fixed-clock | 未声明 | okay |  |
| /external-gmac0-clock | fixed-clock | 未声明 | okay |  |
| /external-gmac1-clock | fixed-clock | 未声明 | okay |  |
| /fiq-debugger | rockchip,fiq-debugger | okay | okay | platform:fiq-debugger -> rk-fiq-debugger |
| /firmware |  | 未声明 | okay |  |
| /firmware/scmi | arm,scmi-smc | 未声明 | okay | platform:firmware:scmi -> arm-scmi |
| /firmware/scmi/protocol@14 |  | 未声明 | okay | scmi_protocol:scmi_dev.1 -> scmi-clocks |
| /firmware/sdei | arm,sdei-1.0 | 未声明 | okay | platform:firmware:sdei (no driver link) |
| /gpio-regulator | regulator-fixed | 未声明 | okay | platform:gpio-regulator -> reg-fixed-voltage |
| /gpu@fde60000 | arm,mali-bifrost | okay | okay | platform:fde60000.gpu -> mali |
| /gpu@fde60000/power-model | simple-power-model | 未声明 | okay |  |
| /hdmi-sound | simple-audio-card | okay | okay | platform:hdmi-sound -> asoc-simple-card |
| /hdmi-sound/simple-audio-card,codec |  | 未声明 | okay |  |
| /hdmi-sound/simple-audio-card,cpu |  | 未声明 | okay |  |
| /hdmi@fe0a0000 | rockchip,rk3568-dw-hdmi | okay | okay | platform:fe0a0000.hdmi -> dwhdmi-rockchip |
| /hdmi@fe0a0000/ports |  | 未声明 | okay |  |
| /hdmi@fe0a0000/ports/port@0 |  | 未声明 | okay |  |
| /hdmi@fe0a0000/ports/port@0/endpoint@0 |  | okay | okay |  |
| /hdmi@fe0a0000/ports/port@0/endpoint@1 |  | disabled | disabled @ /hdmi@fe0a0000/ports/port@0/endpoint@1 |  |
| /i2c@fdd40000 | rockchip,rk3399-i2c | okay | okay | i2c:i2c-0 (no driver link); platform:fdd40000.i2c -> rk3x-i2c |
| /i2c@fdd40000/pmic@20 | rockchip,rk809 | 未声明 | okay | i2c:0-0020 -> rk808 |
| /i2c@fdd40000/pmic@20/codec | rockchip,rk809-codec, rockchip,rk817-codec | okay | okay | platform:rk817-codec -> rk817-codec |
| /i2c@fdd40000/pmic@20/pinctrl_rk8xx |  | 未声明 | okay | gpio:gpiochip5 -> gpio_stub_drv |
| /i2c@fdd40000/pmic@20/pinctrl_rk8xx/rk817_slppin_null |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/pinctrl_rk8xx/rk817_slppin_pwrdn |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/pinctrl_rk8xx/rk817_slppin_rst |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/pinctrl_rk8xx/rk817_slppin_slp |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/pwrkey |  | okay | okay |  |
| /i2c@fdd40000/pmic@20/regulators |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/DCDC_REG1 |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/DCDC_REG1/regulator-state-mem |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/DCDC_REG2 |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/DCDC_REG2/regulator-state-mem |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/DCDC_REG3 |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/DCDC_REG3/regulator-state-mem |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/DCDC_REG4 |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/DCDC_REG4/regulator-state-mem |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/DCDC_REG5 |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/DCDC_REG5/regulator-state-mem |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/LDO_REG1 |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/LDO_REG1/regulator-state-mem |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/LDO_REG2 |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/LDO_REG2/regulator-state-mem |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/LDO_REG3 |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/LDO_REG3/regulator-state-mem |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/LDO_REG4 |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/LDO_REG4/regulator-state-mem |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/LDO_REG5 |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/LDO_REG5/regulator-state-mem |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/LDO_REG6 |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/LDO_REG6/regulator-state-mem |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/LDO_REG7 |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/LDO_REG7/regulator-state-mem |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/LDO_REG8 |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/LDO_REG8/regulator-state-mem |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/LDO_REG9 |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/LDO_REG9/regulator-state-mem |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/SWITCH_REG1 |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/SWITCH_REG1/regulator-state-mem |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/SWITCH_REG2 |  | 未声明 | okay |  |
| /i2c@fdd40000/pmic@20/regulators/SWITCH_REG2/regulator-state-mem |  | 未声明 | okay |  |
| /i2c@fdd40000/tcs4525@1c | tcs,tcs4525 | 未声明 | okay | i2c:0-001c -> fan53555-regulator |
| /i2c@fdd40000/tcs4525@1c/regulator-state-mem |  | 未声明 | okay |  |
| /i2c@fe5a0000 | rockchip,rk3399-i2c | okay | okay | i2c:i2c-1 (no driver link); platform:fe5a0000.i2c -> rk3x-i2c |
| /i2c@fe5a0000/gt9xx@5d | goodix,gt9xx | okay | okay | i2c:1-005d -> Goodix-TS |
| /i2c@fe5b0000 | rockchip,rk3399-i2c | okay | okay | i2c:i2c-2 (no driver link); platform:fe5b0000.i2c -> rk3x-i2c |
| /i2c@fe5c0000 | rockchip,rk3399-i2c | okay | okay | i2c:i2c-3 (no driver link); platform:fe5c0000.i2c -> rk3x-i2c |
| /i2c@fe5d0000 | rockchip,rk3399-i2c | okay | okay | i2c:i2c-4 (no driver link); platform:fe5d0000.i2c -> rk3x-i2c |
| /i2c@fe5d0000/gc5035@37 | galaxycore,gc5035 | disabled | disabled @ /i2c@fe5d0000/gc5035@37 |  |
| /i2c@fe5d0000/gc5035@37/port |  | 未声明 | disabled @ /i2c@fe5d0000/gc5035@37 |  |
| /i2c@fe5d0000/gc5035@37/port/endpoint |  | 未声明 | disabled @ /i2c@fe5d0000/gc5035@37 |  |
| /i2c@fe5d0000/ov5647@36 | ovti,ov5647 | okay | okay | i2c:4-0036 (no driver link) |
| /i2c@fe5d0000/ov5647@36/port |  | 未声明 | okay |  |
| /i2c@fe5d0000/ov5647@36/port/endpoint |  | 未声明 | okay |  |
| /i2c@fe5e0000 | rockchip,rk3399-i2c | okay | okay | i2c:i2c-5 (no driver link); platform:fe5e0000.i2c -> rk3x-i2c |
| /i2c@fe5e0000/hym8563@51 | haoyu,hym8563 | 未声明 | okay | i2c:5-0051 -> rtc-hym8563 |
| /i2s1-mclkin-rx | fixed-clock | 未声明 | okay |  |
| /i2s1-mclkin-tx | fixed-clock | 未声明 | okay |  |
| /i2s2-mclkin | fixed-clock | 未声明 | okay |  |
| /i2s3-mclkin | fixed-clock | 未声明 | okay |  |
| /i2s@fe400000 | rockchip,rk3568-i2s-tdm | okay | okay | platform:fe400000.i2s -> rockchip-i2s-tdm |
| /i2s@fe410000 | rockchip,rk3568-i2s-tdm | okay | okay | platform:fe410000.i2s -> rockchip-i2s-tdm |
| /i2s@fe420000 | rockchip,rk3568-i2s-tdm | disabled | disabled @ /i2s@fe420000 |  |
| /i2s@fe430000 | rockchip,rk3568-i2s-tdm | disabled | disabled @ /i2s@fe430000 |  |
| /iep@fdef0000 | rockchip,iep-v2 | okay | okay | platform:fdef0000.iep -> mpp-iep2 |
| /interrupt-controller@fd400000 | arm,gic-v3 | 未声明 | okay |  |
| /interrupt-controller@fd400000/interrupt-controller@fd440000 | arm,gic-v3-its | 未声明 | okay |  |
| /iommu@fde4b000 | rockchip,iommu-v2 | okay | okay | platform:fde4b000.iommu -> rk_iommu |
| /iommu@fdea0800 | rockchip,iommu-v2 | okay | okay | platform:fdea0800.iommu -> rk_iommu |
| /iommu@fded0480 | rockchip,iommu-v2 | okay | okay | platform:fded0480.iommu -> rk_iommu |
| /iommu@fdee0800 | rockchip,iommu-v2 | okay | okay | platform:fdee0800.iommu -> rk_iommu |
| /iommu@fdef0800 | rockchip,iommu-v2 | okay | okay | platform:fdef0800.iommu -> rk_iommu |
| /iommu@fdf40f00 | rockchip,iommu-v2 | okay | okay | platform:fdf40f00.iommu -> rk_iommu |
| /iommu@fdf80800 | rockchip,iommu-v2 | okay | okay | platform:fdf80800.iommu -> rk_iommu |
| /iommu@fdfe0800 | rockchip,iommu-v2 | disabled | disabled @ /iommu@fdfe0800 |  |
| /iommu@fdff1a00 | rockchip,iommu-v2 | okay | okay | platform:fdff1a00.iommu -> rk_iommu |
| /iommu@fe043e00 | rockchip,iommu-v2 | okay | okay | platform:fe043e00.iommu -> rk_iommu |
| /jpegd@fded0000 | rockchip,rkv-jpeg-decoder-v1 | okay | okay | platform:fded0000.jpegd -> mpp_jpgdec |
| /leds | gpio-leds | 未声明 | okay | platform:leds -> leds-gpio |
| /leds/fan |  | 未声明 | okay |  |
| /leds/gpio1a4 |  | 未声明 | okay |  |
| /leds/gpio1b0 |  | 未声明 | okay |  |
| /leds/gpio1b1 |  | 未声明 | okay |  |
| /leds/gpio1b2 |  | 未声明 | okay |  |
| /leds/gpio1d0 |  | 未声明 | okay |  |
| /leds/gpio1d4 |  | 未声明 | okay |  |
| /leds/gpio3b5 |  | 未声明 | okay |  |
| /leds/gpio3b6 |  | 未声明 | okay |  |
| /leds/gpio4c4 |  | 未声明 | okay |  |
| /leds/gpio4c6 |  | 未声明 | okay |  |
| /leds/work-led |  | 未声明 | okay |  |
| /lpddr3-params |  | 未声明 | okay |  |
| /lpddr4-params |  | 未声明 | okay |  |
| /lpddr4x-params |  | 未声明 | okay |  |
| /mailbox@fe780000 | rockchip,rk3568-mailbox, rockchip,rk3368-mailbox | disabled | disabled @ /mailbox@fe780000 |  |
| /memory |  | 未声明 | okay |  |
| /minipcie-regulator | regulator-fixed | 未声明 | okay | platform:minipcie-regulator -> reg-fixed-voltage |
| /mipi-csi2 | rockchip,rk3568-mipi-csi2 | disabled | disabled @ /mipi-csi2 |  |
| /mipi-csi2-hw@fdfb0000 | rockchip,rk3568-mipi-csi2-hw | okay | okay | platform:fdfb0000.mipi-csi2-hw -> rockchip-mipi-csi2-hw |
| /mpll | fixed-clock | 未声明 | okay |  |
| /mpp-srv | rockchip,mpp-service | okay | okay | platform:mpp-srv -> mpp_service |
| /nandc@fe330000 | rockchip,rk-nandc-v9 | okay | okay | platform:fe330000.nandc (no driver link) |
| /nandc@fe330000/nand@0 |  | 未声明 | okay |  |
| /nocp-cpu@fe102000 | rockchip,rk3568-nocp | 未声明 | okay | platform:fe102000.nocp-cpu -> rockchip-nocp |
| /nocp-gpu-vpu-rga-venc@fe102400 | rockchip,rk3568-nocp | 未声明 | okay | platform:fe102400.nocp-gpu-vpu-rga-venc -> rockchip-nocp |
| /nocp-vdec@fe102800 | rockchip,rk3568-nocp | 未声明 | okay | platform:fe102800.nocp-vdec -> rockchip-nocp |
| /nocp-vi-usb-peri-pipe@fe102c00 | rockchip,rk3568-nocp | 未声明 | okay | platform:fe102c00.nocp-vi-usb-peri-pipe -> rockchip-nocp |
| /nocp-vo@fe103000 | rockchip,rk3568-nocp | 未声明 | okay | platform:fe103000.nocp-vo -> rockchip-nocp |
| /npu-opp-table | operating-points-v2 | 未声明 | okay |  |
| /npu-opp-table/opp-1000000000 |  | disabled | disabled @ /npu-opp-table/opp-1000000000 |  |
| /npu-opp-table/opp-200000000 |  | 未声明 | okay |  |
| /npu-opp-table/opp-300000000 |  | 未声明 | okay |  |
| /npu-opp-table/opp-400000000 |  | 未声明 | okay |  |
| /npu-opp-table/opp-600000000 |  | 未声明 | okay |  |
| /npu-opp-table/opp-700000000 |  | 未声明 | okay |  |
| /npu-opp-table/opp-800000000 |  | 未声明 | okay |  |
| /npu-opp-table/opp-900000000 |  | 未声明 | okay |  |
| /npu-opp-table/opp-j-600000000 |  | 未声明 | okay |  |
| /npu-opp-table/opp-m-900000000 |  | 未声明 | okay |  |
| /npu@fde40000 | rockchip,rk3568-rknpu, rockchip,rknpu | okay | okay | platform:fde40000.npu -> RKNPU |
| /opp-table2 | operating-points-v2 | 未声明 | okay |  |
| /opp-table2/opp-200000000 |  | 未声明 | okay |  |
| /opp-table2/opp-300000000 |  | 未声明 | okay |  |
| /opp-table2/opp-400000000 |  | 未声明 | okay |  |
| /opp-table2/opp-600000000 |  | 未声明 | okay |  |
| /opp-table2/opp-700000000 |  | 未声明 | okay |  |
| /opp-table2/opp-800000000 |  | 未声明 | okay |  |
| /opp-table2/opp-j-600000000 |  | 未声明 | okay |  |
| /opp-table2/opp-m-800000000 |  | 未声明 | okay |  |
| /otp@fe38c000 | rockchip,rk3568-otp | 未声明 | okay | nvmem:rockchip-otp0 (no driver link); platform:fe38c000.otp -> rockchip-otp |
| /otp@fe38c000/core-pvtm@2a |  | 未声明 | okay |  |
| /otp@fe38c000/cpu-code@2 |  | 未声明 | okay |  |
| /otp@fe38c000/cpu-leakage@1a |  | 未声明 | okay |  |
| /otp@fe38c000/cpu-opp-info@36 |  | 未声明 | okay |  |
| /otp@fe38c000/cpu-tsadc-trim-h@2f |  | 未声明 | okay |  |
| /otp@fe38c000/cpu-tsadc-trim-l@2e |  | 未声明 | okay |  |
| /otp@fe38c000/cpu-version@8 |  | 未声明 | okay |  |
| /otp@fe38c000/dmc-opp-info@48 |  | 未声明 | okay |  |
| /otp@fe38c000/gpu-leakage@1d |  | 未声明 | okay |  |
| /otp@fe38c000/gpu-opp-info@3c |  | 未声明 | okay |  |
| /otp@fe38c000/id@a |  | 未声明 | okay |  |
| /otp@fe38c000/log-leakage@1b |  | 未声明 | okay |  |
| /otp@fe38c000/mbist-vmin@9 |  | 未声明 | okay |  |
| /otp@fe38c000/npu-leakage@1c |  | 未声明 | okay |  |
| /otp@fe38c000/npu-opp-info@42 |  | 未声明 | okay |  |
| /otp@fe38c000/npu-tsadc-trim-h@31 |  | 未声明 | okay |  |
| /otp@fe38c000/npu-tsadc-trim-l@30 |  | 未声明 | okay |  |
| /otp@fe38c000/remark-spec-serial-number@56 |  | 未声明 | okay |  |
| /otp@fe38c000/specification-serial-number@7 |  | 未声明 | okay |  |
| /otp@fe38c000/tsadc-trim-base-frac@31 |  | 未声明 | okay |  |
| /otp@fe38c000/tsadc-trim-base@32 |  | 未声明 | okay |  |
| /pcie3-regulator | regulator-fixed | 未声明 | okay | platform:pcie3-regulator -> reg-fixed-voltage |
| /pcie30-avdd0v9 | regulator-fixed | 未声明 | okay | platform:pcie30-avdd0v9 -> reg-fixed-voltage |
| /pcie30-avdd1v8 | regulator-fixed | 未声明 | okay | platform:pcie30-avdd1v8 -> reg-fixed-voltage |
| /pcie@fe260000 | rockchip,rk3568-pcie, snps,dw-pcie | okay | okay | platform:3c0000000.pcie (no driver link) |
| /pcie@fe260000/legacy-interrupt-controller |  | 未声明 | okay |  |
| /pcie@fe270000 | rockchip,rk3568-pcie, snps,dw-pcie | disabled | disabled @ /pcie@fe270000 |  |
| /pcie@fe270000/legacy-interrupt-controller |  | 未声明 | disabled @ /pcie@fe270000 |  |
| /pcie@fe280000 | rockchip,rk3568-pcie, snps,dw-pcie | okay | okay | platform:3c0800000.pcie (no driver link) |
| /pcie@fe280000/legacy-interrupt-controller |  | 未声明 | okay |  |
| /pdm-mic-array | simple-audio-card | disabled | disabled @ /pdm-mic-array |  |
| /pdm-mic-array/simple-audio-card,codec |  | 未声明 | disabled @ /pdm-mic-array |  |
| /pdm-mic-array/simple-audio-card,cpu |  | 未声明 | disabled @ /pdm-mic-array |  |
| /pdm@fe440000 | rockchip,rk3568-pdm, rockchip,pdm | disabled | disabled @ /pdm@fe440000 |  |
| /phy@fe820000 | rockchip,rk3568-naneng-combphy | okay | okay | platform:fe820000.phy -> naneng-combphy |
| /phy@fe830000 | rockchip,rk3568-naneng-combphy | okay | okay | platform:fe830000.phy -> naneng-combphy |
| /phy@fe840000 | rockchip,rk3568-naneng-combphy | okay | okay | platform:fe840000.phy -> naneng-combphy |
| /phy@fe850000 | rockchip,rk3568-dsi-dphy, rockchip,rk3568-video-phy | okay | okay | platform:fe850000.phy -> inno-dsidphy |
| /phy@fe860000 | rockchip,rk3568-dsi-dphy, rockchip,rk3568-video-phy | disabled | disabled @ /phy@fe860000 |  |
| /phy@fe8c0000 | rockchip,rk3568-pcie3-phy | okay | okay | platform:fe8c0000.phy -> rockchip-snps-pcie3-phy |
| /pinctrl | rockchip,rk3568-pinctrl | 未声明 | okay | platform:pinctrl -> rockchip-pinctrl |
| /pinctrl/acodec |  | 未声明 | okay |  |
| /pinctrl/acodec/acodec-pins |  | 未声明 | okay |  |
| /pinctrl/audiopwm |  | 未声明 | okay |  |
| /pinctrl/bt1120 |  | 未声明 | okay |  |
| /pinctrl/bt656 |  | 未声明 | okay |  |
| /pinctrl/cam |  | 未声明 | okay |  |
| /pinctrl/cam/camera-pwr |  | 未声明 | okay |  |
| /pinctrl/can0 |  | 未声明 | okay |  |
| /pinctrl/can0/can0m1-pins |  | 未声明 | okay |  |
| /pinctrl/can1 |  | 未声明 | okay |  |
| /pinctrl/can1/can1m1-pins |  | 未声明 | okay |  |
| /pinctrl/can2 |  | 未声明 | okay |  |
| /pinctrl/can2/can2m1-pins |  | 未声明 | okay |  |
| /pinctrl/cif |  | 未声明 | okay |  |
| /pinctrl/cif/cif-clk |  | 未声明 | okay |  |
| /pinctrl/clk32k |  | 未声明 | okay |  |
| /pinctrl/clk32k/clk32k-out0 |  | 未声明 | okay |  |
| /pinctrl/cpu |  | 未声明 | okay |  |
| /pinctrl/ebc |  | 未声明 | okay |  |
| /pinctrl/ebc/ebc-pins |  | 未声明 | okay |  |
| /pinctrl/edpdp |  | 未声明 | okay |  |
| /pinctrl/emmc |  | 未声明 | okay |  |
| /pinctrl/eth0 |  | 未声明 | okay |  |
| /pinctrl/eth1 |  | 未声明 | okay |  |
| /pinctrl/flash |  | 未声明 | okay |  |
| /pinctrl/fspi |  | 未声明 | okay |  |
| /pinctrl/gmac-txc-level2 |  | 未声明 | okay |  |
| /pinctrl/gmac-txd-level3 |  | 未声明 | okay |  |
| /pinctrl/gmac0 |  | 未声明 | okay |  |
| /pinctrl/gmac0/gmac0-miim |  | 未声明 | okay |  |
| /pinctrl/gmac0/gmac0-rgmii-bus |  | 未声明 | okay |  |
| /pinctrl/gmac0/gmac0-rgmii-clk |  | 未声明 | okay |  |
| /pinctrl/gmac0/gmac0-rx-bus2 |  | 未声明 | okay |  |
| /pinctrl/gmac0/gmac0-tx-bus2 |  | 未声明 | okay |  |
| /pinctrl/gmac1 |  | 未声明 | okay |  |
| /pinctrl/gmac1/gmac1m1-miim |  | 未声明 | okay |  |
| /pinctrl/gmac1/gmac1m1-rgmii-bus |  | 未声明 | okay |  |
| /pinctrl/gmac1/gmac1m1-rgmii-clk |  | 未声明 | okay |  |
| /pinctrl/gmac1/gmac1m1-rx-bus2 |  | 未声明 | okay |  |
| /pinctrl/gmac1/gmac1m1-tx-bus2 |  | 未声明 | okay |  |
| /pinctrl/gpio-func |  | 未声明 | okay |  |
| /pinctrl/gpio-func/tsadc-gpio-func |  | 未声明 | okay |  |
| /pinctrl/gpio0@fdd60000 | rockchip,gpio-bank | 未声明 | okay | gpio:gpiochip0 (no driver link); platform:fdd60000.gpio0 -> rockchip-gpio |
| /pinctrl/gpio1@fe740000 | rockchip,gpio-bank | 未声明 | okay | gpio:gpiochip1 (no driver link); platform:fe740000.gpio1 -> rockchip-gpio |
| /pinctrl/gpio2@fe750000 | rockchip,gpio-bank | 未声明 | okay | gpio:gpiochip2 (no driver link); platform:fe750000.gpio2 -> rockchip-gpio |
| /pinctrl/gpio3@fe760000 | rockchip,gpio-bank | 未声明 | okay | gpio:gpiochip3 (no driver link); platform:fe760000.gpio3 -> rockchip-gpio |
| /pinctrl/gpio4@fe770000 | rockchip,gpio-bank | 未声明 | okay | gpio:gpiochip4 (no driver link); platform:fe770000.gpio4 -> rockchip-gpio |
| /pinctrl/gpu |  | 未声明 | okay |  |
| /pinctrl/hdmitx |  | 未声明 | okay |  |
| /pinctrl/hdmitx/hdmitx-scl |  | 未声明 | okay |  |
| /pinctrl/hdmitx/hdmitx-sda |  | 未声明 | okay |  |
| /pinctrl/hdmitx/hdmitxm0-cec |  | 未声明 | okay |  |
| /pinctrl/headphone |  | 未声明 | okay |  |
| /pinctrl/headphone/hp-det |  | 未声明 | okay |  |
| /pinctrl/i2c0 |  | 未声明 | okay |  |
| /pinctrl/i2c0/i2c0-xfer |  | 未声明 | okay |  |
| /pinctrl/i2c1 |  | 未声明 | okay |  |
| /pinctrl/i2c1/i2c1-xfer |  | 未声明 | okay |  |
| /pinctrl/i2c2 |  | 未声明 | okay |  |
| /pinctrl/i2c2/i2c2m1-xfer |  | 未声明 | okay |  |
| /pinctrl/i2c3 |  | 未声明 | okay |  |
| /pinctrl/i2c3/i2c3m0-xfer |  | 未声明 | okay |  |
| /pinctrl/i2c4 |  | 未声明 | okay |  |
| /pinctrl/i2c4/i2c4m0-xfer |  | 未声明 | okay |  |
| /pinctrl/i2c5 |  | 未声明 | okay |  |
| /pinctrl/i2c5/i2c5m0-xfer |  | 未声明 | okay |  |
| /pinctrl/i2s1 |  | 未声明 | okay |  |
| /pinctrl/i2s1/i2s1m0-lrcktx |  | 未声明 | okay |  |
| /pinctrl/i2s1/i2s1m0-mclk |  | 未声明 | okay |  |
| /pinctrl/i2s1/i2s1m0-sclktx |  | 未声明 | okay |  |
| /pinctrl/i2s1/i2s1m0-sdi0 |  | 未声明 | okay |  |
| /pinctrl/i2s1/i2s1m0-sdo0 |  | 未声明 | okay |  |
| /pinctrl/i2s2 |  | 未声明 | okay |  |
| /pinctrl/i2s2/i2s2m0-lrcktx |  | 未声明 | okay |  |
| /pinctrl/i2s2/i2s2m0-sclktx |  | 未声明 | okay |  |
| /pinctrl/i2s2/i2s2m0-sdi |  | 未声明 | okay |  |
| /pinctrl/i2s2/i2s2m0-sdo |  | 未声明 | okay |  |
| /pinctrl/i2s3 |  | 未声明 | okay |  |
| /pinctrl/i2s3/i2s3m0-lrck |  | 未声明 | okay |  |
| /pinctrl/i2s3/i2s3m0-sclk |  | 未声明 | okay |  |
| /pinctrl/i2s3/i2s3m0-sdi |  | 未声明 | okay |  |
| /pinctrl/i2s3/i2s3m0-sdo |  | 未声明 | okay |  |
| /pinctrl/isp |  | 未声明 | okay |  |
| /pinctrl/jtag |  | 未声明 | okay |  |
| /pinctrl/lcdc |  | 未声明 | okay |  |
| /pinctrl/lcdc/lcdc-ctl |  | 未声明 | okay |  |
| /pinctrl/mcu |  | 未声明 | okay |  |
| /pinctrl/minipcie |  | 未声明 | okay |  |
| /pinctrl/minipcie/minipcie-power-en |  | 未声明 | okay |  |
| /pinctrl/npu |  | 未声明 | okay |  |
| /pinctrl/pcfg-output-low |  | 未声明 | okay |  |
| /pinctrl/pcfg-pull-down |  | 未声明 | okay |  |
| /pinctrl/pcfg-pull-none |  | 未声明 | okay |  |
| /pinctrl/pcfg-pull-none-drv-level-1 |  | 未声明 | okay |  |
| /pinctrl/pcfg-pull-none-drv-level-2 |  | 未声明 | okay |  |
| /pinctrl/pcfg-pull-none-drv-level-3 |  | 未声明 | okay |  |
| /pinctrl/pcfg-pull-none-smt |  | 未声明 | okay |  |
| /pinctrl/pcfg-pull-up |  | 未声明 | okay |  |
| /pinctrl/pcfg-pull-up-drv-level-1 |  | 未声明 | okay |  |
| /pinctrl/pcfg-pull-up-drv-level-2 |  | 未声明 | okay |  |
| /pinctrl/pcie20 |  | 未声明 | okay |  |
| /pinctrl/pcie3 |  | 未声明 | okay |  |
| /pinctrl/pcie3/pcie3-power-en |  | 未声明 | okay |  |
| /pinctrl/pcie30x1 |  | 未声明 | okay |  |
| /pinctrl/pcie30x2 |  | 未声明 | okay |  |
| /pinctrl/pdm |  | 未声明 | okay |  |
| /pinctrl/pdm/pdmm0-clk |  | 未声明 | okay |  |
| /pinctrl/pdm/pdmm0-clk1 |  | 未声明 | okay |  |
| /pinctrl/pdm/pdmm0-sdi0 |  | 未声明 | okay |  |
| /pinctrl/pdm/pdmm0-sdi1 |  | 未声明 | okay |  |
| /pinctrl/pdm/pdmm0-sdi2 |  | 未声明 | okay |  |
| /pinctrl/pdm/pdmm0-sdi3 |  | 未声明 | okay |  |
| /pinctrl/pmic |  | 未声明 | okay |  |
| /pinctrl/pmic/pmic_int |  | 未声明 | okay |  |
| /pinctrl/pmic/soc_slppin_gpio |  | 未声明 | okay |  |
| /pinctrl/pmic/soc_slppin_rst |  | 未声明 | okay |  |
| /pinctrl/pmic/soc_slppin_slp |  | 未声明 | okay |  |
| /pinctrl/pmu |  | 未声明 | okay |  |
| /pinctrl/pwm0 |  | 未声明 | okay |  |
| /pinctrl/pwm0/pwm0m0-pins |  | 未声明 | okay |  |
| /pinctrl/pwm1 |  | 未声明 | okay |  |
| /pinctrl/pwm1/pwm1m0-pins |  | 未声明 | okay |  |
| /pinctrl/pwm10 |  | 未声明 | okay |  |
| /pinctrl/pwm10/pwm10m0-pins |  | 未声明 | okay |  |
| /pinctrl/pwm11 |  | 未声明 | okay |  |
| /pinctrl/pwm11/pwm11m0-pins |  | 未声明 | okay |  |
| /pinctrl/pwm12 |  | 未声明 | okay |  |
| /pinctrl/pwm12/pwm12m0-pins |  | 未声明 | okay |  |
| /pinctrl/pwm13 |  | 未声明 | okay |  |
| /pinctrl/pwm13/pwm13m0-pins |  | 未声明 | okay |  |
| /pinctrl/pwm14 |  | 未声明 | okay |  |
| /pinctrl/pwm14/pwm14m0-pins |  | 未声明 | okay |  |
| /pinctrl/pwm15 |  | 未声明 | okay |  |
| /pinctrl/pwm15/pwm15m0-pins |  | 未声明 | okay |  |
| /pinctrl/pwm2 |  | 未声明 | okay |  |
| /pinctrl/pwm2/pwm2m0-pins |  | 未声明 | okay |  |
| /pinctrl/pwm3 |  | 未声明 | okay |  |
| /pinctrl/pwm3/pwm3-pins |  | 未声明 | okay |  |
| /pinctrl/pwm4 |  | 未声明 | okay |  |
| /pinctrl/pwm4/pwm4-pins |  | 未声明 | okay |  |
| /pinctrl/pwm5 |  | 未声明 | okay |  |
| /pinctrl/pwm5/pwm5-pins |  | 未声明 | okay |  |
| /pinctrl/pwm6 |  | 未声明 | okay |  |
| /pinctrl/pwm6/pwm6-pins |  | 未声明 | okay |  |
| /pinctrl/pwm7 |  | 未声明 | okay |  |
| /pinctrl/pwm7/pwm7-pins |  | 未声明 | okay |  |
| /pinctrl/pwm8 |  | 未声明 | okay |  |
| /pinctrl/pwm8/pwm8m0-pins |  | 未声明 | okay |  |
| /pinctrl/pwm9 |  | 未声明 | okay |  |
| /pinctrl/pwm9/pwm9m0-pins |  | 未声明 | okay |  |
| /pinctrl/refclk |  | 未声明 | okay |  |
| /pinctrl/sata |  | 未声明 | okay |  |
| /pinctrl/sata0 |  | 未声明 | okay |  |
| /pinctrl/sata1 |  | 未声明 | okay |  |
| /pinctrl/sata2 |  | 未声明 | okay |  |
| /pinctrl/scr |  | 未声明 | okay |  |
| /pinctrl/scr/scr-pins |  | 未声明 | okay |  |
| /pinctrl/sdio-pwrseq |  | 未声明 | okay |  |
| /pinctrl/sdio-pwrseq/wifi-enable-h |  | 未声明 | okay |  |
| /pinctrl/sdmmc0 |  | 未声明 | okay |  |
| /pinctrl/sdmmc0/sdmmc0-bus4 |  | 未声明 | okay |  |
| /pinctrl/sdmmc0/sdmmc0-clk |  | 未声明 | okay |  |
| /pinctrl/sdmmc0/sdmmc0-cmd |  | 未声明 | okay |  |
| /pinctrl/sdmmc0/sdmmc0-det |  | 未声明 | okay |  |
| /pinctrl/sdmmc1 |  | 未声明 | okay |  |
| /pinctrl/sdmmc2 |  | 未声明 | okay |  |
| /pinctrl/sdmmc2/sdmmc2m0-bus4 |  | 未声明 | okay |  |
| /pinctrl/sdmmc2/sdmmc2m0-clk |  | 未声明 | okay |  |
| /pinctrl/sdmmc2/sdmmc2m0-cmd |  | 未声明 | okay |  |
| /pinctrl/spdif |  | 未声明 | okay |  |
| /pinctrl/spdif/spdifm0-tx |  | 未声明 | okay |  |
| /pinctrl/spi0 |  | 未声明 | okay |  |
| /pinctrl/spi0/spi0m0-cs0 |  | 未声明 | okay |  |
| /pinctrl/spi0/spi0m0-cs1 |  | 未声明 | okay |  |
| /pinctrl/spi0/spi0m0-pins |  | 未声明 | okay |  |
| /pinctrl/spi0-hs |  | 未声明 | okay |  |
| /pinctrl/spi0-hs/spi0m0-pins |  | 未声明 | okay |  |
| /pinctrl/spi1 |  | 未声明 | okay |  |
| /pinctrl/spi1/spi1m0-cs0 |  | 未声明 | okay |  |
| /pinctrl/spi1/spi1m0-cs1 |  | 未声明 | okay |  |
| /pinctrl/spi1/spi1m0-pins |  | 未声明 | okay |  |
| /pinctrl/spi1-hs |  | 未声明 | okay |  |
| /pinctrl/spi1-hs/spi1m0-pins |  | 未声明 | okay |  |
| /pinctrl/spi2 |  | 未声明 | okay |  |
| /pinctrl/spi2/spi2m0-cs0 |  | 未声明 | okay |  |
| /pinctrl/spi2/spi2m0-cs1 |  | 未声明 | okay |  |
| /pinctrl/spi2/spi2m0-pins |  | 未声明 | okay |  |
| /pinctrl/spi2-hs |  | 未声明 | okay |  |
| /pinctrl/spi2-hs/spi2m0-pins |  | 未声明 | okay |  |
| /pinctrl/spi3 |  | 未声明 | okay |  |
| /pinctrl/spi3/spi3m1-pins |  | 未声明 | okay |  |
| /pinctrl/spi3-hs |  | 未声明 | okay |  |
| /pinctrl/spi3-hs/spi3m1-pins |  | 未声明 | okay |  |
| /pinctrl/touch1 |  | 未声明 | okay |  |
| /pinctrl/touch1/touch-gpio |  | 未声明 | okay |  |
| /pinctrl/tsadc |  | 未声明 | okay |  |
| /pinctrl/tsadc/tsadc-shutorg |  | 未声明 | okay |  |
| /pinctrl/uart0 |  | 未声明 | okay |  |
| /pinctrl/uart0/uart0-xfer |  | 未声明 | okay |  |
| /pinctrl/uart1 |  | 未声明 | okay |  |
| /pinctrl/uart1/uart1m0-xfer |  | 未声明 | okay |  |
| /pinctrl/uart2 |  | 未声明 | okay |  |
| /pinctrl/uart2/uart2m0-xfer |  | 未声明 | okay |  |
| /pinctrl/uart3 |  | 未声明 | okay |  |
| /pinctrl/uart3/uart3m1-xfer |  | 未声明 | okay |  |
| /pinctrl/uart4 |  | 未声明 | okay |  |
| /pinctrl/uart4/uart4m1-xfer |  | 未声明 | okay |  |
| /pinctrl/uart5 |  | 未声明 | okay |  |
| /pinctrl/uart5/uart5m0-xfer |  | 未声明 | okay |  |
| /pinctrl/uart6 |  | 未声明 | okay |  |
| /pinctrl/uart6/uart6m0-xfer |  | 未声明 | okay |  |
| /pinctrl/uart7 |  | 未声明 | okay |  |
| /pinctrl/uart7/uart7m1-xfer |  | 未声明 | okay |  |
| /pinctrl/uart8 |  | 未声明 | okay |  |
| /pinctrl/uart8/uart8m0-ctsn |  | 未声明 | okay |  |
| /pinctrl/uart8/uart8m0-rtsn |  | 未声明 | okay |  |
| /pinctrl/uart8/uart8m0-xfer |  | 未声明 | okay |  |
| /pinctrl/uart9 |  | 未声明 | okay |  |
| /pinctrl/uart9/uart9m0-xfer |  | 未声明 | okay |  |
| /pinctrl/usb |  | 未声明 | okay |  |
| /pinctrl/usb/vcc5v0-host-en |  | 未声明 | okay |  |
| /pinctrl/usb/vcc5v0-otg-en |  | 未声明 | okay |  |
| /pinctrl/vop |  | 未声明 | okay |  |
| /pinctrl/wireless-bluetooth |  | 未声明 | okay |  |
| /pinctrl/wireless-bluetooth/uart8-gpios |  | 未声明 | okay |  |
| /pinctrl/wireless-wlan |  | 未声明 | okay |  |
| /pinctrl/wireless-wlan/wifi-host-wake-irq |  | 未声明 | okay |  |
| /power-management@fdd90000 | rockchip,rk3568-pmu, syscon, simple-mfd | 未声明 | okay | platform:fdd90000.power-management (no driver link) |
| /power-management@fdd90000/power-controller | rockchip,rk3568-power-controller | okay | okay | platform:fdd90000.power-management:power-controller -> rockchip-pm-domain |
| /power-management@fdd90000/power-controller/pd_gpu@7 |  | 未声明 | okay |  |
| /power-management@fdd90000/power-controller/pd_npu@6 |  | 未声明 | okay |  |
| /power-management@fdd90000/power-controller/pd_pipe@15 |  | 未声明 | okay |  |
| /power-management@fdd90000/power-controller/pd_rga@10 |  | 未声明 | okay |  |
| /power-management@fdd90000/power-controller/pd_rkvdec@13 |  | 未声明 | okay |  |
| /power-management@fdd90000/power-controller/pd_rkvenc@14 |  | 未声明 | okay |  |
| /power-management@fdd90000/power-controller/pd_vi@8 |  | 未声明 | okay |  |
| /power-management@fdd90000/power-controller/pd_vo@9 |  | 未声明 | okay |  |
| /power-management@fdd90000/power-controller/pd_vpu@11 |  | 未声明 | okay |  |
| /psci | arm,psci-1.0 | 未声明 | okay | platform:psci -> psci-cpuidle-domain |
| /pvtm@fde00000 | rockchip,rk3568-core-pvtm | 未声明 | okay | platform:fde00000.pvtm -> rockchip-pvtm |
| /pvtm@fde00000/pvtm@0 |  | 未声明 | okay |  |
| /pvtm@fde80000 | rockchip,rk3568-gpu-pvtm | 未声明 | okay | platform:fde80000.pvtm -> rockchip-pvtm |
| /pvtm@fde80000/pvtm@1 |  | 未声明 | okay |  |
| /pvtm@fde90000 | rockchip,rk3568-npu-pvtm | 未声明 | okay | platform:fde90000.pvtm -> rockchip-pvtm |
| /pvtm@fde90000/pvtm@2 |  | 未声明 | okay |  |
| /pwm@fdd70000 | rockchip,rk3568-pwm, rockchip,rk3328-pwm | disabled | disabled @ /pwm@fdd70000 |  |
| /pwm@fdd70010 | rockchip,rk3568-pwm, rockchip,rk3328-pwm | disabled | disabled @ /pwm@fdd70010 |  |
| /pwm@fdd70020 | rockchip,rk3568-pwm, rockchip,rk3328-pwm | disabled | disabled @ /pwm@fdd70020 |  |
| /pwm@fdd70030 | rockchip,rk3568-pwm, rockchip,rk3328-pwm | okay | okay | platform:fdd70030.pwm -> rockchip-pwm |
| /pwm@fe6e0000 | rockchip,rk3568-pwm, rockchip,rk3328-pwm | okay | okay | platform:fe6e0000.pwm -> rockchip-pwm |
| /pwm@fe6e0010 | rockchip,rk3568-pwm, rockchip,rk3328-pwm | disabled | disabled @ /pwm@fe6e0010 |  |
| /pwm@fe6e0020 | rockchip,rk3568-pwm, rockchip,rk3328-pwm | disabled | disabled @ /pwm@fe6e0020 |  |
| /pwm@fe6e0030 | rockchip,remotectl-pwm | okay | okay | platform:fe6e0030.pwm -> remotectl-pwm |
| /pwm@fe6e0030/ir_key1 |  | 未声明 | okay |  |
| /pwm@fe6e0030/ir_key2 |  | 未声明 | okay |  |
| /pwm@fe6e0030/ir_key3 |  | 未声明 | okay |  |
| /pwm@fe6e0030/ir_key4 |  | 未声明 | okay |  |
| /pwm@fe6e0030/ir_key5 |  | 未声明 | okay |  |
| /pwm@fe6e0030/ir_key6 |  | 未声明 | okay |  |
| /pwm@fe6e0030/ir_key7 |  | 未声明 | okay |  |
| /pwm@fe6e0030/ir_key8 |  | 未声明 | okay |  |
| /pwm@fe6e0030/ir_key9 |  | 未声明 | okay |  |
| /pwm@fe6f0000 | rockchip,rk3568-pwm, rockchip,rk3328-pwm | disabled | disabled @ /pwm@fe6f0000 |  |
| /pwm@fe6f0010 | rockchip,rk3568-pwm, rockchip,rk3328-pwm | disabled | disabled @ /pwm@fe6f0010 |  |
| /pwm@fe6f0020 | rockchip,rk3568-pwm, rockchip,rk3328-pwm | disabled | disabled @ /pwm@fe6f0020 |  |
| /pwm@fe6f0030 | rockchip,rk3568-pwm, rockchip,rk3328-pwm | disabled | disabled @ /pwm@fe6f0030 |  |
| /pwm@fe700000 | rockchip,rk3568-pwm, rockchip,rk3328-pwm | disabled | disabled @ /pwm@fe700000 |  |
| /pwm@fe700010 | rockchip,rk3568-pwm, rockchip,rk3328-pwm | disabled | disabled @ /pwm@fe700010 |  |
| /pwm@fe700020 | rockchip,rk3568-pwm, rockchip,rk3328-pwm | disabled | disabled @ /pwm@fe700020 |  |
| /pwm@fe700030 | rockchip,rk3568-pwm, rockchip,rk3328-pwm | disabled | disabled @ /pwm@fe700030 |  |
| /qos@fe128000 | syscon | 未声明 | okay | platform:fe128000.qos (no driver link) |
| /qos@fe138080 | syscon | 未声明 | okay | platform:fe138080.qos (no driver link) |
| /qos@fe138100 | syscon | 未声明 | okay | platform:fe138100.qos (no driver link) |
| /qos@fe138180 | syscon | 未声明 | okay | platform:fe138180.qos (no driver link) |
| /qos@fe148000 | syscon | 未声明 | okay | platform:fe148000.qos (no driver link) |
| /qos@fe148080 | syscon | 未声明 | okay | platform:fe148080.qos (no driver link) |
| /qos@fe148100 | syscon | 未声明 | okay | platform:fe148100.qos (no driver link) |
| /qos@fe150000 | syscon | 未声明 | okay | platform:fe150000.qos (no driver link) |
| /qos@fe158000 | syscon | 未声明 | okay | platform:fe158000.qos (no driver link) |
| /qos@fe158100 | syscon | 未声明 | okay | platform:fe158100.qos (no driver link) |
| /qos@fe158180 | syscon | 未声明 | okay | platform:fe158180.qos (no driver link) |
| /qos@fe158200 | syscon | 未声明 | okay | platform:fe158200.qos (no driver link) |
| /qos@fe158280 | syscon | 未声明 | okay | platform:fe158280.qos (no driver link) |
| /qos@fe158300 | syscon | 未声明 | okay | platform:fe158300.qos (no driver link) |
| /qos@fe180000 | syscon | 未声明 | okay | platform:fe180000.qos (no driver link) |
| /qos@fe190000 | syscon | 未声明 | okay | platform:fe190000.qos (no driver link) |
| /qos@fe190080 | syscon | 未声明 | okay | platform:fe190080.qos (no driver link) |
| /qos@fe190100 | syscon | 未声明 | okay | platform:fe190100.qos (no driver link) |
| /qos@fe190200 | syscon | 未声明 | okay | platform:fe190200.qos (no driver link) |
| /qos@fe190280 | syscon | 未声明 | okay | platform:fe190280.qos (no driver link) |
| /qos@fe190300 | syscon | 未声明 | okay | platform:fe190300.qos (no driver link) |
| /qos@fe190380 | syscon | 未声明 | okay | platform:fe190380.qos (no driver link) |
| /qos@fe190400 | syscon | 未声明 | okay | platform:fe190400.qos (no driver link) |
| /qos@fe198000 | syscon | 未声明 | okay | platform:fe198000.qos (no driver link) |
| /qos@fe1a8000 | syscon | 未声明 | okay | platform:fe1a8000.qos (no driver link) |
| /qos@fe1a8080 | syscon | 未声明 | okay | platform:fe1a8080.qos (no driver link) |
| /qos@fe1a8100 | syscon | 未声明 | okay | platform:fe1a8100.qos (no driver link) |
| /reserved-memory |  | 未声明 | okay |  |
| /reserved-memory/drm-cubic-lut@00000000 | rockchip,drm-cubic-lut | 未声明 | okay |  |
| /reserved-memory/drm-logo@00000000 | rockchip,drm-logo | 未声明 | okay |  |
| /reserved-memory/ramoops@110000 | ramoops | 未声明 | okay | platform:110000.ramoops -> ramoops |
| /rk809-sound | rockchip,multicodecs-card | okay | okay | platform:rk809-sound -> rk-multicodecs |
| /rk_rga@fdeb0000 | rockchip,rga2 | okay | okay | platform:fdeb0000.rk_rga -> rga2 |
| /rkcif@fdfe0000 | rockchip,rk3568-cif | disabled | disabled @ /rkcif@fdfe0000 |  |
| /rkcif_dvp | rockchip,rkcif-dvp | disabled | disabled @ /rkcif_dvp |  |
| /rkcif_dvp_sditf | rockchip,rkcif-sditf | disabled | disabled @ /rkcif_dvp_sditf |  |
| /rkcif_mipi_lvds | rockchip,rkcif-mipi-lvds | disabled | disabled @ /rkcif_mipi_lvds |  |
| /rkcif_mipi_lvds_sditf | rockchip,rkcif-sditf | disabled | disabled @ /rkcif_mipi_lvds_sditf |  |
| /rkisp-vir0 | rockchip,rkisp-vir | okay | okay | platform:rkisp-vir0 -> rkisp |
| /rkisp-vir0/port |  | 未声明 | okay |  |
| /rkisp-vir0/port/endpoint@0 |  | 未声明 | okay |  |
| /rkisp-vir1 | rockchip,rkisp-vir | disabled | disabled @ /rkisp-vir1 |  |
| /rkisp@fdff0000 | rockchip,rk3568-rkisp | okay | okay | platform:fdff0000.rkisp -> rkisp_hw |
| /rkscr@fe560000 | rockchip-scr | disabled | disabled @ /rkscr@fe560000 |  |
| /rkvdec-opp-table | operating-points-v2 | 未声明 | okay |  |
| /rkvdec-opp-table/opp-297000000 |  | 未声明 | okay |  |
| /rkvdec-opp-table/opp-400000000 |  | 未声明 | okay |  |
| /rkvdec@fdf80200 | rockchip,rkv-decoder-rk3568, rockchip,rkv-decoder-v2 | okay | okay | platform:fdf80200.rkvdec -> mpp_rkvdec2 |
| /rkvenc-opp-table | operating-points-v2 | 未声明 | okay |  |
| /rkvenc-opp-table/opp-297000000 |  | 未声明 | okay |  |
| /rkvenc-opp-table/opp-400000000 |  | 未声明 | okay |  |
| /rkvenc@fdf40000 | rockchip,rkv-encoder-v1 | okay | okay | platform:fdf40000.rkvenc -> mpp_rkvenc |
| /rng@fe388000 | rockchip,cryptov2-rng | okay | okay | platform:fe388000.rng -> rockchip-rng |
| /rockchip-suspend | rockchip,pm-rk3568 | okay | okay | platform:rockchip-suspend -> rockchip-pm |
| /rockchip-system-monitor | rockchip,system-monitor | 未声明 | okay | platform:rockchip-system-monitor -> rockchip-system-monitor |
| /saradc@fe720000 | rockchip,rk3568-saradc, rockchip,rk3399-saradc | okay | okay | iio:iio:device0 (no driver link); platform:fe720000.saradc -> rockchip-saradc |
| /sata@fc000000 | snps,dwc-ahci | okay | okay | platform:fc000000.sata -> ahci |
| /sata@fc400000 | snps,dwc-ahci | disabled | disabled @ /sata@fc400000 |  |
| /sata@fc800000 | snps,dwc-ahci | disabled | disabled @ /sata@fc800000 |  |
| /scmi-shmem@10f000 | arm,scmi-shmem | 未声明 | okay | platform:10f000.scmi-shmem (no driver link) |
| /sdhci@fe310000 | rockchip,rk3568-dwcmshc, rockchip,dwcmshc-sdhci | okay | okay | platform:fe310000.sdhci -> sdhci-dwcmshc |
| /sdio-pwrseq | mmc-pwrseq-simple | 未声明 | okay | platform:sdio-pwrseq -> pwrseq_simple |
| /serial@fdd50000 | rockchip,rk3568-uart, snps,dw-apb-uart | okay | okay | platform:fdd50000.serial -> dw-apb-uart |
| /serial@fe650000 | rockchip,rk3568-uart, snps,dw-apb-uart | disabled | disabled @ /serial@fe650000 |  |
| /serial@fe660000 | rockchip,rk3568-uart, snps,dw-apb-uart | disabled | disabled @ /serial@fe660000 |  |
| /serial@fe670000 | rockchip,rk3568-uart, snps,dw-apb-uart | okay | okay | platform:fe670000.serial -> dw-apb-uart |
| /serial@fe680000 | rockchip,rk3568-uart, snps,dw-apb-uart | okay | okay | platform:fe680000.serial -> dw-apb-uart |
| /serial@fe690000 | rockchip,rk3568-uart, snps,dw-apb-uart | disabled | disabled @ /serial@fe690000 |  |
| /serial@fe6a0000 | rockchip,rk3568-uart, snps,dw-apb-uart | disabled | disabled @ /serial@fe6a0000 |  |
| /serial@fe6b0000 | rockchip,rk3568-uart, snps,dw-apb-uart | okay | okay | platform:fe6b0000.serial -> dw-apb-uart |
| /serial@fe6c0000 | rockchip,rk3568-uart, snps,dw-apb-uart | okay | okay | platform:fe6c0000.serial -> dw-apb-uart |
| /serial@fe6d0000 | rockchip,rk3568-uart, snps,dw-apb-uart | disabled | disabled @ /serial@fe6d0000 |  |
| /spdif@fe460000 | rockchip,rk3568-spdif | disabled | disabled @ /spdif@fe460000 |  |
| /spi@fe300000 | rockchip,sfc | disabled | disabled @ /spi@fe300000 |  |
| /spi@fe610000 | rockchip,rk3066-spi | disabled | disabled @ /spi@fe610000 |  |
| /spi@fe620000 | rockchip,rk3066-spi | disabled | disabled @ /spi@fe620000 |  |
| /spi@fe630000 | rockchip,rk3066-spi | disabled | disabled @ /spi@fe630000 |  |
| /spi@fe640000 | rockchip,rk3066-spi | okay | okay | platform:fe640000.spi -> rockchip-spi |
| /spi@fe640000/spi_test@0 | rockchip,spidev | 未声明 | okay | spi:spi3.0 -> spidev |
| /sram@fdcc0000 | mmio-sram | 未声明 | okay | platform:fdcc0000.sram -> sram |
| /sram@fdcc0000/rkvdec-sram@0 |  | 未声明 | okay |  |
| /syscon@fda00000 | rockchip,rk3568-xpcs, syscon | disabled | disabled @ /syscon@fda00000 |  |
| /syscon@fdc20000 | rockchip,rk3568-pmugrf, syscon, simple-mfd | 未声明 | okay | platform:fdc20000.syscon (no driver link) |
| /syscon@fdc20000/io-domains | rockchip,rk3568-pmu-io-voltage-domain | okay | okay | platform:fdc20000.syscon:io-domains -> rockchip-iodomain |
| /syscon@fdc20000/reboot-mode | syscon-reboot-mode | 未声明 | okay | platform:fdc20000.syscon:reboot-mode -> syscon-reboot-mode |
| /syscon@fdc50000 | rockchip,rk3568-pipegrf, syscon | 未声明 | okay | platform:fdc50000.syscon (no driver link) |
| /syscon@fdc60000 | rockchip,rk3568-grf, syscon, simple-mfd | 未声明 | okay | platform:fdc60000.syscon (no driver link) |
| /syscon@fdc60000/io-domains | rockchip,rk3568-io-voltage-domain | disabled | disabled @ /syscon@fdc60000/io-domains |  |
| /syscon@fdc60000/lvds | rockchip,rk3568-lvds | disabled | disabled @ /syscon@fdc60000/lvds |  |
| /syscon@fdc60000/lvds/ports |  | 未声明 | disabled @ /syscon@fdc60000/lvds |  |
| /syscon@fdc60000/lvds/ports/port@0 |  | 未声明 | disabled @ /syscon@fdc60000/lvds |  |
| /syscon@fdc60000/lvds/ports/port@0/endpoint@1 |  | disabled | disabled @ /syscon@fdc60000/lvds |  |
| /syscon@fdc60000/lvds/ports/port@0/endpoint@2 |  | disabled | disabled @ /syscon@fdc60000/lvds |  |
| /syscon@fdc60000/lvds1 | rockchip,rk3568-lvds | disabled | disabled @ /syscon@fdc60000/lvds1 |  |
| /syscon@fdc60000/lvds1/ports |  | 未声明 | disabled @ /syscon@fdc60000/lvds1 |  |
| /syscon@fdc60000/lvds1/ports/port@0 |  | 未声明 | disabled @ /syscon@fdc60000/lvds1 |  |
| /syscon@fdc60000/lvds1/ports/port@0/endpoint@0 |  | 未声明 | disabled @ /syscon@fdc60000/lvds1 |  |
| /syscon@fdc60000/lvds1/ports/port@0/endpoint@1 |  | 未声明 | disabled @ /syscon@fdc60000/lvds1 |  |
| /syscon@fdc60000/rgb | rockchip,rk3568-rgb | disabled | disabled @ /syscon@fdc60000/rgb |  |
| /syscon@fdc60000/rgb/ports |  | 未声明 | disabled @ /syscon@fdc60000/rgb |  |
| /syscon@fdc60000/rgb/ports/port@0 |  | 未声明 | disabled @ /syscon@fdc60000/rgb |  |
| /syscon@fdc60000/rgb/ports/port@0/endpoint@2 |  | disabled | disabled @ /syscon@fdc60000/rgb |  |
| /syscon@fdc70000 | rockchip,pipe-phy-grf, syscon | 未声明 | okay | platform:fdc70000.syscon (no driver link) |
| /syscon@fdc80000 | rockchip,pipe-phy-grf, syscon | 未声明 | okay | platform:fdc80000.syscon (no driver link) |
| /syscon@fdc90000 | rockchip,pipe-phy-grf, syscon | 未声明 | okay | platform:fdc90000.syscon (no driver link) |
| /syscon@fdca0000 | rockchip,rk3568-usb2phy-grf, syscon | 未声明 | okay | platform:fdca0000.syscon (no driver link) |
| /syscon@fdca8000 | rockchip,rk3568-usb2phy-grf, syscon | 未声明 | okay | platform:fdca8000.syscon (no driver link) |
| /syscon@fdcb0000 | rockchip,rk3568-edp-phy-grf, syscon, simple-mfd | 未声明 | okay | platform:fdcb0000.syscon -> rockchip-edp-phy-grf |
| /syscon@fdcb0000/edp-phy | rockchip,rk3568-edp-phy | disabled | disabled @ /syscon@fdcb0000/edp-phy |  |
| /syscon@fdcb8000 | rockchip,pcie30-phy-grf, syscon | 未声明 | okay | platform:fdcb8000.syscon (no driver link) |
| /thermal-zones |  | 未声明 | okay |  |
| /thermal-zones/gpu-thermal |  | 未声明 | okay |  |
| /thermal-zones/soc-thermal |  | 未声明 | okay |  |
| /thermal-zones/soc-thermal/cooling-maps |  | 未声明 | okay |  |
| /thermal-zones/soc-thermal/cooling-maps/map0 |  | 未声明 | okay |  |
| /thermal-zones/soc-thermal/cooling-maps/map1 |  | 未声明 | okay |  |
| /thermal-zones/soc-thermal/trips |  | 未声明 | okay |  |
| /thermal-zones/soc-thermal/trips/soc-crit |  | 未声明 | okay |  |
| /thermal-zones/soc-thermal/trips/trip-point-0 |  | 未声明 | okay |  |
| /thermal-zones/soc-thermal/trips/trip-point-1 |  | 未声明 | okay |  |
| /timer | arm,armv8-timer | 未声明 | okay | platform:timer (no driver link) |
| /timer@fe5f0000 | rockchip,rk3568-timer, rockchip,rk3288-timer | 未声明 | okay | platform:fe5f0000.timer (no driver link) |
| /tsadc@fe710000 | rockchip,rk3568-tsadc | okay | okay | platform:fe710000.tsadc -> rockchip-thermal |
| /tsadc@fe710000/tsadc@0 |  | 未声明 | okay |  |
| /tsadc@fe710000/tsadc@1 |  | 未声明 | okay |  |
| /uio@fe010000 | rockchip,uio-gmac | disabled | disabled @ /uio@fe010000 |  |
| /uio@fe2a0000 | rockchip,uio-gmac | disabled | disabled @ /uio@fe2a0000 |  |
| /usb2-phy@fe8a0000 | rockchip,rk3568-usb2phy | okay | okay | platform:fe8a0000.usb2-phy -> rockchip-usb2phy |
| /usb2-phy@fe8a0000/host-port |  | okay | okay |  |
| /usb2-phy@fe8a0000/otg-port |  | okay | okay |  |
| /usb2-phy@fe8b0000 | rockchip,rk3568-usb2phy | okay | okay | platform:fe8b0000.usb2-phy -> rockchip-usb2phy |
| /usb2-phy@fe8b0000/host-port |  | okay | okay |  |
| /usb2-phy@fe8b0000/otg-port |  | okay | okay |  |
| /usb@fd800000 | generic-ehci | okay | okay | platform:fd800000.usb -> ehci-platform; usb:1-0:1.0 -> hub; usb:usb1 -> usb |
| /usb@fd840000 | generic-ohci | okay | okay | platform:fd840000.usb -> ohci-platform; usb:3-0:1.0 -> hub; usb:usb3 -> usb |
| /usb@fd880000 | generic-ehci | okay | okay | platform:fd880000.usb -> ehci-platform; usb:2-0:1.0 -> hub; usb:usb2 -> usb |
| /usb@fd8c0000 | generic-ohci | okay | okay | platform:fd8c0000.usb -> ohci-platform; usb:4-0:1.0 -> hub; usb:usb4 -> usb |
| /usbdrd | rockchip,rk3568-dwc3, rockchip,rk3399-dwc3 | okay | okay | platform:usbdrd -> dwc3-of-simple |
| /usbdrd/dwc3@fcc00000 | snps,dwc3 | okay | okay | platform:fcc00000.dwc3 -> dwc3 |
| /usbhost | rockchip,rk3568-dwc3, rockchip,rk3399-dwc3 | okay | okay | platform:usbhost -> dwc3-of-simple |
| /usbhost/dwc3@fd000000 | snps,dwc3 | okay | okay | platform:fd000000.dwc3 -> dwc3; usb:5-0:1.0 -> hub; usb:6-0:1.0 -> hub; usb:usb5 -> usb; usb:usb6 -> usb |
| /vad-sound | rockchip,multicodecs-card | disabled | disabled @ /vad-sound |  |
| /vad@fe450000 | rockchip,rk3568-vad | disabled | disabled @ /vad@fe450000 |  |
| /vcc1v8-cam | regulator-fixed | 未声明 | okay | platform:vcc1v8-cam -> reg-fixed-voltage |
| /vcc2v5-ddr | regulator-fixed | 未声明 | okay | platform:vcc2v5-ddr -> reg-fixed-voltage |
| /vcc3v3-bu | regulator-fixed | 未声明 | okay | platform:vcc3v3-bu -> reg-fixed-voltage |
| /vcc3v3-lcd0-n | regulator-fixed | 未声明 | okay | platform:vcc3v3-lcd0-n -> reg-fixed-voltage |
| /vcc3v3-lcd0-n/regulator-state-mem |  | 未声明 | okay |  |
| /vcc3v3-mipi-con | regulator-fixed | 未声明 | okay | platform:vcc3v3-mipi-con -> reg-fixed-voltage |
| /vcc3v3-sys | regulator-fixed | 未声明 | okay | platform:vcc3v3-sys -> reg-fixed-voltage |
| /vcc5v0-host-regulator | regulator-fixed | 未声明 | okay | platform:vcc5v0-host-regulator -> reg-fixed-voltage |
| /vcc5v0-otg-regulator | regulator-fixed | 未声明 | okay | platform:vcc5v0-otg-regulator -> reg-fixed-voltage |
| /vcc5v0-sys | regulator-fixed | 未声明 | okay | platform:vcc5v0-sys -> reg-fixed-voltage |
| /vcc5v0-usb | regulator-fixed | 未声明 | okay | platform:vcc5v0-usb -> reg-fixed-voltage |
| /vdpu@fdea0400 | rockchip,vpu-decoder-v2 | okay | okay | platform:fdea0400.vdpu -> mpp_vdpu2 |
| /vepu@fdee0000 | rockchip,vpu-encoder-v2 | okay | okay | platform:fdee0000.vepu -> mpp_vepu2 |
| /vop@fe040000 | rockchip,rk3568-vop | okay | okay | platform:fe040000.vop -> rockchip-vop2 |
| /vop@fe040000/ports |  | 未声明 | okay |  |
| /vop@fe040000/ports/port@0 |  | 未声明 | okay |  |
| /vop@fe040000/ports/port@0/endpoint@0 |  | 未声明 | okay |  |
| /vop@fe040000/ports/port@0/endpoint@1 |  | 未声明 | okay |  |
| /vop@fe040000/ports/port@0/endpoint@2 |  | 未声明 | okay |  |
| /vop@fe040000/ports/port@0/endpoint@3 |  | 未声明 | okay |  |
| /vop@fe040000/ports/port@1 |  | 未声明 | okay |  |
| /vop@fe040000/ports/port@1/endpoint@0 |  | 未声明 | okay |  |
| /vop@fe040000/ports/port@1/endpoint@1 |  | 未声明 | okay |  |
| /vop@fe040000/ports/port@1/endpoint@2 |  | 未声明 | okay |  |
| /vop@fe040000/ports/port@1/endpoint@3 |  | 未声明 | okay |  |
| /vop@fe040000/ports/port@1/endpoint@4 |  | 未声明 | okay |  |
| /vop@fe040000/ports/port@1/endpoint@5 |  | 未声明 | okay |  |
| /vop@fe040000/ports/port@2 |  | 未声明 | okay |  |
| /vop@fe040000/ports/port@2/endpoint@0 |  | 未声明 | okay |  |
| /vop@fe040000/ports/port@2/endpoint@1 |  | 未声明 | okay |  |
| /vop@fe040000/ports/port@2/endpoint@2 |  | 未声明 | okay |  |
| /watchdog@fe600000 | snps,dw-wdt | okay | okay | platform:fe600000.watchdog -> dw_wdt |
| /wireless-bluetooth | bluetooth-platdata | okay | okay | platform:wireless-bluetooth -> rfkill_bt |
| /wireless-wlan | wlan-platdata | okay | okay | platform:wireless-wlan -> wlan-platdata |
| /xin24m | fixed-clock | 未声明 | okay |  |
| /xin32k | fixed-clock | 未声明 | okay |  |
| /xpcs-gmac0-clock | fixed-clock | 未声明 | okay |  |
| /xpcs-gmac1-clock | fixed-clock | 未声明 | okay |  |

## 全部已枚举总线设备

### amba (2)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| fe530000.dmac | /sys/bus/amba/drivers/dma-pl330 | /sys/firmware/devicetree/base/dmac@fe530000 | /sys/devices/platform/fe530000.dmac |
| fe550000.dmac | /sys/bus/amba/drivers/dma-pl330 | /sys/firmware/devicetree/base/dmac@fe550000 | /sys/devices/platform/fe550000.dmac |

### cec (1)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| cec0 | 无 driver 链接 |  | /sys/devices/platform/fe0a0000.hdmi/cec0 |

### clockevents (5)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| broadcast | 无 driver 链接 |  | /sys/devices/system/clockevents/broadcast |
| clockevent0 | 无 driver 链接 |  | /sys/devices/system/clockevents/clockevent0 |
| clockevent1 | 无 driver 链接 |  | /sys/devices/system/clockevents/clockevent1 |
| clockevent2 | 无 driver 链接 |  | /sys/devices/system/clockevents/clockevent2 |
| clockevent3 | 无 driver 链接 |  | /sys/devices/system/clockevents/clockevent3 |

### clocksource (1)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| clocksource0 | 无 driver 链接 |  | /sys/devices/system/clocksource/clocksource0 |

### cpu (4)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| cpu0 | 无 driver 链接 | /sys/firmware/devicetree/base/cpus/cpu@0 | /sys/devices/system/cpu/cpu0 |
| cpu1 | 无 driver 链接 | /sys/firmware/devicetree/base/cpus/cpu@100 | /sys/devices/system/cpu/cpu1 |
| cpu2 | 无 driver 链接 | /sys/firmware/devicetree/base/cpus/cpu@200 | /sys/devices/system/cpu/cpu2 |
| cpu3 | 无 driver 链接 | /sys/firmware/devicetree/base/cpus/cpu@300 | /sys/devices/system/cpu/cpu3 |

### edac (1)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| mc | 无 driver 链接 |  | /sys/devices/system/edac/mc |

### event_source (5)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| armv8_cortex_a55 | 无 driver 链接 |  | /sys/devices/armv8_cortex_a55 |
| breakpoint | 无 driver 链接 |  | /sys/devices/breakpoint |
| software | 无 driver 链接 |  | /sys/devices/software |
| tracepoint | 无 driver 链接 |  | /sys/devices/tracepoint |
| uprobe | 无 driver 链接 |  | /sys/devices/uprobe |

### gpio (6)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| gpiochip0 | 无 driver 链接 | /sys/firmware/devicetree/base/pinctrl/gpio0@fdd60000 | /sys/devices/platform/pinctrl/fdd60000.gpio0/gpiochip0 |
| gpiochip1 | 无 driver 链接 | /sys/firmware/devicetree/base/pinctrl/gpio1@fe740000 | /sys/devices/platform/pinctrl/fe740000.gpio1/gpiochip1 |
| gpiochip2 | 无 driver 链接 | /sys/firmware/devicetree/base/pinctrl/gpio2@fe750000 | /sys/devices/platform/pinctrl/fe750000.gpio2/gpiochip2 |
| gpiochip3 | 无 driver 链接 | /sys/firmware/devicetree/base/pinctrl/gpio3@fe760000 | /sys/devices/platform/pinctrl/fe760000.gpio3/gpiochip3 |
| gpiochip4 | 无 driver 链接 | /sys/firmware/devicetree/base/pinctrl/gpio4@fe770000 | /sys/devices/platform/pinctrl/fe770000.gpio4/gpiochip4 |
| gpiochip5 | /sys/bus/gpio/drivers/gpio_stub_drv | /sys/firmware/devicetree/base/i2c@fdd40000/pmic@20/pinctrl_rk8xx | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/rk805-pinctrl/gpiochip5 |

### hid (3)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| 0003:1532:006E.0001 | /sys/bus/hid/drivers/hid-generic |  | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.0/0003:1532:006E.0001 |
| 0003:1532:006E.0002 | /sys/bus/hid/drivers/hid-generic |  | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.1/0003:1532:006E.0002 |
| 0003:1532:006E.0003 | /sys/bus/hid/drivers/hid-generic |  | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.2/0003:1532:006E.0003 |

### i2c (12)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| 0-001c | /sys/bus/i2c/drivers/fan53555-regulator | /sys/firmware/devicetree/base/i2c@fdd40000/tcs4525@1c | /sys/devices/platform/fdd40000.i2c/i2c-0/0-001c |
| 0-0020 | /sys/bus/i2c/drivers/rk808 | /sys/firmware/devicetree/base/i2c@fdd40000/pmic@20 | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020 |
| 1-005d | /sys/bus/i2c/drivers/Goodix-TS | /sys/firmware/devicetree/base/i2c@fe5a0000/gt9xx@5d | /sys/devices/platform/fe5a0000.i2c/i2c-1/1-005d |
| 4-0036 | 无 driver 链接 | /sys/firmware/devicetree/base/i2c@fe5d0000/ov5647@36 | /sys/devices/platform/fe5d0000.i2c/i2c-4/4-0036 |
| 5-0051 | /sys/bus/i2c/drivers/rtc-hym8563 | /sys/firmware/devicetree/base/i2c@fe5e0000/hym8563@51 | /sys/devices/platform/fe5e0000.i2c/i2c-5/5-0051 |
| i2c-0 | 无 driver 链接 | /sys/firmware/devicetree/base/i2c@fdd40000 | /sys/devices/platform/fdd40000.i2c/i2c-0 |
| i2c-1 | 无 driver 链接 | /sys/firmware/devicetree/base/i2c@fe5a0000 | /sys/devices/platform/fe5a0000.i2c/i2c-1 |
| i2c-2 | 无 driver 链接 | /sys/firmware/devicetree/base/i2c@fe5b0000 | /sys/devices/platform/fe5b0000.i2c/i2c-2 |
| i2c-3 | 无 driver 链接 | /sys/firmware/devicetree/base/i2c@fe5c0000 | /sys/devices/platform/fe5c0000.i2c/i2c-3 |
| i2c-4 | 无 driver 链接 | /sys/firmware/devicetree/base/i2c@fe5d0000 | /sys/devices/platform/fe5d0000.i2c/i2c-4 |
| i2c-5 | 无 driver 链接 | /sys/firmware/devicetree/base/i2c@fe5e0000 | /sys/devices/platform/fe5e0000.i2c/i2c-5 |
| i2c-6 | 无 driver 链接 |  | /sys/devices/platform/fe0a0000.hdmi/i2c-6 |

### iio (2)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| iio:device0 | 无 driver 链接 | /sys/firmware/devicetree/base/saradc@fe720000 | /sys/devices/platform/fe720000.saradc/iio:device0 |
| iio_sysfs_trigger | 无 driver 链接 |  | /sys/devices/iio_sysfs_trigger |

### mdio_bus (2)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| stmmac-0:00 | /sys/bus/mdio_bus/drivers/MAE0621A-Q2C Gigabit Ethernet | /sys/firmware/devicetree/base/ethernet@fe2a0000/mdio/phy@0 | /sys/devices/platform/fe2a0000.ethernet/mdio_bus/stmmac-0/stmmac-0:00 |
| stmmac-1:00 | /sys/bus/mdio_bus/drivers/MAE0621A-Q2C Gigabit Ethernet | /sys/firmware/devicetree/base/ethernet@fe010000/mdio/phy@0 | /sys/devices/platform/fe010000.ethernet/mdio_bus/stmmac-1/stmmac-1:00 |

### media (1)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| media0 | 无 driver 链接 |  | /sys/devices/platform/rkisp-vir0/media0 |

### mipi-dsi (1)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| fe060000.dsi.0 | /sys/bus/mipi-dsi/drivers/panel-simple-dsi | /sys/firmware/devicetree/base/dsi@fe060000/panel@0 | /sys/devices/platform/fe060000.dsi/fe060000.dsi.0 |

### mmc (2)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| mmc0:0001 | /sys/bus/mmc/drivers/mmcblk |  | /sys/devices/platform/fe310000.sdhci/mmc_host/mmc0/mmc0:0001 |
| mmc3:0001 | 无 driver 链接 |  | /sys/devices/platform/fe000000.dwmmc/mmc_host/mmc3/mmc3:0001 |

### mmc_rpmb (1)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| mmcblk0rpmb | 无 driver 链接 |  | /sys/devices/platform/fe310000.sdhci/mmc_host/mmc0/mmc0:0001/mmcblk0rpmb |

### nvmem (1)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| rockchip-otp0 | 无 driver 链接 | /sys/firmware/devicetree/base/otp@fe38c000 | /sys/devices/platform/fe38c000.otp/rockchip-otp0 |

### platform (204)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| 10f000.scmi-shmem | 无 driver 链接 | /sys/firmware/devicetree/base/scmi-shmem@10f000 | /sys/devices/platform/10f000.scmi-shmem |
| 110000.ramoops | /sys/bus/platform/drivers/ramoops | /sys/firmware/devicetree/base/reserved-memory/ramoops@110000 | /sys/devices/platform/110000.ramoops |
| 3c0000000.pcie | 无 driver 链接 | /sys/firmware/devicetree/base/pcie@fe260000 | /sys/devices/platform/3c0000000.pcie |
| 3c0800000.pcie | 无 driver 链接 | /sys/firmware/devicetree/base/pcie@fe280000 | /sys/devices/platform/3c0800000.pcie |
| Fixed MDIO bus.0 | 无 driver 链接 |  | /sys/devices/platform/Fixed MDIO bus.0 |
| adc-keys | /sys/bus/platform/drivers/adc_keys | /sys/firmware/devicetree/base/adc-keys | /sys/devices/platform/adc-keys |
| alarmtimer.1.auto | /sys/bus/platform/drivers/alarmtimer |  | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/rk808-rtc/rtc/rtc0/alarmtimer.1.auto |
| arm-pmu | /sys/bus/platform/drivers/armv8-pmu | /sys/firmware/devicetree/base/arm-pmu | /sys/devices/platform/arm-pmu |
| backlight-dsi0 | /sys/bus/platform/drivers/pwm-backlight | /sys/firmware/devicetree/base/backlight-dsi0 | /sys/devices/platform/backlight-dsi0 |
| btseekwave.10.auto | /sys/bus/platform/drivers/btseekwave |  | /sys/devices/platform/fe000000.dwmmc/mmc_host/mmc3/mmc3:0001/mmc3:0001:1/btseekwave.10.auto |
| bus-npu | /sys/bus/platform/drivers/rockchip,bus | /sys/firmware/devicetree/base/bus-npu | /sys/devices/platform/bus-npu |
| cpufreq-dt | /sys/bus/platform/drivers/cpufreq-dt |  | /sys/devices/platform/cpufreq-dt |
| cpuinfo | /sys/bus/platform/drivers/rockchip-cpuinfo | /sys/firmware/devicetree/base/cpuinfo | /sys/devices/platform/cpuinfo |
| csi2-dphy0 | /sys/bus/platform/drivers/rockchip-csi2-dphy | /sys/firmware/devicetree/base/csi2-dphy0 | /sys/devices/platform/csi2-dphy0 |
| dc-12v | /sys/bus/platform/drivers/reg-fixed-voltage | /sys/firmware/devicetree/base/dc-12v | /sys/devices/platform/dc-12v |
| display-subsystem | /sys/bus/platform/drivers/rockchip-drm | /sys/firmware/devicetree/base/display-subsystem | /sys/devices/platform/display-subsystem |
| dmabuf | 无 driver 链接 |  | /sys/devices/platform/dmabuf |
| dmc | /sys/bus/platform/drivers/rockchip-dmc | /sys/firmware/devicetree/base/dmc | /sys/devices/platform/dmc |
| dmc-fsp | 无 driver 链接 | /sys/firmware/devicetree/base/dmc-fsp | /sys/devices/platform/dmc-fsp |
| dw-hdmi-cec.4.auto | /sys/bus/platform/drivers/dw-hdmi-cec |  | /sys/devices/platform/fe0a0000.hdmi/dw-hdmi-cec.4.auto |
| dw-hdmi-hdcp.5.auto | /sys/bus/platform/drivers/dw-hdmi-hdcp |  | /sys/devices/platform/fe0a0000.hdmi/dw-hdmi-hdcp.5.auto |
| dw-hdmi-i2s-audio.2.auto | /sys/bus/platform/drivers/dw-hdmi-i2s-audio |  | /sys/devices/platform/fe0a0000.hdmi/dw-hdmi-i2s-audio.2.auto |
| fc000000.sata | /sys/bus/platform/drivers/ahci | /sys/firmware/devicetree/base/sata@fc000000 | /sys/devices/platform/fc000000.sata |
| fcc00000.dwc3 | /sys/bus/platform/drivers/dwc3 | /sys/firmware/devicetree/base/usbdrd/dwc3@fcc00000 | /sys/devices/platform/usbdrd/fcc00000.dwc3 |
| fd000000.dwc3 | /sys/bus/platform/drivers/dwc3 | /sys/firmware/devicetree/base/usbhost/dwc3@fd000000 | /sys/devices/platform/usbhost/fd000000.dwc3 |
| fd800000.usb | /sys/bus/platform/drivers/ehci-platform | /sys/firmware/devicetree/base/usb@fd800000 | /sys/devices/platform/fd800000.usb |
| fd840000.usb | /sys/bus/platform/drivers/ohci-platform | /sys/firmware/devicetree/base/usb@fd840000 | /sys/devices/platform/fd840000.usb |
| fd880000.usb | /sys/bus/platform/drivers/ehci-platform | /sys/firmware/devicetree/base/usb@fd880000 | /sys/devices/platform/fd880000.usb |
| fd8c0000.usb | /sys/bus/platform/drivers/ohci-platform | /sys/firmware/devicetree/base/usb@fd8c0000 | /sys/devices/platform/fd8c0000.usb |
| fd904000.debug | 无 driver 链接 | /sys/firmware/devicetree/base/debug@fd904000 | /sys/devices/platform/fd904000.debug |
| fd90c000.cspmu | 无 driver 链接 | /sys/firmware/devicetree/base/cspmu@fd90c000 | /sys/devices/platform/fd90c000.cspmu |
| fdc20000.syscon | 无 driver 链接 | /sys/firmware/devicetree/base/syscon@fdc20000 | /sys/devices/platform/fdc20000.syscon |
| fdc20000.syscon:io-domains | /sys/bus/platform/drivers/rockchip-iodomain | /sys/firmware/devicetree/base/syscon@fdc20000/io-domains | /sys/devices/platform/fdc20000.syscon/fdc20000.syscon:io-domains |
| fdc20000.syscon:reboot-mode | /sys/bus/platform/drivers/syscon-reboot-mode | /sys/firmware/devicetree/base/syscon@fdc20000/reboot-mode | /sys/devices/platform/fdc20000.syscon/fdc20000.syscon:reboot-mode |
| fdc50000.syscon | 无 driver 链接 | /sys/firmware/devicetree/base/syscon@fdc50000 | /sys/devices/platform/fdc50000.syscon |
| fdc60000.syscon | 无 driver 链接 | /sys/firmware/devicetree/base/syscon@fdc60000 | /sys/devices/platform/fdc60000.syscon |
| fdc70000.syscon | 无 driver 链接 | /sys/firmware/devicetree/base/syscon@fdc70000 | /sys/devices/platform/fdc70000.syscon |
| fdc80000.syscon | 无 driver 链接 | /sys/firmware/devicetree/base/syscon@fdc80000 | /sys/devices/platform/fdc80000.syscon |
| fdc90000.syscon | 无 driver 链接 | /sys/firmware/devicetree/base/syscon@fdc90000 | /sys/devices/platform/fdc90000.syscon |
| fdca0000.syscon | 无 driver 链接 | /sys/firmware/devicetree/base/syscon@fdca0000 | /sys/devices/platform/fdca0000.syscon |
| fdca8000.syscon | 无 driver 链接 | /sys/firmware/devicetree/base/syscon@fdca8000 | /sys/devices/platform/fdca8000.syscon |
| fdcb0000.syscon | /sys/bus/platform/drivers/rockchip-edp-phy-grf | /sys/firmware/devicetree/base/syscon@fdcb0000 | /sys/devices/platform/fdcb0000.syscon |
| fdcb8000.syscon | 无 driver 链接 | /sys/firmware/devicetree/base/syscon@fdcb8000 | /sys/devices/platform/fdcb8000.syscon |
| fdcc0000.sram | /sys/bus/platform/drivers/sram | /sys/firmware/devicetree/base/sram@fdcc0000 | /sys/devices/platform/fdcc0000.sram |
| fdd40000.i2c | /sys/bus/platform/drivers/rk3x-i2c | /sys/firmware/devicetree/base/i2c@fdd40000 | /sys/devices/platform/fdd40000.i2c |
| fdd50000.serial | /sys/bus/platform/drivers/dw-apb-uart | /sys/firmware/devicetree/base/serial@fdd50000 | /sys/devices/platform/fdd50000.serial |
| fdd60000.gpio0 | /sys/bus/platform/drivers/rockchip-gpio | /sys/firmware/devicetree/base/pinctrl/gpio0@fdd60000 | /sys/devices/platform/pinctrl/fdd60000.gpio0 |
| fdd70030.pwm | /sys/bus/platform/drivers/rockchip-pwm | /sys/firmware/devicetree/base/pwm@fdd70030 | /sys/devices/platform/fdd70030.pwm |
| fdd90000.power-management | 无 driver 链接 | /sys/firmware/devicetree/base/power-management@fdd90000 | /sys/devices/platform/fdd90000.power-management |
| fdd90000.power-management:power-controller | /sys/bus/platform/drivers/rockchip-pm-domain | /sys/firmware/devicetree/base/power-management@fdd90000/power-controller | /sys/devices/platform/fdd90000.power-management/fdd90000.power-management:power-controller |
| fde00000.pvtm | /sys/bus/platform/drivers/rockchip-pvtm | /sys/firmware/devicetree/base/pvtm@fde00000 | /sys/devices/platform/fde00000.pvtm |
| fde40000.npu | /sys/bus/platform/drivers/RKNPU | /sys/firmware/devicetree/base/npu@fde40000 | /sys/devices/platform/fde40000.npu |
| fde4b000.iommu | /sys/bus/platform/drivers/rk_iommu | /sys/firmware/devicetree/base/iommu@fde4b000 | /sys/devices/platform/fde4b000.iommu |
| fde60000.gpu | /sys/bus/platform/drivers/mali | /sys/firmware/devicetree/base/gpu@fde60000 | /sys/devices/platform/fde60000.gpu |
| fde80000.pvtm | /sys/bus/platform/drivers/rockchip-pvtm | /sys/firmware/devicetree/base/pvtm@fde80000 | /sys/devices/platform/fde80000.pvtm |
| fde90000.pvtm | /sys/bus/platform/drivers/rockchip-pvtm | /sys/firmware/devicetree/base/pvtm@fde90000 | /sys/devices/platform/fde90000.pvtm |
| fdea0400.vdpu | /sys/bus/platform/drivers/mpp_vdpu2 | /sys/firmware/devicetree/base/vdpu@fdea0400 | /sys/devices/platform/fdea0400.vdpu |
| fdea0800.iommu | /sys/bus/platform/drivers/rk_iommu | /sys/firmware/devicetree/base/iommu@fdea0800 | /sys/devices/platform/fdea0800.iommu |
| fdeb0000.rk_rga | /sys/bus/platform/drivers/rga2 | /sys/firmware/devicetree/base/rk_rga@fdeb0000 | /sys/devices/platform/fdeb0000.rk_rga |
| fded0000.jpegd | /sys/bus/platform/drivers/mpp_jpgdec | /sys/firmware/devicetree/base/jpegd@fded0000 | /sys/devices/platform/fded0000.jpegd |
| fded0480.iommu | /sys/bus/platform/drivers/rk_iommu | /sys/firmware/devicetree/base/iommu@fded0480 | /sys/devices/platform/fded0480.iommu |
| fdee0000.vepu | /sys/bus/platform/drivers/mpp_vepu2 | /sys/firmware/devicetree/base/vepu@fdee0000 | /sys/devices/platform/fdee0000.vepu |
| fdee0800.iommu | /sys/bus/platform/drivers/rk_iommu | /sys/firmware/devicetree/base/iommu@fdee0800 | /sys/devices/platform/fdee0800.iommu |
| fdef0000.iep | /sys/bus/platform/drivers/mpp-iep2 | /sys/firmware/devicetree/base/iep@fdef0000 | /sys/devices/platform/fdef0000.iep |
| fdef0800.iommu | /sys/bus/platform/drivers/rk_iommu | /sys/firmware/devicetree/base/iommu@fdef0800 | /sys/devices/platform/fdef0800.iommu |
| fdf40000.rkvenc | /sys/bus/platform/drivers/mpp_rkvenc | /sys/firmware/devicetree/base/rkvenc@fdf40000 | /sys/devices/platform/fdf40000.rkvenc |
| fdf40f00.iommu | /sys/bus/platform/drivers/rk_iommu | /sys/firmware/devicetree/base/iommu@fdf40f00 | /sys/devices/platform/fdf40f00.iommu |
| fdf80200.rkvdec | /sys/bus/platform/drivers/mpp_rkvdec2 | /sys/firmware/devicetree/base/rkvdec@fdf80200 | /sys/devices/platform/fdf80200.rkvdec |
| fdf80800.iommu | /sys/bus/platform/drivers/rk_iommu | /sys/firmware/devicetree/base/iommu@fdf80800 | /sys/devices/platform/fdf80800.iommu |
| fdfb0000.mipi-csi2-hw | /sys/bus/platform/drivers/rockchip-mipi-csi2-hw | /sys/firmware/devicetree/base/mipi-csi2-hw@fdfb0000 | /sys/devices/platform/fdfb0000.mipi-csi2-hw |
| fdff0000.rkisp | /sys/bus/platform/drivers/rkisp_hw | /sys/firmware/devicetree/base/rkisp@fdff0000 | /sys/devices/platform/fdff0000.rkisp |
| fdff1a00.iommu | /sys/bus/platform/drivers/rk_iommu | /sys/firmware/devicetree/base/iommu@fdff1a00 | /sys/devices/platform/fdff1a00.iommu |
| fe000000.dwmmc | /sys/bus/platform/drivers/dwmmc_rockchip | /sys/firmware/devicetree/base/dwmmc@fe000000 | /sys/devices/platform/fe000000.dwmmc |
| fe010000.ethernet | /sys/bus/platform/drivers/rk_gmac-dwmac | /sys/firmware/devicetree/base/ethernet@fe010000 | /sys/devices/platform/fe010000.ethernet |
| fe040000.vop | /sys/bus/platform/drivers/rockchip-vop2 | /sys/firmware/devicetree/base/vop@fe040000 | /sys/devices/platform/fe040000.vop |
| fe043e00.iommu | /sys/bus/platform/drivers/rk_iommu | /sys/firmware/devicetree/base/iommu@fe043e00 | /sys/devices/platform/fe043e00.iommu |
| fe060000.dsi | /sys/bus/platform/drivers/dw-mipi-dsi-rockchip | /sys/firmware/devicetree/base/dsi@fe060000 | /sys/devices/platform/fe060000.dsi |
| fe0a0000.hdmi | /sys/bus/platform/drivers/dwhdmi-rockchip | /sys/firmware/devicetree/base/hdmi@fe0a0000 | /sys/devices/platform/fe0a0000.hdmi |
| fe102000.nocp-cpu | /sys/bus/platform/drivers/rockchip-nocp | /sys/firmware/devicetree/base/nocp-cpu@fe102000 | /sys/devices/platform/fe102000.nocp-cpu |
| fe102400.nocp-gpu-vpu-rga-venc | /sys/bus/platform/drivers/rockchip-nocp | /sys/firmware/devicetree/base/nocp-gpu-vpu-rga-venc@fe102400 | /sys/devices/platform/fe102400.nocp-gpu-vpu-rga-venc |
| fe102800.nocp-vdec | /sys/bus/platform/drivers/rockchip-nocp | /sys/firmware/devicetree/base/nocp-vdec@fe102800 | /sys/devices/platform/fe102800.nocp-vdec |
| fe102c00.nocp-vi-usb-peri-pipe | /sys/bus/platform/drivers/rockchip-nocp | /sys/firmware/devicetree/base/nocp-vi-usb-peri-pipe@fe102c00 | /sys/devices/platform/fe102c00.nocp-vi-usb-peri-pipe |
| fe103000.nocp-vo | /sys/bus/platform/drivers/rockchip-nocp | /sys/firmware/devicetree/base/nocp-vo@fe103000 | /sys/devices/platform/fe103000.nocp-vo |
| fe128000.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe128000 | /sys/devices/platform/fe128000.qos |
| fe138080.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe138080 | /sys/devices/platform/fe138080.qos |
| fe138100.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe138100 | /sys/devices/platform/fe138100.qos |
| fe138180.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe138180 | /sys/devices/platform/fe138180.qos |
| fe148000.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe148000 | /sys/devices/platform/fe148000.qos |
| fe148080.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe148080 | /sys/devices/platform/fe148080.qos |
| fe148100.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe148100 | /sys/devices/platform/fe148100.qos |
| fe150000.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe150000 | /sys/devices/platform/fe150000.qos |
| fe158000.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe158000 | /sys/devices/platform/fe158000.qos |
| fe158100.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe158100 | /sys/devices/platform/fe158100.qos |
| fe158180.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe158180 | /sys/devices/platform/fe158180.qos |
| fe158200.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe158200 | /sys/devices/platform/fe158200.qos |
| fe158280.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe158280 | /sys/devices/platform/fe158280.qos |
| fe158300.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe158300 | /sys/devices/platform/fe158300.qos |
| fe180000.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe180000 | /sys/devices/platform/fe180000.qos |
| fe190000.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe190000 | /sys/devices/platform/fe190000.qos |
| fe190080.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe190080 | /sys/devices/platform/fe190080.qos |
| fe190100.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe190100 | /sys/devices/platform/fe190100.qos |
| fe190200.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe190200 | /sys/devices/platform/fe190200.qos |
| fe190280.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe190280 | /sys/devices/platform/fe190280.qos |
| fe190300.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe190300 | /sys/devices/platform/fe190300.qos |
| fe190380.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe190380 | /sys/devices/platform/fe190380.qos |
| fe190400.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe190400 | /sys/devices/platform/fe190400.qos |
| fe198000.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe198000 | /sys/devices/platform/fe198000.qos |
| fe1a8000.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe1a8000 | /sys/devices/platform/fe1a8000.qos |
| fe1a8080.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe1a8080 | /sys/devices/platform/fe1a8080.qos |
| fe1a8100.qos | 无 driver 链接 | /sys/firmware/devicetree/base/qos@fe1a8100 | /sys/devices/platform/fe1a8100.qos |
| fe230000.dfi | /sys/bus/platform/drivers/rockchip-dfi | /sys/firmware/devicetree/base/dfi@fe230000 | /sys/devices/platform/fe230000.dfi |
| fe2a0000.ethernet | /sys/bus/platform/drivers/rk_gmac-dwmac | /sys/firmware/devicetree/base/ethernet@fe2a0000 | /sys/devices/platform/fe2a0000.ethernet |
| fe2b0000.dwmmc | /sys/bus/platform/drivers/dwmmc_rockchip | /sys/firmware/devicetree/base/dwmmc@fe2b0000 | /sys/devices/platform/fe2b0000.dwmmc |
| fe310000.sdhci | /sys/bus/platform/drivers/sdhci-dwcmshc | /sys/firmware/devicetree/base/sdhci@fe310000 | /sys/devices/platform/fe310000.sdhci |
| fe330000.nandc | 无 driver 链接 | /sys/firmware/devicetree/base/nandc@fe330000 | /sys/devices/platform/fe330000.nandc |
| fe388000.rng | /sys/bus/platform/drivers/rockchip-rng | /sys/firmware/devicetree/base/rng@fe388000 | /sys/devices/platform/fe388000.rng |
| fe38c000.otp | /sys/bus/platform/drivers/rockchip-otp | /sys/firmware/devicetree/base/otp@fe38c000 | /sys/devices/platform/fe38c000.otp |
| fe400000.i2s | /sys/bus/platform/drivers/rockchip-i2s-tdm | /sys/firmware/devicetree/base/i2s@fe400000 | /sys/devices/platform/fe400000.i2s |
| fe410000.i2s | /sys/bus/platform/drivers/rockchip-i2s-tdm | /sys/firmware/devicetree/base/i2s@fe410000 | /sys/devices/platform/fe410000.i2s |
| fe5a0000.i2c | /sys/bus/platform/drivers/rk3x-i2c | /sys/firmware/devicetree/base/i2c@fe5a0000 | /sys/devices/platform/fe5a0000.i2c |
| fe5b0000.i2c | /sys/bus/platform/drivers/rk3x-i2c | /sys/firmware/devicetree/base/i2c@fe5b0000 | /sys/devices/platform/fe5b0000.i2c |
| fe5c0000.i2c | /sys/bus/platform/drivers/rk3x-i2c | /sys/firmware/devicetree/base/i2c@fe5c0000 | /sys/devices/platform/fe5c0000.i2c |
| fe5d0000.i2c | /sys/bus/platform/drivers/rk3x-i2c | /sys/firmware/devicetree/base/i2c@fe5d0000 | /sys/devices/platform/fe5d0000.i2c |
| fe5e0000.i2c | /sys/bus/platform/drivers/rk3x-i2c | /sys/firmware/devicetree/base/i2c@fe5e0000 | /sys/devices/platform/fe5e0000.i2c |
| fe5f0000.timer | 无 driver 链接 | /sys/firmware/devicetree/base/timer@fe5f0000 | /sys/devices/platform/fe5f0000.timer |
| fe600000.watchdog | /sys/bus/platform/drivers/dw_wdt | /sys/firmware/devicetree/base/watchdog@fe600000 | /sys/devices/platform/fe600000.watchdog |
| fe640000.spi | /sys/bus/platform/drivers/rockchip-spi | /sys/firmware/devicetree/base/spi@fe640000 | /sys/devices/platform/fe640000.spi |
| fe670000.serial | /sys/bus/platform/drivers/dw-apb-uart | /sys/firmware/devicetree/base/serial@fe670000 | /sys/devices/platform/fe670000.serial |
| fe680000.serial | /sys/bus/platform/drivers/dw-apb-uart | /sys/firmware/devicetree/base/serial@fe680000 | /sys/devices/platform/fe680000.serial |
| fe6b0000.serial | /sys/bus/platform/drivers/dw-apb-uart | /sys/firmware/devicetree/base/serial@fe6b0000 | /sys/devices/platform/fe6b0000.serial |
| fe6c0000.serial | /sys/bus/platform/drivers/dw-apb-uart | /sys/firmware/devicetree/base/serial@fe6c0000 | /sys/devices/platform/fe6c0000.serial |
| fe6e0000.pwm | /sys/bus/platform/drivers/rockchip-pwm | /sys/firmware/devicetree/base/pwm@fe6e0000 | /sys/devices/platform/fe6e0000.pwm |
| fe6e0030.pwm | /sys/bus/platform/drivers/remotectl-pwm | /sys/firmware/devicetree/base/pwm@fe6e0030 | /sys/devices/platform/fe6e0030.pwm |
| fe710000.tsadc | /sys/bus/platform/drivers/rockchip-thermal | /sys/firmware/devicetree/base/tsadc@fe710000 | /sys/devices/platform/fe710000.tsadc |
| fe720000.saradc | /sys/bus/platform/drivers/rockchip-saradc | /sys/firmware/devicetree/base/saradc@fe720000 | /sys/devices/platform/fe720000.saradc |
| fe740000.gpio1 | /sys/bus/platform/drivers/rockchip-gpio | /sys/firmware/devicetree/base/pinctrl/gpio1@fe740000 | /sys/devices/platform/pinctrl/fe740000.gpio1 |
| fe750000.gpio2 | /sys/bus/platform/drivers/rockchip-gpio | /sys/firmware/devicetree/base/pinctrl/gpio2@fe750000 | /sys/devices/platform/pinctrl/fe750000.gpio2 |
| fe760000.gpio3 | /sys/bus/platform/drivers/rockchip-gpio | /sys/firmware/devicetree/base/pinctrl/gpio3@fe760000 | /sys/devices/platform/pinctrl/fe760000.gpio3 |
| fe770000.gpio4 | /sys/bus/platform/drivers/rockchip-gpio | /sys/firmware/devicetree/base/pinctrl/gpio4@fe770000 | /sys/devices/platform/pinctrl/fe770000.gpio4 |
| fe820000.phy | /sys/bus/platform/drivers/naneng-combphy | /sys/firmware/devicetree/base/phy@fe820000 | /sys/devices/platform/fe820000.phy |
| fe830000.phy | /sys/bus/platform/drivers/naneng-combphy | /sys/firmware/devicetree/base/phy@fe830000 | /sys/devices/platform/fe830000.phy |
| fe840000.phy | /sys/bus/platform/drivers/naneng-combphy | /sys/firmware/devicetree/base/phy@fe840000 | /sys/devices/platform/fe840000.phy |
| fe850000.phy | /sys/bus/platform/drivers/inno-dsidphy | /sys/firmware/devicetree/base/phy@fe850000 | /sys/devices/platform/fe850000.phy |
| fe870000.csi2-dphy-hw | /sys/bus/platform/drivers/rockchip-csi2-dphy-hw | /sys/firmware/devicetree/base/csi2-dphy-hw@fe870000 | /sys/devices/platform/fe870000.csi2-dphy-hw |
| fe8a0000.usb2-phy | /sys/bus/platform/drivers/rockchip-usb2phy | /sys/firmware/devicetree/base/usb2-phy@fe8a0000 | /sys/devices/platform/fe8a0000.usb2-phy |
| fe8b0000.usb2-phy | /sys/bus/platform/drivers/rockchip-usb2phy | /sys/firmware/devicetree/base/usb2-phy@fe8b0000 | /sys/devices/platform/fe8b0000.usb2-phy |
| fe8c0000.phy | /sys/bus/platform/drivers/rockchip-snps-pcie3-phy | /sys/firmware/devicetree/base/phy@fe8c0000 | /sys/devices/platform/fe8c0000.phy |
| fiq-debugger | /sys/bus/platform/drivers/rk-fiq-debugger | /sys/firmware/devicetree/base/fiq-debugger | /sys/devices/platform/fiq-debugger |
| fiq_debugger.0 | /sys/bus/platform/drivers/fiq_debugger |  | /sys/devices/platform/fiq_debugger.0 |
| firmware:scmi | /sys/bus/platform/drivers/arm-scmi | /sys/firmware/devicetree/base/firmware/scmi | /sys/devices/platform/firmware:scmi |
| firmware:sdei | 无 driver 链接 | /sys/firmware/devicetree/base/firmware/sdei | /sys/devices/platform/firmware:sdei |
| gpio-regulator | /sys/bus/platform/drivers/reg-fixed-voltage | /sys/firmware/devicetree/base/gpio-regulator | /sys/devices/platform/gpio-regulator |
| hdmi-audio-codec.3.auto | /sys/bus/platform/drivers/hdmi-audio-codec |  | /sys/devices/platform/fe0a0000.hdmi/hdmi-audio-codec.3.auto |
| hdmi-sound | /sys/bus/platform/drivers/asoc-simple-card | /sys/firmware/devicetree/base/hdmi-sound | /sys/devices/platform/hdmi-sound |
| leds | /sys/bus/platform/drivers/leds-gpio | /sys/firmware/devicetree/base/leds | /sys/devices/platform/leds |
| minipcie-regulator | /sys/bus/platform/drivers/reg-fixed-voltage | /sys/firmware/devicetree/base/minipcie-regulator | /sys/devices/platform/minipcie-regulator |
| mpp-srv | /sys/bus/platform/drivers/mpp_service | /sys/firmware/devicetree/base/mpp-srv | /sys/devices/platform/mpp-srv |
| mtd_vendor_storage | 无 driver 链接 |  | /sys/devices/platform/mtd_vendor_storage |
| pcie3-regulator | /sys/bus/platform/drivers/reg-fixed-voltage | /sys/firmware/devicetree/base/pcie3-regulator | /sys/devices/platform/pcie3-regulator |
| pcie30-avdd0v9 | /sys/bus/platform/drivers/reg-fixed-voltage | /sys/firmware/devicetree/base/pcie30-avdd0v9 | /sys/devices/platform/pcie30-avdd0v9 |
| pcie30-avdd1v8 | /sys/bus/platform/drivers/reg-fixed-voltage | /sys/firmware/devicetree/base/pcie30-avdd1v8 | /sys/devices/platform/pcie30-avdd1v8 |
| pinctrl | /sys/bus/platform/drivers/rockchip-pinctrl | /sys/firmware/devicetree/base/pinctrl | /sys/devices/platform/pinctrl |
| psci | /sys/bus/platform/drivers/psci-cpuidle-domain | /sys/firmware/devicetree/base/psci | /sys/devices/platform/psci |
| psci-cpuidle | /sys/bus/platform/drivers/psci-cpuidle |  | /sys/devices/platform/psci-cpuidle |
| reg-dummy | /sys/bus/platform/drivers/reg-dummy |  | /sys/devices/platform/reg-dummy |
| regulatory.0 | 无 driver 链接 |  | /sys/devices/platform/regulatory.0 |
| rk805-pinctrl | /sys/bus/platform/drivers/rk805-pinctrl |  | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/rk805-pinctrl |
| rk805-pwrkey | /sys/bus/platform/drivers/rk805-pwrkey |  | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/rk805-pwrkey |
| rk808-clkout | /sys/bus/platform/drivers/rk808-clkout |  | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/rk808-clkout |
| rk808-regulator | /sys/bus/platform/drivers/rk808-regulator |  | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/rk808-regulator |
| rk808-rtc | /sys/bus/platform/drivers/rk808-rtc |  | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/rk808-rtc |
| rk809-sound | /sys/bus/platform/drivers/rk-multicodecs | /sys/firmware/devicetree/base/rk809-sound | /sys/devices/platform/rk809-sound |
| rk817-battery | 无 driver 链接 |  | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/rk817-battery |
| rk817-charger | 无 driver 链接 |  | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/rk817-charger |
| rk817-codec | /sys/bus/platform/drivers/rk817-codec | /sys/firmware/devicetree/base/i2c@fdd40000/pmic@20/codec | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/rk817-codec |
| rkisp-vir0 | /sys/bus/platform/drivers/rkisp | /sys/firmware/devicetree/base/rkisp-vir0 | /sys/devices/platform/rkisp-vir0 |
| rknpu_dev.6.auto | 无 driver 链接 |  | /sys/devices/platform/rknpu_dev.6.auto |
| rockchip-suspend | /sys/bus/platform/drivers/rockchip-pm | /sys/firmware/devicetree/base/rockchip-suspend | /sys/devices/platform/rockchip-suspend |
| rockchip-system-monitor | /sys/bus/platform/drivers/rockchip-system-monitor | /sys/firmware/devicetree/base/rockchip-system-monitor | /sys/devices/platform/rockchip-system-monitor |
| sdio-pwrseq | /sys/bus/platform/drivers/pwrseq_simple | /sys/firmware/devicetree/base/sdio-pwrseq | /sys/devices/platform/sdio-pwrseq |
| serial8250 | /sys/bus/platform/drivers/serial8250 |  | /sys/devices/platform/serial8250 |
| skw_ucom.12.auto | /sys/bus/platform/drivers/skw_ucom |  | /sys/devices/platform/fe000000.dwmmc/mmc_host/mmc3/mmc3:0001/mmc3:0001:1/skw_ucom.12.auto |
| skw_ucom.7.auto | /sys/bus/platform/drivers/skw_ucom |  | /sys/devices/platform/fe000000.dwmmc/mmc_host/mmc3/mmc3:0001/mmc3:0001:1/skw_ucom.7.auto |
| skw_ucom.8.auto | /sys/bus/platform/drivers/skw_ucom |  | /sys/devices/platform/fe000000.dwmmc/mmc_host/mmc3/mmc3:0001/mmc3:0001:1/skw_ucom.8.auto |
| skw_ucom.9.auto | /sys/bus/platform/drivers/skw_ucom |  | /sys/devices/platform/fe000000.dwmmc/mmc_host/mmc3/mmc3:0001/mmc3:0001:1/skw_ucom.9.auto |
| snd-soc-dummy | /sys/bus/platform/drivers/snd-soc-dummy |  | /sys/devices/platform/snd-soc-dummy |
| sv6160lite.0 | /sys/bus/platform/drivers/sv6160lite |  | /sys/devices/platform/sv6160lite.0 |
| sv6621s_wireless1.11.auto | /sys/bus/platform/drivers/sv6621s_wireless1 |  | /sys/devices/platform/fe000000.dwmmc/mmc_host/mmc3/mmc3:0001/mmc3:0001:1/sv6621s_wireless1.11.auto |
| timer | 无 driver 链接 | /sys/firmware/devicetree/base/timer | /sys/devices/platform/timer |
| usbdrd | /sys/bus/platform/drivers/dwc3-of-simple | /sys/firmware/devicetree/base/usbdrd | /sys/devices/platform/usbdrd |
| usbhost | /sys/bus/platform/drivers/dwc3-of-simple | /sys/firmware/devicetree/base/usbhost | /sys/devices/platform/usbhost |
| vcc1v8-cam | /sys/bus/platform/drivers/reg-fixed-voltage | /sys/firmware/devicetree/base/vcc1v8-cam | /sys/devices/platform/vcc1v8-cam |
| vcc2v5-ddr | /sys/bus/platform/drivers/reg-fixed-voltage | /sys/firmware/devicetree/base/vcc2v5-ddr | /sys/devices/platform/vcc2v5-ddr |
| vcc3v3-bu | /sys/bus/platform/drivers/reg-fixed-voltage | /sys/firmware/devicetree/base/vcc3v3-bu | /sys/devices/platform/vcc3v3-bu |
| vcc3v3-lcd0-n | /sys/bus/platform/drivers/reg-fixed-voltage | /sys/firmware/devicetree/base/vcc3v3-lcd0-n | /sys/devices/platform/vcc3v3-lcd0-n |
| vcc3v3-mipi-con | /sys/bus/platform/drivers/reg-fixed-voltage | /sys/firmware/devicetree/base/vcc3v3-mipi-con | /sys/devices/platform/vcc3v3-mipi-con |
| vcc3v3-sys | /sys/bus/platform/drivers/reg-fixed-voltage | /sys/firmware/devicetree/base/vcc3v3-sys | /sys/devices/platform/vcc3v3-sys |
| vcc5v0-host-regulator | /sys/bus/platform/drivers/reg-fixed-voltage | /sys/firmware/devicetree/base/vcc5v0-host-regulator | /sys/devices/platform/vcc5v0-host-regulator |
| vcc5v0-otg-regulator | /sys/bus/platform/drivers/reg-fixed-voltage | /sys/firmware/devicetree/base/vcc5v0-otg-regulator | /sys/devices/platform/vcc5v0-otg-regulator |
| vcc5v0-sys | /sys/bus/platform/drivers/reg-fixed-voltage | /sys/firmware/devicetree/base/vcc5v0-sys | /sys/devices/platform/vcc5v0-sys |
| vcc5v0-usb | /sys/bus/platform/drivers/reg-fixed-voltage | /sys/firmware/devicetree/base/vcc5v0-usb | /sys/devices/platform/vcc5v0-usb |
| wireless-bluetooth | /sys/bus/platform/drivers/rfkill_bt | /sys/firmware/devicetree/base/wireless-bluetooth | /sys/devices/platform/wireless-bluetooth |
| wireless-wlan | /sys/bus/platform/drivers/wlan-platdata | /sys/firmware/devicetree/base/wireless-wlan | /sys/devices/platform/wireless-wlan |
| xhci-hcd.0.auto | /sys/bus/platform/drivers/xhci-hcd |  | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto |

### scmi_protocol (1)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| scmi_dev.1 | /sys/bus/scmi_protocol/drivers/scmi-clocks | /sys/firmware/devicetree/base/firmware/scmi/protocol@14 | /sys/devices/platform/firmware:scmi/scmi_dev.1 |

### scsi (1)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| host0 | 无 driver 链接 |  | /sys/devices/platform/fc000000.sata/ata1/host0 |

### sdio (1)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| mmc3:0001:1 | /sys/bus/sdio/drivers/skw_sdio |  | /sys/devices/platform/fe000000.dwmmc/mmc_host/mmc3/mmc3:0001/mmc3:0001:1 |

### spi (1)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| spi3.0 | /sys/bus/spi/drivers/spidev | /sys/firmware/devicetree/base/spi@fe640000/spi_test@0 | /sys/devices/platform/fe640000.spi/spi_master/spi3/spi3.0 |

### usb (16)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| 1-0:1.0 | /sys/bus/usb/drivers/hub | /sys/firmware/devicetree/base/usb@fd800000 | /sys/devices/platform/fd800000.usb/usb1/1-0:1.0 |
| 2-0:1.0 | /sys/bus/usb/drivers/hub | /sys/firmware/devicetree/base/usb@fd880000 | /sys/devices/platform/fd880000.usb/usb2/2-0:1.0 |
| 3-0:1.0 | /sys/bus/usb/drivers/hub | /sys/firmware/devicetree/base/usb@fd840000 | /sys/devices/platform/fd840000.usb/usb3/3-0:1.0 |
| 4-0:1.0 | /sys/bus/usb/drivers/hub | /sys/firmware/devicetree/base/usb@fd8c0000 | /sys/devices/platform/fd8c0000.usb/usb4/4-0:1.0 |
| 5-0:1.0 | /sys/bus/usb/drivers/hub | /sys/firmware/devicetree/base/usbhost/dwc3@fd000000 | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-0:1.0 |
| 5-1 | /sys/bus/usb/drivers/usb |  | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1 |
| 5-1:1.0 | /sys/bus/usb/drivers/usbhid |  | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.0 |
| 5-1:1.1 | /sys/bus/usb/drivers/usbhid |  | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.1 |
| 5-1:1.2 | /sys/bus/usb/drivers/usbhid |  | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.2 |
| 6-0:1.0 | /sys/bus/usb/drivers/hub | /sys/firmware/devicetree/base/usbhost/dwc3@fd000000 | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb6/6-0:1.0 |
| usb1 | /sys/bus/usb/drivers/usb | /sys/firmware/devicetree/base/usb@fd800000 | /sys/devices/platform/fd800000.usb/usb1 |
| usb2 | /sys/bus/usb/drivers/usb | /sys/firmware/devicetree/base/usb@fd880000 | /sys/devices/platform/fd880000.usb/usb2 |
| usb3 | /sys/bus/usb/drivers/usb | /sys/firmware/devicetree/base/usb@fd840000 | /sys/devices/platform/fd840000.usb/usb3 |
| usb4 | /sys/bus/usb/drivers/usb | /sys/firmware/devicetree/base/usb@fd8c0000 | /sys/devices/platform/fd8c0000.usb/usb4 |
| usb5 | /sys/bus/usb/drivers/usb | /sys/firmware/devicetree/base/usbhost/dwc3@fd000000 | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5 |
| usb6 | /sys/bus/usb/drivers/usb | /sys/firmware/devicetree/base/usbhost/dwc3@fd000000 | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb6 |

### workqueue (9)

| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |
|---|---|---|---|
| blkcg_punt_bio | 无 driver 链接 |  | /sys/devices/virtual/workqueue/blkcg_punt_bio |
| firmware:scmi | 无 driver 链接 |  | /sys/devices/virtual/workqueue/firmware:scmi |
| nvme-delete-wq | 无 driver 链接 |  | /sys/devices/virtual/workqueue/nvme-delete-wq |
| nvme-reset-wq | 无 driver 链接 |  | /sys/devices/virtual/workqueue/nvme-reset-wq |
| nvme-wq | 无 driver 链接 |  | /sys/devices/virtual/workqueue/nvme-wq |
| scsi_tmf_0 | 无 driver 链接 |  | /sys/devices/virtual/workqueue/scsi_tmf_0 |
| skw_txwq.1 | 无 driver 链接 |  | /sys/devices/virtual/workqueue/skw_txwq.1 |
| skwifid_dywq.1 | 无 driver 链接 |  | /sys/devices/virtual/workqueue/skwifid_dywq.1 |
| writeback | 无 driver 链接 |  | /sys/devices/virtual/workqueue/writeback |

## 全部 sysfs class 设备

### android_usb (1)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| android0 | android0 | /sys/devices/virtual/android_usb/android0 |

### ata_device (1)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| dev1.0 | dev1.0 | /sys/devices/platform/fc000000.sata/ata1/link1/dev1.0/ata_device/dev1.0 |

### ata_link (1)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| link1 | link1 | /sys/devices/platform/fc000000.sata/ata1/link1/ata_link/link1 |

### ata_port (1)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| ata1 | ata1 | /sys/devices/platform/fc000000.sata/ata1/ata_port/ata1 |

### backlight (1)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| backlight | backlight | /sys/devices/platform/backlight-dsi0/backlight/backlight |

### bdi (14)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| 179:0 | 179:0 | /sys/devices/virtual/bdi/179:0 |
| 179:32 | 179:32 | /sys/devices/virtual/bdi/179:32 |
| 179:64 | 179:64 | /sys/devices/virtual/bdi/179:64 |
| 1:0 | 1:0 | /sys/devices/virtual/bdi/1:0 |
| 254:0 | 254:0 | /sys/devices/virtual/bdi/254:0 |
| 7:0 | 7:0 | /sys/devices/virtual/bdi/7:0 |
| 7:1 | 7:1 | /sys/devices/virtual/bdi/7:1 |
| 7:2 | 7:2 | /sys/devices/virtual/bdi/7:2 |
| 7:3 | 7:3 | /sys/devices/virtual/bdi/7:3 |
| 7:4 | 7:4 | /sys/devices/virtual/bdi/7:4 |
| 7:5 | 7:5 | /sys/devices/virtual/bdi/7:5 |
| 7:6 | 7:6 | /sys/devices/virtual/bdi/7:6 |
| 7:7 | 7:7 | /sys/devices/virtual/bdi/7:7 |
| mtd-0 | mtd-0 | /sys/devices/virtual/bdi/mtd-0 |

### block (19)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| loop0 | loop0 | /sys/devices/virtual/block/loop0 |
| loop1 | loop1 | /sys/devices/virtual/block/loop1 |
| loop2 | loop2 | /sys/devices/virtual/block/loop2 |
| loop3 | loop3 | /sys/devices/virtual/block/loop3 |
| loop4 | loop4 | /sys/devices/virtual/block/loop4 |
| loop5 | loop5 | /sys/devices/virtual/block/loop5 |
| loop6 | loop6 | /sys/devices/virtual/block/loop6 |
| loop7 | loop7 | /sys/devices/virtual/block/loop7 |
| mmcblk0 | mmcblk0 | /sys/devices/platform/fe310000.sdhci/mmc_host/mmc0/mmc0:0001/block/mmcblk0 |
| mmcblk0boot0 | mmcblk0boot0 | /sys/devices/platform/fe310000.sdhci/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0boot0 |
| mmcblk0boot1 | mmcblk0boot1 | /sys/devices/platform/fe310000.sdhci/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0boot1 |
| mmcblk0p1 | mmcblk0p1 | /sys/devices/platform/fe310000.sdhci/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0p1 |
| mmcblk0p2 | mmcblk0p2 | /sys/devices/platform/fe310000.sdhci/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0p2 |
| mmcblk0p3 | mmcblk0p3 | /sys/devices/platform/fe310000.sdhci/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0p3 |
| mmcblk0p4 | mmcblk0p4 | /sys/devices/platform/fe310000.sdhci/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0p4 |
| mmcblk0p5 | mmcblk0p5 | /sys/devices/platform/fe310000.sdhci/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0p5 |
| mmcblk0p6 | mmcblk0p6 | /sys/devices/platform/fe310000.sdhci/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0p6 |
| ram0 | ram0 | /sys/devices/virtual/block/ram0 |
| zram0 | zram0 | /sys/devices/virtual/block/zram0 |

### bluetooth (1)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| hci0 | hci0 | /sys/devices/platform/fe000000.dwmmc/mmc_host/mmc3/mmc3:0001/mmc3:0001:1/btseekwave.10.auto/bluetooth/hci0 |

### btcom (5)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| ATC | ATC | /sys/devices/virtual/btcom/ATC |
| BTBOOT | BTBOOT | /sys/devices/virtual/btcom/BTBOOT |
| LOG | LOG | /sys/devices/virtual/btcom/LOG |
| LOOPCHECK | LOOPCHECK | /sys/devices/virtual/btcom/LOOPCHECK |
| SKWDUMP | SKWDUMP | /sys/devices/virtual/btcom/SKWDUMP |

### devcoredump (1)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| disabled | disabled | /sys/class/devcoredump/disabled |

### devfreq (5)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| dmc | dmc<br> | /sys/devices/platform/dmc/devfreq/dmc |
| fde40000.npu | fde40000.npu<br> | /sys/devices/platform/fde40000.npu/devfreq/fde40000.npu |
| fde60000.gpu | fde60000.gpu<br> | /sys/devices/platform/fde60000.gpu/devfreq/fde60000.gpu |
| fdf40000.rkvenc | fdf40000.rkvenc<br> | /sys/devices/platform/fdf40000.rkvenc/devfreq/fdf40000.rkvenc |
| fdf80200.rkvdec | fdf80200.rkvdec<br> | /sys/devices/platform/fdf80200.rkvdec/devfreq/fdf80200.rkvdec |

### devfreq-event (6)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| event0 | dfi<br> | /sys/devices/platform/fe230000.dfi/devfreq-event/event0 |
| event1 | nocp-cpu<br> | /sys/devices/platform/fe102000.nocp-cpu/devfreq-event/event1 |
| event2 | nocp-gpu-vpu-rga-venc<br> | /sys/devices/platform/fe102400.nocp-gpu-vpu-rga-venc/devfreq-event/event2 |
| event3 | nocp-vdec<br> | /sys/devices/platform/fe102800.nocp-vdec/devfreq-event/event3 |
| event4 | nocp-vi-usb-peri-pipe<br> | /sys/devices/platform/fe102c00.nocp-vi-usb-peri-pipe/devfreq-event/event4 |
| event5 | nocp-vo<br> | /sys/devices/platform/fe103000.nocp-vo/devfreq-event/event5 |

### devlink (173)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| amba:fe530000.dmac--platform:fdd50000.serial | amba:fe530000.dmac--platform:fdd50000.serial | /sys/devices/virtual/devlink/amba:fe530000.dmac--platform:fdd50000.serial |
| amba:fe530000.dmac--platform:fe640000.spi | amba:fe530000.dmac--platform:fe640000.spi | /sys/devices/virtual/devlink/amba:fe530000.dmac--platform:fe640000.spi |
| amba:fe530000.dmac--platform:fe670000.serial | amba:fe530000.dmac--platform:fe670000.serial | /sys/devices/virtual/devlink/amba:fe530000.dmac--platform:fe670000.serial |
| amba:fe530000.dmac--platform:fe680000.serial | amba:fe530000.dmac--platform:fe680000.serial | /sys/devices/virtual/devlink/amba:fe530000.dmac--platform:fe680000.serial |
| amba:fe530000.dmac--platform:fe6b0000.serial | amba:fe530000.dmac--platform:fe6b0000.serial | /sys/devices/virtual/devlink/amba:fe530000.dmac--platform:fe6b0000.serial |
| amba:fe530000.dmac--platform:fe6c0000.serial | amba:fe530000.dmac--platform:fe6c0000.serial | /sys/devices/virtual/devlink/amba:fe530000.dmac--platform:fe6c0000.serial |
| amba:fe550000.dmac--platform:fe400000.i2s | amba:fe550000.dmac--platform:fe400000.i2s | /sys/devices/virtual/devlink/amba:fe550000.dmac--platform:fe400000.i2s |
| amba:fe550000.dmac--platform:fe410000.i2s | amba:fe550000.dmac--platform:fe410000.i2s | /sys/devices/virtual/devlink/amba:fe550000.dmac--platform:fe410000.i2s |
| i2c:0-001c--platform:bus-npu | i2c:0-001c--platform:bus-npu | /sys/devices/virtual/devlink/i2c:0-001c--platform:bus-npu |
| i2c:0-0020--platform:bus-npu | i2c:0-0020--platform:bus-npu | /sys/devices/virtual/devlink/i2c:0-0020--platform:bus-npu |
| i2c:0-0020--platform:dmc | i2c:0-0020--platform:dmc | /sys/devices/virtual/devlink/i2c:0-0020--platform:dmc |
| i2c:0-0020--platform:fdc20000.syscon:io-domains | i2c:0-0020--platform:fdc20000.syscon:io-domains | /sys/devices/virtual/devlink/i2c:0-0020--platform:fdc20000.syscon:io-domains |
| i2c:0-0020--platform:fde40000.npu | i2c:0-0020--platform:fde40000.npu | /sys/devices/virtual/devlink/i2c:0-0020--platform:fde40000.npu |
| i2c:0-0020--platform:fde60000.gpu | i2c:0-0020--platform:fde60000.gpu | /sys/devices/virtual/devlink/i2c:0-0020--platform:fde60000.gpu |
| i2c:0-0020--platform:fdf40000.rkvenc | i2c:0-0020--platform:fdf40000.rkvenc | /sys/devices/virtual/devlink/i2c:0-0020--platform:fdf40000.rkvenc |
| i2c:0-0020--platform:fdf80200.rkvdec | i2c:0-0020--platform:fdf80200.rkvdec | /sys/devices/virtual/devlink/i2c:0-0020--platform:fdf80200.rkvdec |
| i2c:0-0020--platform:fe2b0000.dwmmc | i2c:0-0020--platform:fe2b0000.dwmmc | /sys/devices/virtual/devlink/i2c:0-0020--platform:fe2b0000.dwmmc |
| i2c:0-0020--platform:fe720000.saradc | i2c:0-0020--platform:fe720000.saradc | /sys/devices/virtual/devlink/i2c:0-0020--platform:fe720000.saradc |
| i2c:0-0020--platform:sdio-pwrseq | i2c:0-0020--platform:sdio-pwrseq | /sys/devices/virtual/devlink/i2c:0-0020--platform:sdio-pwrseq |
| i2c:0-0020--platform:vcc3v3-mipi-con | i2c:0-0020--platform:vcc3v3-mipi-con | /sys/devices/virtual/devlink/i2c:0-0020--platform:vcc3v3-mipi-con |
| i2c:0-0020--platform:wireless-bluetooth | i2c:0-0020--platform:wireless-bluetooth | /sys/devices/virtual/devlink/i2c:0-0020--platform:wireless-bluetooth |
| phy:phy-fe820000.phy.5--platform:fc000000.sata | phy:phy-fe820000.phy.5--platform:fc000000.sata | /sys/devices/virtual/devlink/phy:phy-fe820000.phy.5--platform:fc000000.sata |
| phy:phy-fe830000.phy.6--platform:fd000000.dwc3 | phy:phy-fe830000.phy.6--platform:fd000000.dwc3 | /sys/devices/virtual/devlink/phy:phy-fe830000.phy.6--platform:fd000000.dwc3 |
| phy:phy-fe850000.phy.0--platform:fe060000.dsi | phy:phy-fe850000.phy.0--platform:fe060000.dsi | /sys/devices/virtual/devlink/phy:phy-fe850000.phy.0--platform:fe060000.dsi |
| phy:phy-fe8a0000.usb2-phy.1--platform:fd000000.dwc3 | phy:phy-fe8a0000.usb2-phy.1--platform:fd000000.dwc3 | /sys/devices/virtual/devlink/phy:phy-fe8a0000.usb2-phy.1--platform:fd000000.dwc3 |
| phy:phy-fe8a0000.usb2-phy.2--platform:fcc00000.dwc3 | phy:phy-fe8a0000.usb2-phy.2--platform:fcc00000.dwc3 | /sys/devices/virtual/devlink/phy:phy-fe8a0000.usb2-phy.2--platform:fcc00000.dwc3 |
| phy:phy-fe8b0000.usb2-phy.3--platform:fd880000.usb | phy:phy-fe8b0000.usb2-phy.3--platform:fd880000.usb | /sys/devices/virtual/devlink/phy:phy-fe8b0000.usb2-phy.3--platform:fd880000.usb |
| phy:phy-fe8b0000.usb2-phy.3--platform:fd8c0000.usb | phy:phy-fe8b0000.usb2-phy.3--platform:fd8c0000.usb | /sys/devices/virtual/devlink/phy:phy-fe8b0000.usb2-phy.3--platform:fd8c0000.usb |
| phy:phy-fe8b0000.usb2-phy.4--platform:fd800000.usb | phy:phy-fe8b0000.usb2-phy.4--platform:fd800000.usb | /sys/devices/virtual/devlink/phy:phy-fe8b0000.usb2-phy.4--platform:fd800000.usb |
| phy:phy-fe8b0000.usb2-phy.4--platform:fd840000.usb | phy:phy-fe8b0000.usb2-phy.4--platform:fd840000.usb | /sys/devices/virtual/devlink/phy:phy-fe8b0000.usb2-phy.4--platform:fd840000.usb |
| platform:dc-12v--platform:gpio-regulator | platform:dc-12v--platform:gpio-regulator | /sys/devices/virtual/devlink/platform:dc-12v--platform:gpio-regulator |
| platform:dc-12v--platform:vcc3v3-sys | platform:dc-12v--platform:vcc3v3-sys | /sys/devices/virtual/devlink/platform:dc-12v--platform:vcc3v3-sys |
| platform:dc-12v--platform:vcc5v0-sys | platform:dc-12v--platform:vcc5v0-sys | /sys/devices/virtual/devlink/platform:dc-12v--platform:vcc5v0-sys |
| platform:dc-12v--platform:vcc5v0-usb | platform:dc-12v--platform:vcc5v0-usb | /sys/devices/virtual/devlink/platform:dc-12v--platform:vcc5v0-usb |
| platform:fdd60000.gpio0--i2c:0-0020 | platform:fdd60000.gpio0--i2c:0-0020 | /sys/devices/virtual/devlink/platform:fdd60000.gpio0--i2c:0-0020 |
| platform:fdd60000.gpio0--i2c:5-0051 | platform:fdd60000.gpio0--i2c:5-0051 | /sys/devices/virtual/devlink/platform:fdd60000.gpio0--i2c:5-0051 |
| platform:fdd60000.gpio0--platform:gpio-regulator | platform:fdd60000.gpio0--platform:gpio-regulator | /sys/devices/virtual/devlink/platform:fdd60000.gpio0--platform:gpio-regulator |
| platform:fdd60000.gpio0--platform:pcie3-regulator | platform:fdd60000.gpio0--platform:pcie3-regulator | /sys/devices/virtual/devlink/platform:fdd60000.gpio0--platform:pcie3-regulator |
| platform:fdd60000.gpio0--platform:vcc3v3-lcd0-n | platform:fdd60000.gpio0--platform:vcc3v3-lcd0-n | /sys/devices/virtual/devlink/platform:fdd60000.gpio0--platform:vcc3v3-lcd0-n |
| platform:fdd60000.gpio0--platform:vcc5v0-host-regulator | platform:fdd60000.gpio0--platform:vcc5v0-host-regulator | /sys/devices/virtual/devlink/platform:fdd60000.gpio0--platform:vcc5v0-host-regulator |
| platform:fdd60000.gpio0--platform:vcc5v0-otg-regulator | platform:fdd60000.gpio0--platform:vcc5v0-otg-regulator | /sys/devices/virtual/devlink/platform:fdd60000.gpio0--platform:vcc5v0-otg-regulator |
| platform:fdd90000.power-management:power-controller--platform:3c0000000.pcie | platform:fdd90000.power-management:power-controller--platform:3c0000000.pcie | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:3c0000000.pcie |
| platform:fdd90000.power-management:power-controller--platform:3c0800000.pcie | platform:fdd90000.power-management:power-controller--platform:3c0800000.pcie | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:3c0800000.pcie |
| platform:fdd90000.power-management:power-controller--platform:fc000000.sata | platform:fdd90000.power-management:power-controller--platform:fc000000.sata | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fc000000.sata |
| platform:fdd90000.power-management:power-controller--platform:fcc00000.dwc3 | platform:fdd90000.power-management:power-controller--platform:fcc00000.dwc3 | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fcc00000.dwc3 |
| platform:fdd90000.power-management:power-controller--platform:fd000000.dwc3 | platform:fdd90000.power-management:power-controller--platform:fd000000.dwc3 | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fd000000.dwc3 |
| platform:fdd90000.power-management:power-controller--platform:fde40000.npu | platform:fdd90000.power-management:power-controller--platform:fde40000.npu | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fde40000.npu |
| platform:fdd90000.power-management:power-controller--platform:fde4b000.iommu | platform:fdd90000.power-management:power-controller--platform:fde4b000.iommu | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fde4b000.iommu |
| platform:fdd90000.power-management:power-controller--platform:fde60000.gpu | platform:fdd90000.power-management:power-controller--platform:fde60000.gpu | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fde60000.gpu |
| platform:fdd90000.power-management:power-controller--platform:fdea0400.vdpu | platform:fdd90000.power-management:power-controller--platform:fdea0400.vdpu | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fdea0400.vdpu |
| platform:fdd90000.power-management:power-controller--platform:fdea0800.iommu | platform:fdd90000.power-management:power-controller--platform:fdea0800.iommu | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fdea0800.iommu |
| platform:fdd90000.power-management:power-controller--platform:fdeb0000.rk_rga | platform:fdd90000.power-management:power-controller--platform:fdeb0000.rk_rga | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fdeb0000.rk_rga |
| platform:fdd90000.power-management:power-controller--platform:fded0000.jpegd | platform:fdd90000.power-management:power-controller--platform:fded0000.jpegd | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fded0000.jpegd |
| platform:fdd90000.power-management:power-controller--platform:fded0480.iommu | platform:fdd90000.power-management:power-controller--platform:fded0480.iommu | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fded0480.iommu |
| platform:fdd90000.power-management:power-controller--platform:fdee0000.vepu | platform:fdd90000.power-management:power-controller--platform:fdee0000.vepu | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fdee0000.vepu |
| platform:fdd90000.power-management:power-controller--platform:fdee0800.iommu | platform:fdd90000.power-management:power-controller--platform:fdee0800.iommu | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fdee0800.iommu |
| platform:fdd90000.power-management:power-controller--platform:fdef0000.iep | platform:fdd90000.power-management:power-controller--platform:fdef0000.iep | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fdef0000.iep |
| platform:fdd90000.power-management:power-controller--platform:fdef0800.iommu | platform:fdd90000.power-management:power-controller--platform:fdef0800.iommu | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fdef0800.iommu |
| platform:fdd90000.power-management:power-controller--platform:fdf40000.rkvenc | platform:fdd90000.power-management:power-controller--platform:fdf40000.rkvenc | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fdf40000.rkvenc |
| platform:fdd90000.power-management:power-controller--platform:fdf40f00.iommu | platform:fdd90000.power-management:power-controller--platform:fdf40f00.iommu | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fdf40f00.iommu |
| platform:fdd90000.power-management:power-controller--platform:fdf80200.rkvdec | platform:fdd90000.power-management:power-controller--platform:fdf80200.rkvdec | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fdf80200.rkvdec |
| platform:fdd90000.power-management:power-controller--platform:fdf80800.iommu | platform:fdd90000.power-management:power-controller--platform:fdf80800.iommu | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fdf80800.iommu |
| platform:fdd90000.power-management:power-controller--platform:fdff0000.rkisp | platform:fdd90000.power-management:power-controller--platform:fdff0000.rkisp | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fdff0000.rkisp |
| platform:fdd90000.power-management:power-controller--platform:fdff1a00.iommu | platform:fdd90000.power-management:power-controller--platform:fdff1a00.iommu | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fdff1a00.iommu |
| platform:fdd90000.power-management:power-controller--platform:fe040000.vop | platform:fdd90000.power-management:power-controller--platform:fe040000.vop | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fe040000.vop |
| platform:fdd90000.power-management:power-controller--platform:fe060000.dsi | platform:fdd90000.power-management:power-controller--platform:fe060000.dsi | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fe060000.dsi |
| platform:fdd90000.power-management:power-controller--platform:fe0a0000.hdmi | platform:fdd90000.power-management:power-controller--platform:fe0a0000.hdmi | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fe0a0000.hdmi |
| platform:fdd90000.power-management:power-controller--platform:fe850000.phy | platform:fdd90000.power-management:power-controller--platform:fe850000.phy | /sys/devices/virtual/devlink/platform:fdd90000.power-management:power-controller--platform:fe850000.phy |
| platform:fde4b000.iommu--platform:fde40000.npu | platform:fde4b000.iommu--platform:fde40000.npu | /sys/devices/virtual/devlink/platform:fde4b000.iommu--platform:fde40000.npu |
| platform:fdea0800.iommu--platform:fdea0400.vdpu | platform:fdea0800.iommu--platform:fdea0400.vdpu | /sys/devices/virtual/devlink/platform:fdea0800.iommu--platform:fdea0400.vdpu |
| platform:fded0480.iommu--platform:fded0000.jpegd | platform:fded0480.iommu--platform:fded0000.jpegd | /sys/devices/virtual/devlink/platform:fded0480.iommu--platform:fded0000.jpegd |
| platform:fdee0800.iommu--platform:fdee0000.vepu | platform:fdee0800.iommu--platform:fdee0000.vepu | /sys/devices/virtual/devlink/platform:fdee0800.iommu--platform:fdee0000.vepu |
| platform:fdef0800.iommu--platform:fdef0000.iep | platform:fdef0800.iommu--platform:fdef0000.iep | /sys/devices/virtual/devlink/platform:fdef0800.iommu--platform:fdef0000.iep |
| platform:fdf40f00.iommu--platform:fdf40000.rkvenc | platform:fdf40f00.iommu--platform:fdf40000.rkvenc | /sys/devices/virtual/devlink/platform:fdf40f00.iommu--platform:fdf40000.rkvenc |
| platform:fdf80800.iommu--platform:fdf80200.rkvdec | platform:fdf80800.iommu--platform:fdf80200.rkvdec | /sys/devices/virtual/devlink/platform:fdf80800.iommu--platform:fdf80200.rkvdec |
| platform:fdff1a00.iommu--platform:fdff0000.rkisp | platform:fdff1a00.iommu--platform:fdff0000.rkisp | /sys/devices/virtual/devlink/platform:fdff1a00.iommu--platform:fdff0000.rkisp |
| platform:fe040000.vop--platform:display-subsystem | platform:fe040000.vop--platform:display-subsystem | /sys/devices/virtual/devlink/platform:fe040000.vop--platform:display-subsystem |
| platform:fe043e00.iommu--platform:fe040000.vop | platform:fe043e00.iommu--platform:fe040000.vop | /sys/devices/virtual/devlink/platform:fe043e00.iommu--platform:fe040000.vop |
| platform:fe060000.dsi--platform:display-subsystem | platform:fe060000.dsi--platform:display-subsystem | /sys/devices/virtual/devlink/platform:fe060000.dsi--platform:display-subsystem |
| platform:fe0a0000.hdmi--platform:display-subsystem | platform:fe0a0000.hdmi--platform:display-subsystem | /sys/devices/virtual/devlink/platform:fe0a0000.hdmi--platform:display-subsystem |
| platform:fe38c000.otp--platform:cpuinfo | platform:fe38c000.otp--platform:cpuinfo | /sys/devices/virtual/devlink/platform:fe38c000.otp--platform:cpuinfo |
| platform:fe38c000.otp--platform:fe710000.tsadc | platform:fe38c000.otp--platform:fe710000.tsadc | /sys/devices/virtual/devlink/platform:fe38c000.otp--platform:fe710000.tsadc |
| platform:fe6e0000.pwm--platform:backlight-dsi0 | platform:fe6e0000.pwm--platform:backlight-dsi0 | /sys/devices/virtual/devlink/platform:fe6e0000.pwm--platform:backlight-dsi0 |
| platform:fe740000.gpio1--platform:rk809-sound | platform:fe740000.gpio1--platform:rk809-sound | /sys/devices/virtual/devlink/platform:fe740000.gpio1--platform:rk809-sound |
| platform:fe750000.gpio2--platform:3c0800000.pcie | platform:fe750000.gpio2--platform:3c0800000.pcie | /sys/devices/virtual/devlink/platform:fe750000.gpio2--platform:3c0800000.pcie |
| platform:fe750000.gpio2--platform:fe2a0000.ethernet | platform:fe750000.gpio2--platform:fe2a0000.ethernet | /sys/devices/virtual/devlink/platform:fe750000.gpio2--platform:fe2a0000.ethernet |
| platform:fe760000.gpio3--platform:3c0000000.pcie | platform:fe760000.gpio3--platform:3c0000000.pcie | /sys/devices/virtual/devlink/platform:fe760000.gpio3--platform:3c0000000.pcie |
| platform:fe760000.gpio3--platform:fe010000.ethernet | platform:fe760000.gpio3--platform:fe010000.ethernet | /sys/devices/virtual/devlink/platform:fe760000.gpio3--platform:fe010000.ethernet |
| platform:fe760000.gpio3--platform:minipcie-regulator | platform:fe760000.gpio3--platform:minipcie-regulator | /sys/devices/virtual/devlink/platform:fe760000.gpio3--platform:minipcie-regulator |
| platform:fe770000.gpio4--platform:rk809-sound | platform:fe770000.gpio4--platform:rk809-sound | /sys/devices/virtual/devlink/platform:fe770000.gpio4--platform:rk809-sound |
| platform:fe770000.gpio4--platform:vcc1v8-cam | platform:fe770000.gpio4--platform:vcc1v8-cam | /sys/devices/virtual/devlink/platform:fe770000.gpio4--platform:vcc1v8-cam |
| platform:fe770000.gpio4--platform:vcc3v3-mipi-con | platform:fe770000.gpio4--platform:vcc3v3-mipi-con | /sys/devices/virtual/devlink/platform:fe770000.gpio4--platform:vcc3v3-mipi-con |
| platform:fe820000.phy--platform:fc000000.sata | platform:fe820000.phy--platform:fc000000.sata | /sys/devices/virtual/devlink/platform:fe820000.phy--platform:fc000000.sata |
| platform:fe830000.phy--platform:fd000000.dwc3 | platform:fe830000.phy--platform:fd000000.dwc3 | /sys/devices/virtual/devlink/platform:fe830000.phy--platform:fd000000.dwc3 |
| platform:fe840000.phy--platform:3c0000000.pcie | platform:fe840000.phy--platform:3c0000000.pcie | /sys/devices/virtual/devlink/platform:fe840000.phy--platform:3c0000000.pcie |
| platform:fe850000.phy--platform:fe060000.dsi | platform:fe850000.phy--platform:fe060000.dsi | /sys/devices/virtual/devlink/platform:fe850000.phy--platform:fe060000.dsi |
| platform:fe8a0000.usb2-phy--platform:fcc00000.dwc3 | platform:fe8a0000.usb2-phy--platform:fcc00000.dwc3 | /sys/devices/virtual/devlink/platform:fe8a0000.usb2-phy--platform:fcc00000.dwc3 |
| platform:fe8a0000.usb2-phy--platform:fd000000.dwc3 | platform:fe8a0000.usb2-phy--platform:fd000000.dwc3 | /sys/devices/virtual/devlink/platform:fe8a0000.usb2-phy--platform:fd000000.dwc3 |
| platform:fe8b0000.usb2-phy--platform:fd800000.usb | platform:fe8b0000.usb2-phy--platform:fd800000.usb | /sys/devices/virtual/devlink/platform:fe8b0000.usb2-phy--platform:fd800000.usb |
| platform:fe8b0000.usb2-phy--platform:fd840000.usb | platform:fe8b0000.usb2-phy--platform:fd840000.usb | /sys/devices/virtual/devlink/platform:fe8b0000.usb2-phy--platform:fd840000.usb |
| platform:fe8b0000.usb2-phy--platform:fd880000.usb | platform:fe8b0000.usb2-phy--platform:fd880000.usb | /sys/devices/virtual/devlink/platform:fe8b0000.usb2-phy--platform:fd880000.usb |
| platform:fe8b0000.usb2-phy--platform:fd8c0000.usb | platform:fe8b0000.usb2-phy--platform:fd8c0000.usb | /sys/devices/virtual/devlink/platform:fe8b0000.usb2-phy--platform:fd8c0000.usb |
| platform:fe8c0000.phy--platform:3c0800000.pcie | platform:fe8c0000.phy--platform:3c0800000.pcie | /sys/devices/virtual/devlink/platform:fe8c0000.phy--platform:3c0800000.pcie |
| platform:firmware:scmi--platform:bus-npu | platform:firmware:scmi--platform:bus-npu | /sys/devices/virtual/devlink/platform:firmware:scmi--platform:bus-npu |
| platform:firmware:scmi--platform:dmc | platform:firmware:scmi--platform:dmc | /sys/devices/virtual/devlink/platform:firmware:scmi--platform:dmc |
| platform:firmware:scmi--platform:fde40000.npu | platform:firmware:scmi--platform:fde40000.npu | /sys/devices/virtual/devlink/platform:firmware:scmi--platform:fde40000.npu |
| platform:firmware:scmi--platform:fde60000.gpu | platform:firmware:scmi--platform:fde60000.gpu | /sys/devices/virtual/devlink/platform:firmware:scmi--platform:fde60000.gpu |
| platform:gpio-regulator--platform:3c0800000.pcie | platform:gpio-regulator--platform:3c0800000.pcie | /sys/devices/virtual/devlink/platform:gpio-regulator--platform:3c0800000.pcie |
| platform:minipcie-regulator--platform:3c0000000.pcie | platform:minipcie-regulator--platform:3c0000000.pcie | /sys/devices/virtual/devlink/platform:minipcie-regulator--platform:3c0000000.pcie |
| platform:pinctrl--i2c:0-0020 | platform:pinctrl--i2c:0-0020 | /sys/devices/virtual/devlink/platform:pinctrl--i2c:0-0020 |
| platform:pinctrl--i2c:1-005d | platform:pinctrl--i2c:1-005d | /sys/devices/virtual/devlink/platform:pinctrl--i2c:1-005d |
| platform:pinctrl--platform:fdd40000.i2c | platform:pinctrl--platform:fdd40000.i2c | /sys/devices/virtual/devlink/platform:pinctrl--platform:fdd40000.i2c |
| platform:pinctrl--platform:fdd50000.serial | platform:pinctrl--platform:fdd50000.serial | /sys/devices/virtual/devlink/platform:pinctrl--platform:fdd50000.serial |
| platform:pinctrl--platform:fdd70030.pwm | platform:pinctrl--platform:fdd70030.pwm | /sys/devices/virtual/devlink/platform:pinctrl--platform:fdd70030.pwm |
| platform:pinctrl--platform:fe000000.dwmmc | platform:pinctrl--platform:fe000000.dwmmc | /sys/devices/virtual/devlink/platform:pinctrl--platform:fe000000.dwmmc |
| platform:pinctrl--platform:fe010000.ethernet | platform:pinctrl--platform:fe010000.ethernet | /sys/devices/virtual/devlink/platform:pinctrl--platform:fe010000.ethernet |
| platform:pinctrl--platform:fe0a0000.hdmi | platform:pinctrl--platform:fe0a0000.hdmi | /sys/devices/virtual/devlink/platform:pinctrl--platform:fe0a0000.hdmi |
| platform:pinctrl--platform:fe2a0000.ethernet | platform:pinctrl--platform:fe2a0000.ethernet | /sys/devices/virtual/devlink/platform:pinctrl--platform:fe2a0000.ethernet |
| platform:pinctrl--platform:fe2b0000.dwmmc | platform:pinctrl--platform:fe2b0000.dwmmc | /sys/devices/virtual/devlink/platform:pinctrl--platform:fe2b0000.dwmmc |
| platform:pinctrl--platform:fe410000.i2s | platform:pinctrl--platform:fe410000.i2s | /sys/devices/virtual/devlink/platform:pinctrl--platform:fe410000.i2s |
| platform:pinctrl--platform:fe5a0000.i2c | platform:pinctrl--platform:fe5a0000.i2c | /sys/devices/virtual/devlink/platform:pinctrl--platform:fe5a0000.i2c |
| platform:pinctrl--platform:fe5b0000.i2c | platform:pinctrl--platform:fe5b0000.i2c | /sys/devices/virtual/devlink/platform:pinctrl--platform:fe5b0000.i2c |
| platform:pinctrl--platform:fe5c0000.i2c | platform:pinctrl--platform:fe5c0000.i2c | /sys/devices/virtual/devlink/platform:pinctrl--platform:fe5c0000.i2c |
| platform:pinctrl--platform:fe5d0000.i2c | platform:pinctrl--platform:fe5d0000.i2c | /sys/devices/virtual/devlink/platform:pinctrl--platform:fe5d0000.i2c |
| platform:pinctrl--platform:fe5e0000.i2c | platform:pinctrl--platform:fe5e0000.i2c | /sys/devices/virtual/devlink/platform:pinctrl--platform:fe5e0000.i2c |
| platform:pinctrl--platform:fe640000.spi | platform:pinctrl--platform:fe640000.spi | /sys/devices/virtual/devlink/platform:pinctrl--platform:fe640000.spi |
| platform:pinctrl--platform:fe670000.serial | platform:pinctrl--platform:fe670000.serial | /sys/devices/virtual/devlink/platform:pinctrl--platform:fe670000.serial |
| platform:pinctrl--platform:fe680000.serial | platform:pinctrl--platform:fe680000.serial | /sys/devices/virtual/devlink/platform:pinctrl--platform:fe680000.serial |
| platform:pinctrl--platform:fe6b0000.serial | platform:pinctrl--platform:fe6b0000.serial | /sys/devices/virtual/devlink/platform:pinctrl--platform:fe6b0000.serial |
| platform:pinctrl--platform:fe6c0000.serial | platform:pinctrl--platform:fe6c0000.serial | /sys/devices/virtual/devlink/platform:pinctrl--platform:fe6c0000.serial |
| platform:pinctrl--platform:fe6e0000.pwm | platform:pinctrl--platform:fe6e0000.pwm | /sys/devices/virtual/devlink/platform:pinctrl--platform:fe6e0000.pwm |
| platform:pinctrl--platform:fe6e0030.pwm | platform:pinctrl--platform:fe6e0030.pwm | /sys/devices/virtual/devlink/platform:pinctrl--platform:fe6e0030.pwm |
| platform:pinctrl--platform:fe710000.tsadc | platform:pinctrl--platform:fe710000.tsadc | /sys/devices/virtual/devlink/platform:pinctrl--platform:fe710000.tsadc |
| platform:pinctrl--platform:fiq-debugger | platform:pinctrl--platform:fiq-debugger | /sys/devices/virtual/devlink/platform:pinctrl--platform:fiq-debugger |
| platform:pinctrl--platform:minipcie-regulator | platform:pinctrl--platform:minipcie-regulator | /sys/devices/virtual/devlink/platform:pinctrl--platform:minipcie-regulator |
| platform:pinctrl--platform:pcie3-regulator | platform:pinctrl--platform:pcie3-regulator | /sys/devices/virtual/devlink/platform:pinctrl--platform:pcie3-regulator |
| platform:pinctrl--platform:rk809-sound | platform:pinctrl--platform:rk809-sound | /sys/devices/virtual/devlink/platform:pinctrl--platform:rk809-sound |
| platform:pinctrl--platform:rk817-codec | platform:pinctrl--platform:rk817-codec | /sys/devices/virtual/devlink/platform:pinctrl--platform:rk817-codec |
| platform:pinctrl--platform:sdio-pwrseq | platform:pinctrl--platform:sdio-pwrseq | /sys/devices/virtual/devlink/platform:pinctrl--platform:sdio-pwrseq |
| platform:pinctrl--platform:vcc5v0-host-regulator | platform:pinctrl--platform:vcc5v0-host-regulator | /sys/devices/virtual/devlink/platform:pinctrl--platform:vcc5v0-host-regulator |
| platform:pinctrl--platform:vcc5v0-otg-regulator | platform:pinctrl--platform:vcc5v0-otg-regulator | /sys/devices/virtual/devlink/platform:pinctrl--platform:vcc5v0-otg-regulator |
| platform:pinctrl--platform:wireless-bluetooth | platform:pinctrl--platform:wireless-bluetooth | /sys/devices/virtual/devlink/platform:pinctrl--platform:wireless-bluetooth |
| platform:pinctrl--platform:wireless-wlan | platform:pinctrl--platform:wireless-wlan | /sys/devices/virtual/devlink/platform:pinctrl--platform:wireless-wlan |
| platform:vcc3v3-sys--i2c:0-0020 | platform:vcc3v3-sys--i2c:0-0020 | /sys/devices/virtual/devlink/platform:vcc3v3-sys--i2c:0-0020 |
| platform:vcc3v3-sys--platform:pcie30-avdd0v9 | platform:vcc3v3-sys--platform:pcie30-avdd0v9 | /sys/devices/virtual/devlink/platform:vcc3v3-sys--platform:pcie30-avdd0v9 |
| platform:vcc3v3-sys--platform:pcie30-avdd1v8 | platform:vcc3v3-sys--platform:pcie30-avdd1v8 | /sys/devices/virtual/devlink/platform:vcc3v3-sys--platform:pcie30-avdd1v8 |
| platform:vcc3v3-sys--platform:vcc2v5-ddr | platform:vcc3v3-sys--platform:vcc2v5-ddr | /sys/devices/virtual/devlink/platform:vcc3v3-sys--platform:vcc2v5-ddr |
| platform:vcc5v0-sys--i2c:0-001c | platform:vcc5v0-sys--i2c:0-001c | /sys/devices/virtual/devlink/platform:vcc5v0-sys--i2c:0-001c |
| platform:vcc5v0-sys--platform:vcc3v3-bu | platform:vcc5v0-sys--platform:vcc3v3-bu | /sys/devices/virtual/devlink/platform:vcc5v0-sys--platform:vcc3v3-bu |
| platform:vcc5v0-usb--platform:vcc5v0-host-regulator | platform:vcc5v0-usb--platform:vcc5v0-host-regulator | /sys/devices/virtual/devlink/platform:vcc5v0-usb--platform:vcc5v0-host-regulator |
| platform:vcc5v0-usb--platform:vcc5v0-otg-regulator | platform:vcc5v0-usb--platform:vcc5v0-otg-regulator | /sys/devices/virtual/devlink/platform:vcc5v0-usb--platform:vcc5v0-otg-regulator |
| regulator:regulator.0--platform:backlight-dsi0 | regulator:regulator.0--platform:backlight-dsi0 | /sys/devices/virtual/devlink/regulator:regulator.0--platform:backlight-dsi0 |
| regulator:regulator.0--platform:fc000000.sata | regulator:regulator.0--platform:fc000000.sata | /sys/devices/virtual/devlink/regulator:regulator.0--platform:fc000000.sata |
| regulator:regulator.15--mipi-dsi:fe060000.dsi.0 | regulator:regulator.15--mipi-dsi:fe060000.dsi.0 | /sys/devices/virtual/devlink/regulator:regulator.15--mipi-dsi:fe060000.dsi.0 |
| regulator:regulator.16--cpu:cpu0 | regulator:regulator.16--cpu:cpu0 | /sys/devices/virtual/devlink/regulator:regulator.16--cpu:cpu0 |
| regulator:regulator.17--platform:bus-npu | regulator:regulator.17--platform:bus-npu | /sys/devices/virtual/devlink/regulator:regulator.17--platform:bus-npu |
| regulator:regulator.17--platform:dmc | regulator:regulator.17--platform:dmc | /sys/devices/virtual/devlink/regulator:regulator.17--platform:dmc |
| regulator:regulator.17--platform:fdf40000.rkvenc | regulator:regulator.17--platform:fdf40000.rkvenc | /sys/devices/virtual/devlink/regulator:regulator.17--platform:fdf40000.rkvenc |
| regulator:regulator.17--platform:fdf80200.rkvdec | regulator:regulator.17--platform:fdf80200.rkvdec | /sys/devices/virtual/devlink/regulator:regulator.17--platform:fdf80200.rkvdec |
| regulator:regulator.18--platform:fde60000.gpu | regulator:regulator.18--platform:fde60000.gpu | /sys/devices/virtual/devlink/regulator:regulator.18--platform:fde60000.gpu |
| regulator:regulator.20--platform:fde40000.npu | regulator:regulator.20--platform:fde40000.npu | /sys/devices/virtual/devlink/regulator:regulator.20--platform:fde40000.npu |
| regulator:regulator.21--platform:fdc20000.syscon:io-domains | regulator:regulator.21--platform:fdc20000.syscon:io-domains | /sys/devices/virtual/devlink/regulator:regulator.21--platform:fdc20000.syscon:io-domains |
| regulator:regulator.25--platform:fdc20000.syscon:io-domains | regulator:regulator.25--platform:fdc20000.syscon:io-domains | /sys/devices/virtual/devlink/regulator:regulator.25--platform:fdc20000.syscon:io-domains |
| regulator:regulator.26--platform:fdc20000.syscon:io-domains | regulator:regulator.26--platform:fdc20000.syscon:io-domains | /sys/devices/virtual/devlink/regulator:regulator.26--platform:fdc20000.syscon:io-domains |
| regulator:regulator.26--platform:fe2b0000.dwmmc | regulator:regulator.26--platform:fe2b0000.dwmmc | /sys/devices/virtual/devlink/regulator:regulator.26--platform:fe2b0000.dwmmc |
| regulator:regulator.27--platform:fdc20000.syscon:io-domains | regulator:regulator.27--platform:fdc20000.syscon:io-domains | /sys/devices/virtual/devlink/regulator:regulator.27--platform:fdc20000.syscon:io-domains |
| regulator:regulator.28--platform:fe720000.saradc | regulator:regulator.28--platform:fe720000.saradc | /sys/devices/virtual/devlink/regulator:regulator.28--platform:fe720000.saradc |
| regulator:regulator.31--platform:fdc20000.syscon:io-domains | regulator:regulator.31--platform:fdc20000.syscon:io-domains | /sys/devices/virtual/devlink/regulator:regulator.31--platform:fdc20000.syscon:io-domains |
| regulator:regulator.32--platform:fe2b0000.dwmmc | regulator:regulator.32--platform:fe2b0000.dwmmc | /sys/devices/virtual/devlink/regulator:regulator.32--platform:fe2b0000.dwmmc |
| regulator:regulator.6--phy:phy-fe8a0000.usb2-phy.1 | regulator:regulator.6--phy:phy-fe8a0000.usb2-phy.1 | /sys/devices/virtual/devlink/regulator:regulator.6--phy:phy-fe8a0000.usb2-phy.1 |
| regulator:regulator.6--phy:phy-fe8b0000.usb2-phy.3 | regulator:regulator.6--phy:phy-fe8b0000.usb2-phy.3 | /sys/devices/virtual/devlink/regulator:regulator.6--phy:phy-fe8b0000.usb2-phy.3 |
| regulator:regulator.6--phy:phy-fe8b0000.usb2-phy.4 | regulator:regulator.6--phy:phy-fe8b0000.usb2-phy.4 | /sys/devices/virtual/devlink/regulator:regulator.6--phy:phy-fe8b0000.usb2-phy.4 |
| regulator:regulator.7--phy:phy-fe8a0000.usb2-phy.2 | regulator:regulator.7--phy:phy-fe8a0000.usb2-phy.2 | /sys/devices/virtual/devlink/regulator:regulator.7--phy:phy-fe8a0000.usb2-phy.2 |

### dma (64)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| dma0chan0 | dma0chan0 | /sys/devices/platform/fe530000.dmac/dma/dma0chan0 |
| dma0chan1 | dma0chan1 | /sys/devices/platform/fe530000.dmac/dma/dma0chan1 |
| dma0chan10 | dma0chan10 | /sys/devices/platform/fe530000.dmac/dma/dma0chan10 |
| dma0chan11 | dma0chan11 | /sys/devices/platform/fe530000.dmac/dma/dma0chan11 |
| dma0chan12 | dma0chan12 | /sys/devices/platform/fe530000.dmac/dma/dma0chan12 |
| dma0chan13 | dma0chan13 | /sys/devices/platform/fe530000.dmac/dma/dma0chan13 |
| dma0chan14 | dma0chan14 | /sys/devices/platform/fe530000.dmac/dma/dma0chan14 |
| dma0chan15 | dma0chan15 | /sys/devices/platform/fe530000.dmac/dma/dma0chan15 |
| dma0chan16 | dma0chan16 | /sys/devices/platform/fe530000.dmac/dma/dma0chan16 |
| dma0chan17 | dma0chan17 | /sys/devices/platform/fe530000.dmac/dma/dma0chan17 |
| dma0chan18 | dma0chan18 | /sys/devices/platform/fe530000.dmac/dma/dma0chan18 |
| dma0chan19 | dma0chan19 | /sys/devices/platform/fe530000.dmac/dma/dma0chan19 |
| dma0chan2 | dma0chan2 | /sys/devices/platform/fe530000.dmac/dma/dma0chan2 |
| dma0chan20 | dma0chan20 | /sys/devices/platform/fe530000.dmac/dma/dma0chan20 |
| dma0chan21 | dma0chan21 | /sys/devices/platform/fe530000.dmac/dma/dma0chan21 |
| dma0chan22 | dma0chan22 | /sys/devices/platform/fe530000.dmac/dma/dma0chan22 |
| dma0chan23 | dma0chan23 | /sys/devices/platform/fe530000.dmac/dma/dma0chan23 |
| dma0chan24 | dma0chan24 | /sys/devices/platform/fe530000.dmac/dma/dma0chan24 |
| dma0chan25 | dma0chan25 | /sys/devices/platform/fe530000.dmac/dma/dma0chan25 |
| dma0chan26 | dma0chan26 | /sys/devices/platform/fe530000.dmac/dma/dma0chan26 |
| dma0chan27 | dma0chan27 | /sys/devices/platform/fe530000.dmac/dma/dma0chan27 |
| dma0chan28 | dma0chan28 | /sys/devices/platform/fe530000.dmac/dma/dma0chan28 |
| dma0chan29 | dma0chan29 | /sys/devices/platform/fe530000.dmac/dma/dma0chan29 |
| dma0chan3 | dma0chan3 | /sys/devices/platform/fe530000.dmac/dma/dma0chan3 |
| dma0chan30 | dma0chan30 | /sys/devices/platform/fe530000.dmac/dma/dma0chan30 |
| dma0chan31 | dma0chan31 | /sys/devices/platform/fe530000.dmac/dma/dma0chan31 |
| dma0chan4 | dma0chan4 | /sys/devices/platform/fe530000.dmac/dma/dma0chan4 |
| dma0chan5 | dma0chan5 | /sys/devices/platform/fe530000.dmac/dma/dma0chan5 |
| dma0chan6 | dma0chan6 | /sys/devices/platform/fe530000.dmac/dma/dma0chan6 |
| dma0chan7 | dma0chan7 | /sys/devices/platform/fe530000.dmac/dma/dma0chan7 |
| dma0chan8 | dma0chan8 | /sys/devices/platform/fe530000.dmac/dma/dma0chan8 |
| dma0chan9 | dma0chan9 | /sys/devices/platform/fe530000.dmac/dma/dma0chan9 |
| dma1chan0 | dma1chan0 | /sys/devices/platform/fe550000.dmac/dma/dma1chan0 |
| dma1chan1 | dma1chan1 | /sys/devices/platform/fe550000.dmac/dma/dma1chan1 |
| dma1chan10 | dma1chan10 | /sys/devices/platform/fe550000.dmac/dma/dma1chan10 |
| dma1chan11 | dma1chan11 | /sys/devices/platform/fe550000.dmac/dma/dma1chan11 |
| dma1chan12 | dma1chan12 | /sys/devices/platform/fe550000.dmac/dma/dma1chan12 |
| dma1chan13 | dma1chan13 | /sys/devices/platform/fe550000.dmac/dma/dma1chan13 |
| dma1chan14 | dma1chan14 | /sys/devices/platform/fe550000.dmac/dma/dma1chan14 |
| dma1chan15 | dma1chan15 | /sys/devices/platform/fe550000.dmac/dma/dma1chan15 |
| dma1chan16 | dma1chan16 | /sys/devices/platform/fe550000.dmac/dma/dma1chan16 |
| dma1chan17 | dma1chan17 | /sys/devices/platform/fe550000.dmac/dma/dma1chan17 |
| dma1chan18 | dma1chan18 | /sys/devices/platform/fe550000.dmac/dma/dma1chan18 |
| dma1chan19 | dma1chan19 | /sys/devices/platform/fe550000.dmac/dma/dma1chan19 |
| dma1chan2 | dma1chan2 | /sys/devices/platform/fe550000.dmac/dma/dma1chan2 |
| dma1chan20 | dma1chan20 | /sys/devices/platform/fe550000.dmac/dma/dma1chan20 |
| dma1chan21 | dma1chan21 | /sys/devices/platform/fe550000.dmac/dma/dma1chan21 |
| dma1chan22 | dma1chan22 | /sys/devices/platform/fe550000.dmac/dma/dma1chan22 |
| dma1chan23 | dma1chan23 | /sys/devices/platform/fe550000.dmac/dma/dma1chan23 |
| dma1chan24 | dma1chan24 | /sys/devices/platform/fe550000.dmac/dma/dma1chan24 |
| dma1chan25 | dma1chan25 | /sys/devices/platform/fe550000.dmac/dma/dma1chan25 |
| dma1chan26 | dma1chan26 | /sys/devices/platform/fe550000.dmac/dma/dma1chan26 |
| dma1chan27 | dma1chan27 | /sys/devices/platform/fe550000.dmac/dma/dma1chan27 |
| dma1chan28 | dma1chan28 | /sys/devices/platform/fe550000.dmac/dma/dma1chan28 |
| dma1chan29 | dma1chan29 | /sys/devices/platform/fe550000.dmac/dma/dma1chan29 |
| dma1chan3 | dma1chan3 | /sys/devices/platform/fe550000.dmac/dma/dma1chan3 |
| dma1chan30 | dma1chan30 | /sys/devices/platform/fe550000.dmac/dma/dma1chan30 |
| dma1chan31 | dma1chan31 | /sys/devices/platform/fe550000.dmac/dma/dma1chan31 |
| dma1chan4 | dma1chan4 | /sys/devices/platform/fe550000.dmac/dma/dma1chan4 |
| dma1chan5 | dma1chan5 | /sys/devices/platform/fe550000.dmac/dma/dma1chan5 |
| dma1chan6 | dma1chan6 | /sys/devices/platform/fe550000.dmac/dma/dma1chan6 |
| dma1chan7 | dma1chan7 | /sys/devices/platform/fe550000.dmac/dma/dma1chan7 |
| dma1chan8 | dma1chan8 | /sys/devices/platform/fe550000.dmac/dma/dma1chan8 |
| dma1chan9 | dma1chan9 | /sys/devices/platform/fe550000.dmac/dma/dma1chan9 |

### dma_heap (6)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| cma | cma | /sys/devices/virtual/dma_heap/cma |
| cma-uncached | cma-uncached | /sys/devices/virtual/dma_heap/cma-uncached |
| system | system | /sys/devices/virtual/dma_heap/system |
| system-dma32 | system-dma32 | /sys/devices/virtual/dma_heap/system-dma32 |
| system-uncached | system-uncached | /sys/devices/virtual/dma_heap/system-uncached |
| system-uncached-dma32 | system-uncached-dma32 | /sys/devices/virtual/dma_heap/system-uncached-dma32 |

### drm (8)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| card0 | card0 | /sys/devices/platform/display-subsystem/drm/card0 |
| card0-DSI-1 | card0-DSI-1 | /sys/devices/platform/display-subsystem/drm/card0/card0-DSI-1 |
| card0-HDMI-A-1 | card0-HDMI-A-1 | /sys/devices/platform/display-subsystem/drm/card0/card0-HDMI-A-1 |
| card0-Writeback-1 | card0-Writeback-1 | /sys/devices/platform/display-subsystem/drm/card0/card0-Writeback-1 |
| card1 | card1 | /sys/devices/platform/fde40000.npu/drm/card1 |
| renderD128 | renderD128 | /sys/devices/platform/display-subsystem/drm/renderD128 |
| renderD129 | renderD129 | /sys/devices/platform/fde40000.npu/drm/renderD129 |
| version | version | /sys/class/drm/version |

### extcon (4)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| extcon0 | fe8a0000.usb2-phy<br> | /sys/devices/platform/fe8a0000.usb2-phy/extcon/extcon0 |
| extcon1 | fe8b0000.usb2-phy<br> | /sys/devices/platform/fe8b0000.usb2-phy/extcon/extcon1 |
| extcon3 | rk809-sound<br> | /sys/devices/platform/rk809-sound/extcon/extcon3 |
| extcon4 | fe0a0000.hdmi<br> | /sys/devices/platform/fe0a0000.hdmi/extcon/extcon4 |

### gpio (8)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| export | export | /sys/class/gpio/export |
| gpiochip0 | gpio0<br> | /sys/devices/platform/pinctrl/fdd60000.gpio0/gpio/gpiochip0 |
| gpiochip128 | gpio4<br> | /sys/devices/platform/pinctrl/fe770000.gpio4/gpio/gpiochip128 |
| gpiochip32 | gpio1<br> | /sys/devices/platform/pinctrl/fe740000.gpio1/gpio/gpiochip32 |
| gpiochip511 | rk817-gpio<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/rk805-pinctrl/gpio/gpiochip511 |
| gpiochip64 | gpio2<br> | /sys/devices/platform/pinctrl/fe750000.gpio2/gpio/gpiochip64 |
| gpiochip96 | gpio3<br> | /sys/devices/platform/pinctrl/fe760000.gpio3/gpio/gpiochip96 |
| unexport | unexport | /sys/class/gpio/unexport |

### graphics (2)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| fb0 | rockchipdrmfb<br> | /sys/devices/platform/display-subsystem/graphics/fb0 |
| fbcon | fbcon | /sys/devices/virtual/graphics/fbcon |

### hidraw (3)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| hidraw0 | hidraw0 | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.0/0003:1532:006E.0001/hidraw/hidraw0 |
| hidraw1 | hidraw1 | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.1/0003:1532:006E.0002/hidraw/hidraw1 |
| hidraw2 | hidraw2 | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.2/0003:1532:006E.0003/hidraw/hidraw2 |

### hwmon (2)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| hwmon0 | soc_thermal<br> | /sys/devices/virtual/thermal/thermal_zone0/hwmon0 |
| hwmon1 | gpu_thermal<br> | /sys/devices/virtual/thermal/thermal_zone1/hwmon1 |

### i2c-adapter (7)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| i2c-0 | rk3x-i2c<br> | /sys/devices/platform/fdd40000.i2c/i2c-0 |
| i2c-1 | rk3x-i2c<br> | /sys/devices/platform/fe5a0000.i2c/i2c-1 |
| i2c-2 | rk3x-i2c<br> | /sys/devices/platform/fe5b0000.i2c/i2c-2 |
| i2c-3 | rk3x-i2c<br> | /sys/devices/platform/fe5c0000.i2c/i2c-3 |
| i2c-4 | rk3x-i2c<br> | /sys/devices/platform/fe5d0000.i2c/i2c-4 |
| i2c-5 | rk3x-i2c<br> | /sys/devices/platform/fe5e0000.i2c/i2c-5 |
| i2c-6 | DesignWare HDMI<br> | /sys/devices/platform/fe0a0000.hdmi/i2c-6 |

### i2c-dev (7)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| i2c-0 | rk3x-i2c<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/i2c-dev/i2c-0 |
| i2c-1 | rk3x-i2c<br> | /sys/devices/platform/fe5a0000.i2c/i2c-1/i2c-dev/i2c-1 |
| i2c-2 | rk3x-i2c<br> | /sys/devices/platform/fe5b0000.i2c/i2c-2/i2c-dev/i2c-2 |
| i2c-3 | rk3x-i2c<br> | /sys/devices/platform/fe5c0000.i2c/i2c-3/i2c-dev/i2c-3 |
| i2c-4 | rk3x-i2c<br> | /sys/devices/platform/fe5d0000.i2c/i2c-4/i2c-dev/i2c-4 |
| i2c-5 | rk3x-i2c<br> | /sys/devices/platform/fe5e0000.i2c/i2c-5/i2c-dev/i2c-5 |
| i2c-6 | DesignWare HDMI<br> | /sys/devices/platform/fe0a0000.hdmi/i2c-6/i2c-dev/i2c-6 |

### ieee80211 (1)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| phy0 | phy0<br> | /sys/devices/platform/fe000000.dwmmc/mmc_host/mmc3/mmc3:0001/mmc3:0001:1/sv6621s_wireless1.11.auto/ieee80211/phy0 |

### input (24)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| event0 | event0 | /sys/devices/platform/fe6e0030.pwm/input/input0/event0 |
| event1 | event1 | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/rk805-pwrkey/input/input1/event1 |
| event10 | event10 | /sys/devices/platform/fe0a0000.hdmi/dw-hdmi-cec.4.auto/input/input10/event10 |
| event11 | event11 | /sys/devices/platform/adc-keys/input/input11/event11 |
| event2 | event2 | /sys/devices/virtual/input/input2/event2 |
| event3 | event3 | /sys/devices/platform/rk809-sound/sound/card0/input3/event3 |
| event4 | event4 | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.0/0003:1532:006E.0001/input/input4/event4 |
| event5 | event5 | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.1/0003:1532:006E.0002/input/input5/event5 |
| event6 | event6 | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.1/0003:1532:006E.0002/input/input6/event6 |
| event7 | event7 | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.1/0003:1532:006E.0002/input/input7/event7 |
| event8 | event8 | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.1/0003:1532:006E.0002/input/input8/event8 |
| event9 | event9 | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.2/0003:1532:006E.0003/input/input9/event9 |
| input0 | fe6e0030.pwm<br> | /sys/devices/platform/fe6e0030.pwm/input/input0 |
| input1 | rk805 pwrkey<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/rk805-pwrkey/input/input1 |
| input10 | hdmi_cec_key<br> | /sys/devices/platform/fe0a0000.hdmi/dw-hdmi-cec.4.auto/input/input10 |
| input11 | adc-keys<br> | /sys/devices/platform/adc-keys/input/input11 |
| input2 | goodix-ts<br> | /sys/devices/virtual/input/input2 |
| input3 | rockchip-rk809 Headset<br> | /sys/devices/platform/rk809-sound/sound/card0/input3 |
| input4 | Razer Razer DeathAdder Essential<br> | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.0/0003:1532:006E.0001/input/input4 |
| input5 | Razer Razer DeathAdder Essential Keyboard<br> | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.1/0003:1532:006E.0002/input/input5 |
| input6 | Razer Razer DeathAdder Essential Consumer Control<br> | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.1/0003:1532:006E.0002/input/input6 |
| input7 | Razer Razer DeathAdder Essential System Control<br> | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.1/0003:1532:006E.0002/input/input7 |
| input8 | Razer Razer DeathAdder Essential<br> | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.1/0003:1532:006E.0002/input/input8 |
| input9 | Razer Razer DeathAdder Essential<br> | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.2/0003:1532:006E.0003/input/input9 |

### iommu (9)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| fde4b000.iommu | fde4b000.iommu | /sys/devices/platform/fde4b000.iommu/iommu/fde4b000.iommu |
| fdea0800.iommu | fdea0800.iommu | /sys/devices/platform/fdea0800.iommu/iommu/fdea0800.iommu |
| fded0480.iommu | fded0480.iommu | /sys/devices/platform/fded0480.iommu/iommu/fded0480.iommu |
| fdee0800.iommu | fdee0800.iommu | /sys/devices/platform/fdee0800.iommu/iommu/fdee0800.iommu |
| fdef0800.iommu | fdef0800.iommu | /sys/devices/platform/fdef0800.iommu/iommu/fdef0800.iommu |
| fdf40f00.iommu | fdf40f00.iommu | /sys/devices/platform/fdf40f00.iommu/iommu/fdf40f00.iommu |
| fdf80800.iommu | fdf80800.iommu | /sys/devices/platform/fdf80800.iommu/iommu/fdf80800.iommu |
| fdff1a00.iommu | fdff1a00.iommu | /sys/devices/platform/fdff1a00.iommu/iommu/fdff1a00.iommu |
| fe043e00.iommu | fe043e00.iommu | /sys/devices/platform/fe043e00.iommu/iommu/fe043e00.iommu |

### leds (16)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| fan | fan | /sys/devices/platform/leds/leds/fan |
| gpio1a4 | gpio1a4 | /sys/devices/platform/leds/leds/gpio1a4 |
| gpio1b0 | gpio1b0 | /sys/devices/platform/leds/leds/gpio1b0 |
| gpio1b1 | gpio1b1 | /sys/devices/platform/leds/leds/gpio1b1 |
| gpio1b2 | gpio1b2 | /sys/devices/platform/leds/leds/gpio1b2 |
| gpio1d0 | gpio1d0 | /sys/devices/platform/leds/leds/gpio1d0 |
| gpio1d4 | gpio1d4 | /sys/devices/platform/leds/leds/gpio1d4 |
| gpio3b5 | gpio3b5 | /sys/devices/platform/leds/leds/gpio3b5 |
| gpio3b6 | gpio3b6 | /sys/devices/platform/leds/leds/gpio3b6 |
| gpio4c4 | gpio4c4 | /sys/devices/platform/leds/leds/gpio4c4 |
| gpio4c6 | gpio4c6 | /sys/devices/platform/leds/leds/gpio4c6 |
| input9::capslock | input9::capslock | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.2/0003:1532:006E.0003/input/input9/input9::capslock |
| input9::numlock | input9::numlock | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.2/0003:1532:006E.0003/input/input9/input9::numlock |
| input9::scrolllock | input9::scrolllock | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/5-1:1.2/0003:1532:006E.0003/input/input9/input9::scrolllock |
| mmc0:: | mmc0:: | /sys/devices/platform/fe310000.sdhci/leds/mmc0:: |
| work-led | work-led | /sys/devices/platform/leds/leds/work-led |

### mdio_bus (3)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| fixed-0 | fixed-0 | /sys/devices/platform/Fixed MDIO bus.0/mdio_bus/fixed-0 |
| stmmac-0 | stmmac-0 | /sys/devices/platform/fe2a0000.ethernet/mdio_bus/stmmac-0 |
| stmmac-1 | stmmac-1 | /sys/devices/platform/fe010000.ethernet/mdio_bus/stmmac-1 |

### mem (8)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| full | full | /sys/devices/virtual/mem/full |
| kmsg | kmsg | /sys/devices/virtual/mem/kmsg |
| mem | mem | /sys/devices/virtual/mem/mem |
| null | null | /sys/devices/virtual/mem/null |
| port | port | /sys/devices/virtual/mem/port |
| random | random | /sys/devices/virtual/mem/random |
| urandom | urandom | /sys/devices/virtual/mem/urandom |
| zero | zero | /sys/devices/virtual/mem/zero |

### misc (20)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| btrfs-control | btrfs-control | /sys/devices/virtual/misc/btrfs-control |
| cpu_dma_latency | cpu_dma_latency | /sys/devices/virtual/misc/cpu_dma_latency |
| crypto | crypto | /sys/devices/virtual/misc/crypto |
| device-mapper | device-mapper | /sys/devices/virtual/misc/device-mapper |
| fuse | fuse | /sys/devices/virtual/misc/fuse |
| hdmi_hdcp1x | hdmi_hdcp1x | /sys/devices/virtual/misc/hdmi_hdcp1x |
| hw_random | hw_random | /sys/devices/virtual/misc/hw_random |
| loop-control | loop-control | /sys/devices/virtual/misc/loop-control |
| mali0 | mali0 | /sys/devices/platform/fde60000.gpu/misc/mali0 |
| rfkill | rfkill | /sys/devices/virtual/misc/rfkill |
| rga | rga | /sys/devices/virtual/misc/rga |
| rk_cec | rk_cec | /sys/devices/virtual/misc/rk_cec |
| sw_sync | sw_sync | /sys/devices/virtual/misc/sw_sync |
| tun | tun | /sys/devices/virtual/misc/tun |
| ubi_ctrl | ubi_ctrl | /sys/devices/virtual/misc/ubi_ctrl |
| uhid | uhid | /sys/devices/virtual/misc/uhid |
| uinput | uinput | /sys/devices/virtual/misc/uinput |
| vendor_storage | vendor_storage | /sys/devices/virtual/misc/vendor_storage |
| vhci | vhci | /sys/devices/virtual/misc/vhci |
| watchdog | watchdog | /sys/devices/platform/fe600000.watchdog/misc/watchdog |

### mmc_host (3)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| mmc0 | mmc0 | /sys/devices/platform/fe310000.sdhci/mmc_host/mmc0 |
| mmc1 | mmc1 | /sys/devices/platform/fe2b0000.dwmmc/mmc_host/mmc1 |
| mmc3 | mmc3 | /sys/devices/platform/fe000000.dwmmc/mmc_host/mmc3 |

### mpp_class (1)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| mpp_service | mpp_service | /sys/devices/platform/mpp-srv/mpp_class/mpp_service |

### net (5)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| dummy0 | dummy0 | /sys/devices/virtual/net/dummy0 |
| eth0 | eth0 | /sys/devices/platform/fe010000.ethernet/net/eth0 |
| eth1 | eth1 | /sys/devices/platform/fe2a0000.ethernet/net/eth1 |
| lo | lo | /sys/devices/virtual/net/lo |
| wlan0 | wlan0 | /sys/devices/platform/fe000000.dwmmc/mmc_host/mmc3/mmc3:0001/mmc3:0001:1/sv6621s_wireless1.11.auto/net/wlan0 |

### phy (9)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| phy-fe820000.phy.5 | phy-fe820000.phy.5 | /sys/devices/platform/fe820000.phy/phy/phy-fe820000.phy.5 |
| phy-fe830000.phy.6 | phy-fe830000.phy.6 | /sys/devices/platform/fe830000.phy/phy/phy-fe830000.phy.6 |
| phy-fe840000.phy.7 | phy-fe840000.phy.7 | /sys/devices/platform/fe840000.phy/phy/phy-fe840000.phy.7 |
| phy-fe850000.phy.0 | phy-fe850000.phy.0 | /sys/devices/platform/fe850000.phy/phy/phy-fe850000.phy.0 |
| phy-fe8a0000.usb2-phy.1 | phy-fe8a0000.usb2-phy.1 | /sys/devices/platform/fe8a0000.usb2-phy/phy/phy-fe8a0000.usb2-phy.1 |
| phy-fe8a0000.usb2-phy.2 | phy-fe8a0000.usb2-phy.2 | /sys/devices/platform/fe8a0000.usb2-phy/phy/phy-fe8a0000.usb2-phy.2 |
| phy-fe8b0000.usb2-phy.3 | phy-fe8b0000.usb2-phy.3 | /sys/devices/platform/fe8b0000.usb2-phy/phy/phy-fe8b0000.usb2-phy.3 |
| phy-fe8b0000.usb2-phy.4 | phy-fe8b0000.usb2-phy.4 | /sys/devices/platform/fe8b0000.usb2-phy/phy/phy-fe8b0000.usb2-phy.4 |
| phy-fe8c0000.phy.8 | phy-fe8c0000.phy.8 | /sys/devices/platform/fe8c0000.phy/phy/phy-fe8c0000.phy.8 |

### ppp (1)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| ppp | ppp | /sys/devices/virtual/ppp/ppp |

### ptp (2)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| ptp0 | ptp0 | /sys/devices/platform/fe010000.ethernet/ptp/ptp0 |
| ptp1 | ptp1 | /sys/devices/platform/fe2a0000.ethernet/ptp/ptp1 |

### pwm (2)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| pwmchip0 | pwmchip0 | /sys/devices/platform/fdd70030.pwm/pwm/pwmchip0 |
| pwmchip1 | pwmchip1 | /sys/devices/platform/fe6e0000.pwm/pwm/pwmchip1 |

### regulator (34)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| regulator.0 | regulator-dummy<br> | /sys/devices/platform/reg-dummy/regulator/regulator.0 |
| regulator.1 | dc_12v<br> | /sys/devices/platform/dc-12v/regulator/regulator.1 |
| regulator.10 | vcc3v3_pcie<br> | /sys/devices/platform/gpio-regulator/regulator/regulator.10 |
| regulator.11 | pcie3_power<br> | /sys/devices/platform/pcie3-regulator/regulator/regulator.11 |
| regulator.12 | minipcie_power<br> | /sys/devices/platform/minipcie-regulator/regulator/regulator.12 |
| regulator.13 | vcc2v5-sys<br> | /sys/devices/platform/vcc2v5-ddr/regulator/regulator.13 |
| regulator.14 | vcc3v3_bu<br> | /sys/devices/platform/vcc3v3-bu/regulator/regulator.14 |
| regulator.15 | vcc3v3_lcd0_n<br> | /sys/devices/platform/vcc3v3-lcd0-n/regulator/regulator.15 |
| regulator.16 | vdd_cpu<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-001c/regulator/regulator.16 |
| regulator.17 | vdd_logic<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/regulator/regulator.17 |
| regulator.18 | vdd_gpu<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/regulator/regulator.18 |
| regulator.19 | vcc_ddr<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/regulator/regulator.19 |
| regulator.2 | vcc3v3_sys<br> | /sys/devices/platform/vcc3v3-sys/regulator/regulator.2 |
| regulator.20 | vdd_npu<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/regulator/regulator.20 |
| regulator.21 | vcc_1v8<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/regulator/regulator.21 |
| regulator.22 | vdda0v9_image<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/regulator/regulator.22 |
| regulator.23 | vdda_0v9<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/regulator/regulator.23 |
| regulator.24 | vdda0v9_pmu<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/regulator/regulator.24 |
| regulator.25 | vccio_acodec<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/regulator/regulator.25 |
| regulator.26 | vccio_sd<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/regulator/regulator.26 |
| regulator.27 | vcc3v3_pmu<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/regulator/regulator.27 |
| regulator.28 | vcca_1v8<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/regulator/regulator.28 |
| regulator.29 | vcca1v8_pmu<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/regulator/regulator.29 |
| regulator.3 | vcc5v0_sys<br> | /sys/devices/platform/vcc5v0-sys/regulator/regulator.3 |
| regulator.30 | vcca1v8_image<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/regulator/regulator.30 |
| regulator.31 | vcc_3v3<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/regulator/regulator.31 |
| regulator.32 | vcc3v3_sd<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/regulator/regulator.32 |
| regulator.33 | vcc3v3_mipi_con<br> | /sys/devices/platform/vcc3v3-mipi-con/regulator/regulator.33 |
| regulator.4 | vcc5v0_usb<br> | /sys/devices/platform/vcc5v0-usb/regulator/regulator.4 |
| regulator.5 | vcc1v8_cam<br> | /sys/devices/platform/vcc1v8-cam/regulator/regulator.5 |
| regulator.6 | vcc5v0_host<br> | /sys/devices/platform/vcc5v0-host-regulator/regulator/regulator.6 |
| regulator.7 | vcc5v0_otg<br> | /sys/devices/platform/vcc5v0-otg-regulator/regulator/regulator.7 |
| regulator.8 | pcie30_avdd0v9<br> | /sys/devices/platform/pcie30-avdd0v9/regulator/regulator.8 |
| regulator.9 | pcie30_avdd1v8<br> | /sys/devices/platform/pcie30-avdd1v8/regulator/regulator.9 |

### rfkill (3)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| rfkill0 | bt_default<br> | /sys/devices/platform/wireless-bluetooth/rfkill/rfkill0 |
| rfkill1 | phy0<br> | /sys/devices/platform/fe000000.dwmmc/mmc_host/mmc3/mmc3:0001/mmc3:0001:1/sv6621s_wireless1.11.auto/ieee80211/phy0/rfkill1 |
| rfkill2 | hci0<br> | /sys/devices/platform/fe000000.dwmmc/mmc_host/mmc3/mmc3:0001/mmc3:0001:1/btseekwave.10.auto/bluetooth/hci0/rfkill2 |

### rkwifi (3)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| wifi_bt_vbat | wifi_bt_vbat | /sys/class/rkwifi/wifi_bt_vbat |
| wifi_power | wifi_power | /sys/class/rkwifi/wifi_power |
| wifi_set_carddetect | wifi_set_carddetect | /sys/class/rkwifi/wifi_set_carddetect |

### rtc (2)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| rtc0 | rk808-rtc rk808-rtc<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/rk808-rtc/rtc/rtc0 |
| rtc1 | rtc-hym8563 5-0051<br> | /sys/devices/platform/fe5e0000.i2c/i2c-5/5-0051/rtc/rtc1 |

### scsi_host (1)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| host0 | host0 | /sys/devices/platform/fc000000.sata/ata1/host0/scsi_host/host0 |

### skwbtlog_port (1)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| SKWBT_LOG | SKWBT_LOG | /sys/devices/virtual/skwbtlog_port/SKWBT_LOG |

### sound (9)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| card0 | card0 | /sys/devices/platform/rk809-sound/sound/card0 |
| card1 | card1 | /sys/devices/platform/hdmi-sound/sound/card1 |
| controlC0 | controlC0 | /sys/devices/platform/rk809-sound/sound/card0/controlC0 |
| controlC1 | controlC1 | /sys/devices/platform/hdmi-sound/sound/card1/controlC1 |
| pcmC0D0c | pcmC0D0c | /sys/devices/platform/rk809-sound/sound/card0/pcmC0D0c |
| pcmC0D0p | pcmC0D0p | /sys/devices/platform/rk809-sound/sound/card0/pcmC0D0p |
| pcmC1D0p | pcmC1D0p | /sys/devices/platform/hdmi-sound/sound/card1/pcmC1D0p |
| seq | seq | /sys/devices/virtual/sound/seq |
| timer | timer | /sys/devices/virtual/sound/timer |

### spi_master (1)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| spi3 | spi3 | /sys/devices/platform/fe640000.spi/spi_master/spi3 |

### spidev (1)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| spidev3.0 | spidev3.0 | /sys/devices/platform/fe640000.spi/spi_master/spi3/spi3.0/spidev/spidev3.0 |

### thermal (4)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| cooling_device0 | cooling_device0 | /sys/devices/virtual/thermal/cooling_device0 |
| cooling_device1 | cooling_device1 | /sys/devices/virtual/thermal/cooling_device1 |
| thermal_zone0 | thermal_zone0 | /sys/devices/virtual/thermal/thermal_zone0 |
| thermal_zone1 | thermal_zone1 | /sys/devices/virtual/thermal/thermal_zone1 |

### tty (73)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| console | console | /sys/devices/virtual/tty/console |
| ptmx | ptmx | /sys/devices/virtual/tty/ptmx |
| tty | tty | /sys/devices/virtual/tty/tty |
| tty0 | tty0 | /sys/devices/virtual/tty/tty0 |
| tty1 | tty1 | /sys/devices/virtual/tty/tty1 |
| tty10 | tty10 | /sys/devices/virtual/tty/tty10 |
| tty11 | tty11 | /sys/devices/virtual/tty/tty11 |
| tty12 | tty12 | /sys/devices/virtual/tty/tty12 |
| tty13 | tty13 | /sys/devices/virtual/tty/tty13 |
| tty14 | tty14 | /sys/devices/virtual/tty/tty14 |
| tty15 | tty15 | /sys/devices/virtual/tty/tty15 |
| tty16 | tty16 | /sys/devices/virtual/tty/tty16 |
| tty17 | tty17 | /sys/devices/virtual/tty/tty17 |
| tty18 | tty18 | /sys/devices/virtual/tty/tty18 |
| tty19 | tty19 | /sys/devices/virtual/tty/tty19 |
| tty2 | tty2 | /sys/devices/virtual/tty/tty2 |
| tty20 | tty20 | /sys/devices/virtual/tty/tty20 |
| tty21 | tty21 | /sys/devices/virtual/tty/tty21 |
| tty22 | tty22 | /sys/devices/virtual/tty/tty22 |
| tty23 | tty23 | /sys/devices/virtual/tty/tty23 |
| tty24 | tty24 | /sys/devices/virtual/tty/tty24 |
| tty25 | tty25 | /sys/devices/virtual/tty/tty25 |
| tty26 | tty26 | /sys/devices/virtual/tty/tty26 |
| tty27 | tty27 | /sys/devices/virtual/tty/tty27 |
| tty28 | tty28 | /sys/devices/virtual/tty/tty28 |
| tty29 | tty29 | /sys/devices/virtual/tty/tty29 |
| tty3 | tty3 | /sys/devices/virtual/tty/tty3 |
| tty30 | tty30 | /sys/devices/virtual/tty/tty30 |
| tty31 | tty31 | /sys/devices/virtual/tty/tty31 |
| tty32 | tty32 | /sys/devices/virtual/tty/tty32 |
| tty33 | tty33 | /sys/devices/virtual/tty/tty33 |
| tty34 | tty34 | /sys/devices/virtual/tty/tty34 |
| tty35 | tty35 | /sys/devices/virtual/tty/tty35 |
| tty36 | tty36 | /sys/devices/virtual/tty/tty36 |
| tty37 | tty37 | /sys/devices/virtual/tty/tty37 |
| tty38 | tty38 | /sys/devices/virtual/tty/tty38 |
| tty39 | tty39 | /sys/devices/virtual/tty/tty39 |
| tty4 | tty4 | /sys/devices/virtual/tty/tty4 |
| tty40 | tty40 | /sys/devices/virtual/tty/tty40 |
| tty41 | tty41 | /sys/devices/virtual/tty/tty41 |
| tty42 | tty42 | /sys/devices/virtual/tty/tty42 |
| tty43 | tty43 | /sys/devices/virtual/tty/tty43 |
| tty44 | tty44 | /sys/devices/virtual/tty/tty44 |
| tty45 | tty45 | /sys/devices/virtual/tty/tty45 |
| tty46 | tty46 | /sys/devices/virtual/tty/tty46 |
| tty47 | tty47 | /sys/devices/virtual/tty/tty47 |
| tty48 | tty48 | /sys/devices/virtual/tty/tty48 |
| tty49 | tty49 | /sys/devices/virtual/tty/tty49 |
| tty5 | tty5 | /sys/devices/virtual/tty/tty5 |
| tty50 | tty50 | /sys/devices/virtual/tty/tty50 |
| tty51 | tty51 | /sys/devices/virtual/tty/tty51 |
| tty52 | tty52 | /sys/devices/virtual/tty/tty52 |
| tty53 | tty53 | /sys/devices/virtual/tty/tty53 |
| tty54 | tty54 | /sys/devices/virtual/tty/tty54 |
| tty55 | tty55 | /sys/devices/virtual/tty/tty55 |
| tty56 | tty56 | /sys/devices/virtual/tty/tty56 |
| tty57 | tty57 | /sys/devices/virtual/tty/tty57 |
| tty58 | tty58 | /sys/devices/virtual/tty/tty58 |
| tty59 | tty59 | /sys/devices/virtual/tty/tty59 |
| tty6 | tty6 | /sys/devices/virtual/tty/tty6 |
| tty60 | tty60 | /sys/devices/virtual/tty/tty60 |
| tty61 | tty61 | /sys/devices/virtual/tty/tty61 |
| tty62 | tty62 | /sys/devices/virtual/tty/tty62 |
| tty63 | tty63 | /sys/devices/virtual/tty/tty63 |
| tty7 | tty7 | /sys/devices/virtual/tty/tty7 |
| tty8 | tty8 | /sys/devices/virtual/tty/tty8 |
| tty9 | tty9 | /sys/devices/virtual/tty/tty9 |
| ttyFIQ0 | ttyFIQ0 | /sys/devices/platform/fiq_debugger.0/tty/ttyFIQ0 |
| ttyS0 | ttyS0 | /sys/devices/platform/fdd50000.serial/tty/ttyS0 |
| ttyS3 | ttyS3 | /sys/devices/platform/fe670000.serial/tty/ttyS3 |
| ttyS4 | ttyS4 | /sys/devices/platform/fe680000.serial/tty/ttyS4 |
| ttyS7 | ttyS7 | /sys/devices/platform/fe6b0000.serial/tty/ttyS7 |
| ttyS8 | ttyS8 | /sys/devices/platform/fe6c0000.serial/tty/ttyS8 |

### ubi (1)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| version | version | /sys/class/ubi/version |

### udc (1)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| fcc00000.dwc3 | fcc00000.dwc3 | /sys/devices/platform/usbdrd/fcc00000.dwc3/udc/fcc00000.dwc3 |

### usbmon (7)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| usbmon0 | usbmon0 | /sys/devices/virtual/usbmon/usbmon0 |
| usbmon1 | usbmon1 | /sys/devices/platform/fd800000.usb/usbmon/usbmon1 |
| usbmon2 | usbmon2 | /sys/devices/platform/fd880000.usb/usbmon/usbmon2 |
| usbmon3 | usbmon3 | /sys/devices/platform/fd840000.usb/usbmon/usbmon3 |
| usbmon4 | usbmon4 | /sys/devices/platform/fd8c0000.usb/usbmon/usbmon4 |
| usbmon5 | usbmon5 | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usbmon/usbmon5 |
| usbmon6 | usbmon6 | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usbmon/usbmon6 |

### vc (21)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| vcs | vcs | /sys/devices/virtual/vc/vcs |
| vcs1 | vcs1 | /sys/devices/virtual/vc/vcs1 |
| vcs2 | vcs2 | /sys/devices/virtual/vc/vcs2 |
| vcs3 | vcs3 | /sys/devices/virtual/vc/vcs3 |
| vcs4 | vcs4 | /sys/devices/virtual/vc/vcs4 |
| vcs5 | vcs5 | /sys/devices/virtual/vc/vcs5 |
| vcs6 | vcs6 | /sys/devices/virtual/vc/vcs6 |
| vcsa | vcsa | /sys/devices/virtual/vc/vcsa |
| vcsa1 | vcsa1 | /sys/devices/virtual/vc/vcsa1 |
| vcsa2 | vcsa2 | /sys/devices/virtual/vc/vcsa2 |
| vcsa3 | vcsa3 | /sys/devices/virtual/vc/vcsa3 |
| vcsa4 | vcsa4 | /sys/devices/virtual/vc/vcsa4 |
| vcsa5 | vcsa5 | /sys/devices/virtual/vc/vcsa5 |
| vcsa6 | vcsa6 | /sys/devices/virtual/vc/vcsa6 |
| vcsu | vcsu | /sys/devices/virtual/vc/vcsu |
| vcsu1 | vcsu1 | /sys/devices/virtual/vc/vcsu1 |
| vcsu2 | vcsu2 | /sys/devices/virtual/vc/vcsu2 |
| vcsu3 | vcsu3 | /sys/devices/virtual/vc/vcsu3 |
| vcsu4 | vcsu4 | /sys/devices/virtual/vc/vcsu4 |
| vcsu5 | vcsu5 | /sys/devices/virtual/vc/vcsu5 |
| vcsu6 | vcsu6 | /sys/devices/virtual/vc/vcsu6 |

### video4linux (13)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| v4l-subdev0 | rkisp-isp-subdev<br> | /sys/devices/platform/rkisp-vir0/video4linux/v4l-subdev0 |
| v4l-subdev1 | rkisp-csi-subdev<br> | /sys/devices/platform/rkisp-vir0/video4linux/v4l-subdev1 |
| v4l-subdev2 | rockchip-csi2-dphy0<br> | /sys/devices/platform/csi2-dphy0/video4linux/v4l-subdev2 |
| video0 | rkisp_mainpath<br> | /sys/devices/platform/rkisp-vir0/video4linux/video0 |
| video1 | rkisp_selfpath<br> | /sys/devices/platform/rkisp-vir0/video4linux/video1 |
| video2 | rkisp_rawwr0<br> | /sys/devices/platform/rkisp-vir0/video4linux/video2 |
| video3 | rkisp_rawwr2<br> | /sys/devices/platform/rkisp-vir0/video4linux/video3 |
| video4 | rkisp_rawwr3<br> | /sys/devices/platform/rkisp-vir0/video4linux/video4 |
| video5 | rkisp_iqtool<br> | /sys/devices/platform/rkisp-vir0/video4linux/video5 |
| video6 | rkisp_rawrd0_m<br> | /sys/devices/platform/rkisp-vir0/video4linux/video6 |
| video7 | rkisp_rawrd2_s<br> | /sys/devices/platform/rkisp-vir0/video4linux/video7 |
| video8 | rkisp-statistics<br> | /sys/devices/platform/rkisp-vir0/video4linux/video8 |
| video9 | rkisp-input-params<br> | /sys/devices/platform/rkisp-vir0/video4linux/video9 |

### vtconsole (2)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| vtcon0 | (S) dummy device<br> | /sys/devices/virtual/vtconsole/vtcon0 |
| vtcon1 | (M) frame buffer device<br> | /sys/devices/virtual/vtconsole/vtcon1 |

### wakeup (18)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| wakeup0 | fdea0400.vdpu<br> | /sys/devices/platform/fdea0400.vdpu/wakeup/wakeup0 |
| wakeup1 | fdee0000.vepu<br> | /sys/devices/platform/fdee0000.vepu/wakeup/wakeup1 |
| wakeup10 | mmc3<br> | /sys/devices/virtual/wakeup/wakeup10 |
| wakeup11 | mmc1<br> | /sys/devices/virtual/wakeup/wakeup11 |
| wakeup12 | mmc0<br> | /sys/devices/virtual/wakeup/wakeup12 |
| wakeup13 | fdeb0000.rk_rga<br> | /sys/devices/platform/fdeb0000.rk_rga/wakeup/wakeup13 |
| wakeup14 | 5-1<br> | /sys/devices/platform/usbhost/fd000000.dwc3/xhci-hcd.0.auto/usb5/5-1/wakeup/wakeup14 |
| wakeup15 | fdf40000.rkvenc<br> | /sys/devices/platform/fdf40000.rkvenc/wakeup/wakeup15 |
| wakeup16 | fdf80200.rkvdec<br> | /sys/devices/platform/fdf80200.rkvdec/wakeup/wakeup16 |
| wakeup17 | skw_sdio_r_wakelock<br> | /sys/devices/virtual/wakeup/wakeup17 |
| wakeup2 | fdef0000.iep<br> | /sys/devices/platform/fdef0000.iep/wakeup/wakeup2 |
| wakeup3 | fded0000.jpegd<br> | /sys/devices/platform/fded0000.jpegd/wakeup/wakeup3 |
| wakeup4 | fe6e0030.pwm<br> | /sys/devices/platform/fe6e0030.pwm/wakeup/wakeup4 |
| wakeup5 | 0-0020<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/wakeup/wakeup5 |
| wakeup6 | rk805-pwrkey<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/rk805-pwrkey/wakeup/wakeup6 |
| wakeup7 | rk808-rtc<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/rk808-rtc/wakeup/wakeup7 |
| wakeup8 | alarmtimer.1.auto<br> | /sys/devices/platform/fdd40000.i2c/i2c-0/0-0020/rk808-rtc/rtc/rtc0/alarmtimer.1.auto/wakeup/wakeup8 |
| wakeup9 | fcc00000.dwc3<br> | /sys/devices/platform/usbdrd/fcc00000.dwc3/wakeup/wakeup9 |

### watchdog (1)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| watchdog0 | watchdog0 | /sys/devices/platform/fe600000.watchdog/watchdog/watchdog0 |

### xt_idletimer (1)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| timers | timers | /sys/devices/virtual/xt_idletimer/timers |

### zram-control (2)

| 设备名 | 名称 / 备注 | sysfs 路径 |
|---|---|---|
| hot_add | hot_add | /sys/class/zram-control/hot_add |
| hot_remove | hot_remove | /sys/class/zram-control/hot_remove |

