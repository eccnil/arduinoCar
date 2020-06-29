#include <Arduino.h>
#include "common_esp_now.h"


void onRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
             mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4],
             mac_addr[5]);
    Serial.print("Last Packet Recv from: ");
    Serial.println(macStr);
    Serial.print("Last Packet Recv Data: ");
    // if it could be a string, print as one
    if (data[data_len - 1] == 0)
        Serial.printf("%s\n", data);
    // additionally print as hex
    for (int i = 0; i < data_len; i++) {
        Serial.printf("%x ", data[i]);
    }
    Serial.println("");
}

void setup(){
    Serial.begin(115200);
    Serial.println("ESPNow receiver Demo");

#ifdef ESP8266
    WiFi.mode(WIFI_STA); // MUST NOT BE WIFI_MODE_NULL
#elif ESP32
    WiFi.mode(WIFI_MODE_STA);
#endif

    ESPNow.set_mac(MAC_MANDO);
    WiFi.disconnect();
    ESPNow.init();
    ESPNow.reg_recv_cb(onRecv);
}
 
void loop(){
    yield();
}