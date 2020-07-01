#include <Arduino.h>
#include "common_esp_now.h"
#include "rgbled.hpp"
#include "joystick.hpp"

//ref: https://randomnerdtutorials.com/esp-now-esp32-arduino-ide/

#define RED_PIN 27
#define GREEN_PIN 26
#define BLUE_PIN 25
#define RGB_LED_COMMON_ANODE true
#define JOY_X 34
#define JOY_y 35
#define JOY_BTN 32

struct_message data;
RGBLed led (RED_PIN, GREEN_PIN, BLUE_PIN, RGB_LED_COMMON_ANODE);
Joystick joy(JOY_X, JOY_y, JOY_BTN);
bool clicked = false;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    //Serial.print("\r\nLast Packet Send Status:\t");
    //Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
    if(status == ESP_NOW_SEND_SUCCESS ){
        led.setGreen();
    } else {
        led.setYellow();
    }
}

// callback de boton pulsado
auto onclick = []() { 
  clicked = true;
};

// callback de boton muy pulsado
auto onLongClick = []() { 
  led.setWhite();
  delay(100);
};

void setup(){
    led.setCyan();
    //Initialize ESP-NOW;
    //You must initialize Wi-Fi before initializing ESP-NOW.
#ifdef ESP8266
    WiFi.mode(WIFI_STA); // MUST NOT BE WIFI_MODE_NULL
#elif ESP32
    WiFi.mode(WIFI_MODE_STA);
#endif
    if (esp_now_init() != ESP_OK) { //Initializes ESP-NOW. 
        //"Error initializing ESP-NOW" red-blue
        for(int i=10; i; i--){
            led.setRed();
            delay(200);
            led.setBlue();
            delay(200);
        }
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
        //Failed to add peer" --> red - magenta
        for(int i=10; i; i--){
            led.setRed();
            delay(200);
            led.setMagenta();
            delay(200);
        }
        return;
    }

    //init joystick
    joy.setup();
    joy.setOnClick(onclick);
    joy.setOnLongClick(onLongClick);
}
 
void loop(){
    joy.loop();

    data.x = joy.getX();
    data.y = joy.getY();
    data.e = clicked;
    clicked=false;  

    //Send a message to the peer device.
    if (ESP_OK != esp_now_send(MAC_RECEPTOR, (uint8_t*) &data, sizeof(data))){
        //Error sending the data -> red
        led.setRed();
    }


    delay(50);
}