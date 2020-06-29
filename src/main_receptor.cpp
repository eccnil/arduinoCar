#include <Arduino.h>
#include "common_esp_now.h"

struct_message data;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&data, incomingData, sizeof(data));
  Serial.print("Bytes received: ");
  Serial.print(len);
  Serial.print(" - Int x: ");
  Serial.print(data.x);
  Serial.print(" - Int y: ");
  Serial.print(data.y);
  Serial.print(" - Boool e: ");
  Serial.print(data.e);
  Serial.println();
}

void setup(){
    Serial.begin(115200);
    Serial.println("ESPNow receiver Demo");

    //Initialize ESP-NOW;
    //You must initialize Wi-Fi before initializing ESP-NOW.
#ifdef ESP8266
    WiFi.mode(WIFI_STA); // MUST NOT BE WIFI_MODE_NULL
#elif ESP32
    WiFi.mode(WIFI_MODE_STA);
#endif
    if (esp_now_init() != ESP_OK) { //Initializes ESP-NOW. 
        Serial.println("Error initializing ESP-NOW");
        return;
    } 

    //Register for a receive callback function (OnDataRecv). This is a function that will be executed when a message is received.
    esp_now_register_recv_cb(OnDataRecv);
}
 
void loop(){
    yield();
}