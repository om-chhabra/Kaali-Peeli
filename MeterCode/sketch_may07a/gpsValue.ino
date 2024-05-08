void getGpsValues(){
  while (Serial2.available() > 0) {
    gps.encode(Serial2.read());
    if (gps.location.isUpdated()) {
      
      currentLat = gps.location.lat();
      currentLon = gps.location.lng();
      speedMps = (gps.speed.kmph())*1000/3600;
    }
    
    if(gps.time.isValid()){
         convertUTCtoIST();
      }
      
    }
}

void convertUTCtoIST(){
  gpsHour = gps.time.hour();
  gpsMinute = gps.time.minute();
  gpsSecond = gps.time.second();
  
  gpsHour += 5;
  gpsMinute += 30;
  
  if(gpsMinute >= 60){
    gpsMinute -= 60;
    gpsHour++;
  }

  if(gpsHour >= 24){
    gpsHour -= 24;
  }
  sprintf(timestamp,"%d:%d:%d",gpsHour,gpsMinute,gpsSecond);
}
