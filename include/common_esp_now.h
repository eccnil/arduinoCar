#ifndef _common_esp_now_h_
#define _common_esp_now_h_

#include <Arduino.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif ESP32
#include <WiFi.h>
#endif
#include "ESPNowW.h"

//https://platformio.org/lib/show/6122/ESPNowW/examples

uint8_t MAC_MANDO[] = { 0x84, 0x0D, 0x8E, 0xA5, 0x83, 0x07};
uint8_t MAC_RECEPTOR[] = { 0x84, 0x0D, 0x8E, 0x39, 0xB5, 0xAC};

typedef struct struct_message {
  int x;
  int y;
  bool e;
} struct_message;

#endif