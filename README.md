# [V8850](https://doc.soc.xin/V8850)

* [unisoc](https://www.unisoc.com): [Cortex-A7](https://github.com/SoCXin/Cortex)
* [L5R3](https://github.com/SoCXin/Level): 624 MHz

## [简介](https://github.com/SoCXin/V8850/wiki)

[V8850](https://www.unisoc.com/cn_zh/home/new/CPZX1009) 高度集成了BB/RF/PMIC/GNSS，拥有更小尺寸8.2x8.2mm, 可使模组尺寸较上一代减小30%, 最小可至16x18mm，适合对于设备尺寸要求较高的更广泛应用场景。

集成GNSS与Wifi-Scan的室内外融合定位。V8850支持GPS/BDS/Galileo/Glonas，支持单模/双模/三模/四模工作方式，定位精度达到5米。更高的集成度使带GNSS定位的蜂窝通讯模组最小可至16x18mm, 为当前市场上更小的Cat.1加GNSS定位模组。同时，集成GNSS IP使模组外围设计更加简捷方便且整体成本能做到更优。

V8850芯片平台增加用户空间/节省外部Flash空间，增加更丰富IO接口可以外置更多传感器，满足终端客户更多的应用行业场景。支持宽温，可承载工作温度从-40度到85度，达到工规标准，满足特定市场对工规宽温的高要求。

V8850芯片以更先进的制程工艺、先进的芯片级电源设计、优秀的内核级电源管理和融合的协议栈电源优化，大幅度减低了整体功耗。以定位器产品为例，V8850较上一代PSM功耗进一步优化，可使2000mAh电池容量的定位器每天按定位/上传一次，工作天数从443天提升为512天。同样地，DRX功耗比上一代降低15%，同样为2000mAh电池容量的共享二轮车，TDD寻呼2.56s按待机天数可从83天提升至111天。

支持TrustZone及国密1级认证/国密算法SM2/3/4安全，实现更加安全可信。V8850平台引入TrustZone技术，增强安全启动，安全传输的基础安全能力，支持安全升级、安全调试、安全隔离、安全存储和设备可信认证的系统级安全。V8850平台采用紫光展锐自研安全IP，可应用在支付、区块链、 物流、工业互联主动标识等行业场景。

### 关键参数

* Cortex-A7


## [资源收录](https://github.com/SoCXin)

* [参考资源](src/)
* [参考文档](docs/)
* [参考工程](project/)

## [选型建议](https://github.com/SoCXin/V8850)

Cat.4速率更高，上行最高50Mbps、下行最高150Mbps的，但在功耗、集成度、价格方面很难满足部分行业的物联网应用需求，而Cat.1兼顾制式、性能、功耗、成本等优势，尤其成本比Cat.4低近30%。


[V8850](https://github.com/SoCXin/V8850) 同类Cat.1bis竞品包括：

* [EC618](https://github.com/SoCXin/EC618)
* [ASR1606](https://github.com/SoCXin/ASR1606)

