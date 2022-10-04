# 上拉電阻
## 學習何時使用上拉電阻

- ### 按鈕使用上拉電阻,PIN12接收訊號的說明圖

![](button02.png)



### 線路圖
![上拉電阻線路圖](上拉電阻_bb.jpg)

### 實體線路圖
![成品](IMG_0372.jpg)

### 上拉電阻接線
[![上拉電阻成品展示](https://img.youtube.com/vi/y28I-Kwlljg/2.jpg)](https://youtu.be/y28I-Kwlljg)

### 上拉電阻成品展示
[![上拉電阻成品展示](https://img.youtube.com/vi/_LYhqSXSdy8/1.jpg)](https://youtu.be/_LYhqSXSdy8)



```C++
#define btn 2
#define led 13

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(btn, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorVal = digitalRead(btn);
  if(sensorVal == LOW)
    digitalWrite(led,HIGH);
  else
    digitalWrite(led,LOW);
}
```

