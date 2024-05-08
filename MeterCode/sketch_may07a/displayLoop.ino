void displayAll(){
  display.setTextSize(2);
  display1.setTextSize(2);
  
  display.clearDisplay();
  display1.clearDisplay();

  display.setCursor(0,25);
  display.print(totalDistance);
  display.println(" m");
        
  display.setCursor(0,0);
  display.print("Rs. ");
  display.println(fareValue);

  display.setCursor(0,45);
  display.print(speedMps);
  display.println(" m/s");
  

  display1.setCursor(0,0);
  display1.print(gpsHour);
  display1.print(":");
  display1.print(gpsMinute);
  display1.print(":");
  display1.println(gpsSecond);

  display.display();
  display1.display();
}
