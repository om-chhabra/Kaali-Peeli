void setup2(){
  pinMode(15, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  I2C.begin(SDA_PIN, SCL_PIN, 400000);
  Wire.begin(21,22);

  if(!display1.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    for(;;); // Don't proceed, loop forever
  }
  
  //START THE OLED COMMUNICATION 
  display.begin(0X3C, true);
  delay(2000);
  display.clearDisplay();
  display.display();
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);

  display1.clearDisplay();
  display1.setTextSize(2);
  display1.setTextColor(SSD1306_WHITE);
  display1.display();
}

void fareSetup(){
  
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Start ?");
  display.display();
  
  while (startStopFare == 0){
    pushButtonValue = digitalRead(15);
    
    if (pushButtonValue == LOW){
      startStopFare = 1;
      digitalWrite(2, HIGH);
      display.setCursor(0,30);
      display.println("Started");
      display.display();
      pushButtonValue = HIGH;
    }
  }
}

void meterOnOff(){
  pushButtonValue = digitalRead(15);
    if (pushButtonValue == LOW){
      startStopFare = (1 - startStopFare);
      digitalWrite(2,startStopFare);
      totalDistance = 0;
      
      while(pushButtonValue == LOW){
        pushButtonValue = digitalRead(15);
      } 
    }
}
