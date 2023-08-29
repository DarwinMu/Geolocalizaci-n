/*
  Daniel Carrasco
  This and more tutorials at https://www.electrosoftcloud.com/
*/
#include <esp_now.h>
#include <WiFi.h>
// Set the SLAVE MAC Address

#include <TinyGPS++.h>

#define RXD2 16
#define TXD2 17

int mes,dia,anio,altur,hora,minuto,segundo;
float latit,longi,gpvel;
TinyGPSPlus gps;
 const byte ledON =10;
 int ledRX=7;
  int ledGPS=8;
int i;

uint8_t slaveAddress[] = {0x08, 0x3A, 0xF2, 0xA9, 0xDB, 0xAC};
// Structure to keep the temperature and humidity data from a DHT sensor
typedef struct temp_humidity {
  float temperature;
  float humidity;
};
// Create a struct_message called myData
temp_humidity dhtData;
// Callback to have a track of sent messages
void OnSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nSend message status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Sent Successfully" : "Sent Failed");
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  pinMode(ledON,OUTPUT);
  pinMode(ledGPS,OUTPUT);
 pinMode(ledRX,OUTPUT);
  for(i=1;i<=30;i++){
    digitalWrite(ledON,HIGH);
    delay(100);
    digitalWrite(ledON,LOW);
    digitalWrite(ledRX,HIGH);
    delay(100);
    digitalWrite(ledRX,LOW);
    digitalWrite(ledGPS,HIGH);
    delay(100);
    digitalWrite(ledGPS,LOW);
  }
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("There was an error initializing ESP-NOW");
    return;
  }
  // We will register the callback function to respond to the event
  esp_now_register_send_cb(OnSent);
  
  // Register the slave
  esp_now_peer_info_t slaveInfo;
  memcpy(slaveInfo.peer_addr, slaveAddress, 6);
  slaveInfo.channel = 0;  
  slaveInfo.encrypt = false;
  
  // Add slave        
  if (esp_now_add_peer(&slaveInfo) != ESP_OK){
    Serial.println("There was an error registering the slave");
    return;
  }

   
}
void loop() {
digitalWrite(ledON,HIGH);
  latit=gps.location.lat(), gps.location.isValid(), 11, 6;
longi=gps.location.lng(), gps.location.isValid(), 12, 6;

Serial.print(" LAT:");
Serial.print(latit,6);
Serial.print(" Longi:");
Serial.print(longi,6);
Serial.println("");
Serial.println("");
  // Set values to send
  // To simplify the code, we will just set two floats and I'll send it 
  dhtData.temperature = longi*1000000;
  dhtData.humidity = latit*1000000;
  // Is time to send the messsage via ESP-NOW
  esp_err_t result = esp_now_send(slaveAddress, (uint8_t *) &dhtData, sizeof(dhtData));
   
  if (result == ESP_OK) {
    Serial.println("The message was sent sucessfully.");
  }
  else {
    Serial.println("There was an error sending the message.");
  }
  smartDelay(1000);
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (Serial2.available())
      gps.encode(Serial2.read());
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
