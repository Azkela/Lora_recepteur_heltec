#include <Arduino.h>
#include "wifi_manager.h"
#include "sensor_api.hpp"
#include "display_manager.hpp"
#include "variables.hpp"

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
      PIN_BME280,
      "esp32_bme280_1.0",
      {{"temperature", "23.7"},
       {"humidity", "49.8"},
       {"pressure", "1014.2"}});

  sendToSensorCommunity(
      PIN_GP2Y1010,
      "esp32_gp2y1010_1.0",
      {{"P1", "18.5"}});

  sendToSensorCommunity(
      PIN_INMP441,
      "esp32_inmp441_1.0",
      {{"P2", "62.4"}});
}

void loop()
{
}
