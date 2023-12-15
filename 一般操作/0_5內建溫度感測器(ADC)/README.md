## 內建溫度感測器(ADC)
- ADC為12-bit(0~4095)
- RP2024提供5個ADC(channel 0~4)
- GP26,GP27,GP28->一般使用
- GP29->可以測量目主機版電壓(VSYS)
- 最後一個為溫度感測器專用

### 線路圖

![](./images/pic1.png)

```
From machine import ADC
```


### 使用GPIO連線 
- GP26

```
adc = machine.ADC(26) # Connect to GP26, which is channel 0
```


### 使用channel連線

###

```
adc = machine.ADC(4) # Connect to the internal temperature sensor adc = machine.ADC(0) # Connect to channel 0 (GP26)
```



