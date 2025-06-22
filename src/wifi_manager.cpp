#include <WiFi.h>
#include "wifi_manager.h"
#include "variables.hpp"
#include "display_manager.hpp"

void connectToWiFi()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    DisplayManager::log("Connexion WiFi...");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    DisplayManager::log("WiFi connecte !");
    DisplayManager::log("IP: " + WiFi.localIP().toString());
}
