#include <Arduino.h>
#include "common_esp_now.h"

//ref: https://randomnerdtutorials.com/esp-now-esp32-arduino-ide/

struct_message data;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup(){
   Serial.begin(115200);
   Serial.println();

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

    //Register a callback function upon sending data – the OnDataSent function will be executed when a message is sent. This can tell us if the message was successfully delivered or not;
    esp_now_register_send_cb(OnDataSent);

    //Add a peer device (the receiver). For this, you need to know the the receiver MAC address;
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, MAC_RECEPTOR, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    if(esp_now_add_peer(&peerInfo) != ESP_OK){
        Serial.println("Failed to add peer");
        return;
    }
    
}
 
void loop(){
    data.x ++;
    data.y = random(10,20);
    data.e = false;

    //Send a message to the peer device.
    esp_err_t result = esp_now_send(MAC_RECEPTOR, (uint8_t*) &data, sizeof(data));
    if (result == ESP_OK) {
        Serial.println("Sent with success");
    }
    else {
        Serial.println("Error sending the data");
    }

    delay(1000);
}