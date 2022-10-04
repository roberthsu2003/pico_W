void setup(){  
  Serial.begin(9600);
  while (!Serial);
  Serial.println("歡迎來到Arduino");
}

void loop(){
  //Serial.available()會算出目前在buffer內有多少byte的資料
  if(Serial.available()){
    //Serial.read()會讀取第一個byte內的資料,讀取完畢後,buffer內的資料就被刪除。
    //傳送來的資料是char
    Serial.println(Serial.read());    
  }
}
