float lat,lon;

#include <esp_now.h>
#include <WiFi.h>
float latit,longi,gpvel;
String Slat="";
String Slon="";
#define RXD2 16
#define TXD2 17

// Structure to keep the temperature and humidity data
// Is also required in the client to be able to save the data directly
typedef struct temp_humidity {
  float temperature;
  float humidity;
  
};
// Create a struct_message called myData
temp_humidity dhtData;
// callback function executed when data is received
void OnRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {

  lat=dhtData.temperature/1000000;
  lon=dhtData.humidity/1000000;
  memcpy(&dhtData, incomingData, sizeof(dhtData));
 

  Slat="Lat:";                          
Slat+=lat*1000000; 
Slon="Lon:";
Slon+=lon*1000000;
Serial.print("Latitud: ");
Serial.print(Slat);
Serial.print("Longitud: ");
Serial.println(Slon);
Serial2.println(Slat);
Serial2.println(Slon);
}
void setup() {
  // Initialize Serial Monitor
 Serial.begin(115200);
   Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("There was an error initializing ESP-NOW");
    return;
  }
  
  // Once the ESP-Now protocol is initialized, we will register the callback function
  // to be able to react when a package arrives in near to real time without pooling every loop.
  esp_now_register_recv_cb(OnRecv);
}
void loop() {
}
