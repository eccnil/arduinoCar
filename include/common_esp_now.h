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

uint8_t MAC_MANDO[] = { 0x84, 0x0D, 0x8E, 0xA5, 0x83, 0x07}; //hat
uint8_t MAC_RECEPTOR[] = { 0xA4, 0xCF, 0x12, 0x25, 0x9D, 0xC4}; //lora

typedef struct struct_message {
  int x;
  int y;
  bool e;
} struct_message;

#endif