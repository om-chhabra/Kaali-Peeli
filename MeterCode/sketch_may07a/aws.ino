void connectWifi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Wifi");
  display.display();

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  } 

  display.setCursor(0,30);
  display.println("Wifi done");
  display.display();
}

void connectAWS(){
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
  client.setServer(AWS_IOT_ENDPOINT, 8883);
  
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("AWS");
  display.display();

  while (!client.connect(THINGNAME))
  {
    delay(100);
  }

  if (!client.connected())
  {
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Timeout");
    display.display();
    delay(5000);
    return;
  }

  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
  
  display.setCursor(0,30);
  display.println("AWS done");
  display.display();
}
