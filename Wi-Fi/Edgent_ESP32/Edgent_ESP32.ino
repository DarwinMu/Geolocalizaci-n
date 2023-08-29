#define BLYNK_TEMPLATE_ID "TMPLuI5XkoLY"
#define BLYNK_DEVICE_NAME "COMUNICACIÓN WIFI"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7
//#define USE_ESP32C3_DEV_MODULE
//#define USE_ESP32S2_DEV_KIT

#include "BlynkEdgent.h"


 String slatit,slongi;
float flatit,flongi;
String str, ID;
 float lat = -1.491380;
  float lon = -78.562643;

float limlatma=lat+0.001;
float limlamen=lat-0.001;
  int i,cont;
  WidgetLED led1(V1);
  WidgetLED led2(V2);
BlynkTimer timer; 
void setup()
{
  Serial.begin(115200);
   Serial2.begin(115200);
 

  BlynkEdgent.begin();
 //timer.setInterval(1000L, blinkLedWidget);
}

void loop() {
  BlynkEdgent.run();
  leercom();
}


void leercom(){
   if (Serial2.available()) {
    str = Serial2.readStringUntil('\n');
    ID=str.substring(0,3); 
   
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
     //lat=flatit;
     //lon=flongi;
//     cont=cont+1;
//     if(cont==100)
//     {
//    GPSDataSend();
//     cont=0;
//     }
    //imprimirdatos();
     GPSDataSend();
}
}
void GPSDataSend()
{

  Blynk.virtualWrite(V13, String(flatit, 6), String(flongi, 6));
  Blynk.virtualWrite(V5, lat);
  Blynk.virtualWrite(V3, lon);
  
  if(lat<limlatma || lat>limlamen)
  {
    led2.on();
     Blynk.virtualWrite(V4, "FUERA DE LIMITE");
 
  }else
  {
    led2.off();
    
    Blynk.virtualWrite(V4, " OK");
  }
}

void blinkLedWidget()
{
 
  if (led1.getValue()) {
    led1.off();

  } else {
    led1.on();
  
  }
}
void imprimirdatos()
{
  Serial.print("ID: ");
  Serial.print(ID);
  Serial.print(" Latitud: ");
  Serial.print(flatit,6);
  Serial.print(" Longitud: ");
  Serial.print(flongi,6);

}
