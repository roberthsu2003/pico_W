/*
 * g = digital 9
 * f = digital 8
 * e = digital 7
 */
byte pins[] = {9, 8, 7, 6, 5, 4, 3}; //g,f,e,d,c,b,a
byte pinCount = 7;

/*
 * numbers[10]內儲存的顯示數值依序是0,1,2,3,4,5,6,7,8,9
 * B01111110代表的是要顯示數值，
 * 最後的0代表的是g要輸出0
 * 倒數第2個值是1,是f要輸出1
 */
byte numbers[10] = {B01111110,B00110000,B01101101,B01111001,B00110011,B01011011,B01011111,B01110000,B01111111,B01111011};

void setup() {
  Serial.begin(9600);
  for(int i=0;i<pinCount;i++){
    pinMode(pins[i],OUTPUT);
  }
  
}

void loop() {
  
  //Serial.println(numbers[0]);
  //Serial.println(bitRead(numbers[0],6));
  
  for(int i=0;i<10;i++){
    for(int j=0; j<=6; j++){
      bool state = bitRead(numbers[i],j); //j是0,代表抓最右邊的數值
      digitalWrite(pins[j],state);
    }
    delay(1000);
  }  
}
