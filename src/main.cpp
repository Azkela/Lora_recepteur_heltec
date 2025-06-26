#include <Arduino.h>
#include "wifi_manager.h"
#include "sensor_api.hpp"
#include "display_manager.hpp"
#include "lora_manager.hpp"
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

  initLoRa();
}

void loop()
{
  processIncomingLoRaMessage();
  delay(1000);
}
