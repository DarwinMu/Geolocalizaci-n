
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLfUpoOXJw"
#define BLYNK_DEVICE_NAME "Quickstart Template"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"
 const byte ledON =16;
 int ledRX=5;
 int buzzer=0;
 String slatit,slongi;
float flatit,flongi;
String str, ID;
 float lat = -0.108844;
  float lon = -78.470044;
BlynkTimer timer; 
void setup()
{
  Serial.begin(9600);
  delay(100);

  BlynkEdgent.begin();
  pinMode(ledON,OUTPUT);
  pinMode(buzzer,OUTPUT);
 pinMode(ledRX,OUTPUT);
 digitalWrite(buzzer,LOW);
 digitalWrite(ledON,HIGH);
  int buzzer=0;
}

void loop() {
  BlynkEdgent.run();
   timer.run();   
   digitalWrite(buzzer,LOW);

    if (Serial.available()) {
    str = Serial.readStringUntil('\n');
    ID=str.substring(0,3); 
    digitalWrite(ledRX,HIGH);
    if(ID=="Lon")
    {
      slongi=str.substring(4,13);
      flongi=slongi.toFloat()/1000000;
      
    }

    if(ID=="Lat")
    {
      slatit=str.substring(4,13);
      flatit=slatit.toFloat()/1000000;
    
  
    }
    digitalWrite(ledRX,LOW);
      Serial.print("Cadena: ");
      Serial.print(str);
      Serial.print("  :ID: ");
      Serial.print(ID);
      Serial.print(":    Longitud: ");
      Serial.print(flongi,6);
      Serial.print(":    Latitud: ");
      Serial.println(flatit,6);
   

 int pointIndex = 0;
  lon=lon+0.01;
  lat=lat+0,03;

  timer.setInterval(1000L, GPSDataSend); 
 // Blynk.virtualWrite(V4, lon, lat);
  }
}
BLYNK_WRITE(V5)
{
 int state=param.asInt(); 
 digitalWrite(ledON,state);
}
void GPSDataSend()
{
  Blynk.virtualWrite(V4, lon, lat);
}
