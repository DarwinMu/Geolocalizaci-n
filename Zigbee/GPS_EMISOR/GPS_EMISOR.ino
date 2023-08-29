#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 10, TXPin = 11;
static const uint32_t GPSBaud = 9600;
int mes,dia,anio,altur,hora,minuto,segundo;
float latit,longi,gpvel;
String Slat="";
String Slon="";
int ledON=9;
int ledGPS=8;
int ledTX=7;
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);
  pinMode(ledON,OUTPUT);
  pinMode(ledGPS,OUTPUT);
  pinMode(ledTX,OUTPUT);
  digitalWrite(ledGPS,LOW);
}

void loop()
{
digitalWrite(ledON,HIGH);
latit=gps.location.lat(), gps.location.isValid(), 11, 6;
longi=gps.location.lng(), gps.location.isValid(), 12, 6;
altur=gps.altitude.meters();
gpvel=gps.speed.kmph();

Slat="Lat:";                          
Slat+=latit*1000000; 
Slon="Lon:";
Slon+=longi*1000000;

if(longi<-1){
  digitalWrite(ledGPS,HIGH);
}
digitalWrite(ledTX,HIGH);
Serial.println(Slat);
Serial.println(Slon);
 digitalWrite(ledTX,LOW);
 smartDelay(1000);

}


static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    
    while (ss.available())
      gps.encode(ss.read()); 
  } while (millis() - start < ms);
 
  
}

static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartDelay(0);
}
