#define dataPin 2
#define latchPin 3
#define clockPin 4

/*
 * numbers[10]內儲存的顯示數值依序是0,1,2,3,4,5,6,7,8,9
 * B01111110代表的是要顯示數值，
 * 最後的0代表的是g要輸出0
 * 倒數第2個值是1,是f要輸出1
 */
byte numbers[10] = {B01111110,B00110000,B01101101,B01111001,B00110011,B01011011,B01011111,B01110000,B01111111,B01111011};
byte i = 0;

void setup() {
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
}

void loop() {
  digitalWrite(latchPin,LOW); //關閉閘門
  //以序列方式傳進74595
  shiftOut(dataPin,clockPin,LSBFIRST,numbers[i]);
  digitalWrite(latchPin,HIGH); //開啟閘門

  delay(1000);
  i++;
  if(i == 10){
    i = 0;
  }
}
