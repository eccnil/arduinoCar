#ifndef _common_esp_now_h_
#define _common_esp_now_h_

#include <Arduino.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <espnow.h>
#elif ESP32
#include <WiFi.h>
#include <esp_now.h>
#endif

//https://platformio.org/lib/show/6122/ESPNowW/examples

uint8_t MAC_MANDO[] = { 0x24, 0x0A, 0xC4, 0x5D, 0x28, 0x80}; //hat
uint8_t MAC_RECEPTOR[] = { 0x24, 0x62, 0xAB, 0xE7, 0x6F, 0xB0}; //lora

typedef struct struct_message {
  int x;
  int y;
  bool e;
} struct_message;

#endif