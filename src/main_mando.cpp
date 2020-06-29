#include <Arduino.h>
#include "common_esp_now.h"

struct_message data;

void setup(){
   Serial.begin(115200);
   Serial.println();

#ifdef ESP8266
    WiFi.mode(WIFI_STA); // MUST NOT BE WIFI_MODE_NULL
#elif ESP32
    WiFi.mode(WIFI_MODE_STA);
#endif

   ESPNow.init();
   ESPNow.add_peer(MAC_RECEPTOR);
   data.x = 0;
   data.y = 0;
   data.e = 0;
}
 
void loop(){
    delay(100);
    ESPNow.send_message(MAC_RECEPTOR, (uint8_t *) &data, sizeof(data));
    data.x ++;
    Serial.println(data.x);
}