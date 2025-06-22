#include <Arduino.h>
#include "wifi_manager.h"
#include "sensor_api.hpp"
#include "display_manager.hpp"

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;

  DisplayManager::init();
  DisplayManager::log("Demarrage...");

  connectToWiFi();
  DisplayManager::log("WiFi connecté");

  sendToSensorCommunity(
      "11",              
      "esp32_bme280_1.0",
      {
          {"temperature", "23.7"},
          {"humidity", "49.8"},
          {"pressure", "1014.2"}});

  sendToSensorCommunity(
      "5",
      "esp32_gp2y1010_1.0",
      {{"P1", "18.5"}});

  sendToSensorCommunity(
      "7",
      "esp32_inmp441_1.0",
      {{"P2", "62.4"}}
  );
}

void loop()
{
}
