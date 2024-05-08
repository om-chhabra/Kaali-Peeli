void fixGps(){
  gpsFix = gps.location.isValid();

  while(gpsFix==0){
    if (Serial2.available() > 0) {
      if (gps.encode(Serial2.read())) {
        gpsFix = gps.location.isValid();
        display.clearDisplay();
        display.setCursor(0,0);
        display.println("Gps fix: ");
        display.display();
      }
    }
  }
  display.setCursor(0,30);
  display.println("Done");
  display.display();
}
