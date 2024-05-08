void publishMessage(){
  StaticJsonDocument<200> doc;
  
  doc["ID"] = id;
  doc["Type"] = vehicleType;
  doc["Latitude"] = currentLat;
  doc["Longitude"] = currentLon;
  
  if(startStopFare == 1){
    doc["Speed"] = speedMps;
    doc["Distance"] = totalDistance;
    doc["Fare"] = fareValue;
  }
  
  doc["Timestamp"] = timestamp;
  
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}
