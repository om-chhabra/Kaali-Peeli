/**********************************LIBRARIES**********************************/
//WIFI PLUS AWS
#include "secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"

//GPS LIBRARY
#include <TinyGPS++.h>

//LIBRARIES FOR OLED DISPLAY
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_SSD1306.h>


/**********************************DEFINITIONS**********************************/
#define AWS_IOT_PUBLISH_TOPIC   "meter/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "meter/sub"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define SDA_PIN 18
#define SCL_PIN 5


/**********************************OBJECTS**********************************/
TinyGPSPlus gps;
WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);
TwoWire I2C = TwoWire(1);
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_SSD1306 display1(128,32,&I2C,4);


/**********************************VARIABLES**********************************/
int period = 5000;
unsigned long time_now = 0;

String id = "MH048";
String vehicleType = "Auto";
double currentLat,currentLon;
double previousLat,previousLon;
int gpsHour,gpsMinute,gpsSecond;
double speedMps;
char timestamp[50];

bool gpsFix;
bool startStopFare = 0;
bool pushButtonValue;

double totalDistance = 0;
double distance;

//FARE CALCULATIONS
float kmDistance;
float difference;
float variableReference = 1.5;
int fareValue = 23;

/**********************************declarations**********************************/
void setup2();
void fixGps();
void connectWifi();
void convertUTCtoIST();
void connectAWS();
void fareSetup();
void publishMessage();
void getGpsValues(); 
void getDistance();
void fareCalculator();
void displayAll();
void meterOnOff();


/**********************************SETUP()**********************************/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
  
  //OLED,GPS FIX AND LED+PUSHBUTTON SETUP HERE
  setup2();

  fixGps();
  delay(3000);
  
  connectWifi();
  delay(3000);
  connectAWS();
  delay(10000);

  // START FARE SETUP HERE
  fareSetup();
  delay(3000);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  if(startStopFare == 1){
      getGpsValues(); 
      getDistance();
      previousLat = currentLat;
      previousLon = currentLon;
      fareCalculator();
      displayAll();
  }
  
  if(millis() >= time_now + period){
    time_now += period;
    publishMessage();
    client.loop();
  }
  
  meterOnOff();
}
