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

  String testPayload = R"rawliteral(
    {
      "sensordatavalues": [
        { "value_type": "temperature", "value": "23.4" }  
      ]
    }
    )rawliteral";

  DisplayManager::log("Envoi JSON...");
  sendToSensorCommunityRawPayload(testPayload);
  DisplayManager::log("Termine !");
}

void loop()
{
  static unsigned long last = 0;
  if (millis() - last > 10000)
  {
    last = millis();
    DisplayManager::log("Ping à " + String(millis() / 1000) + "s");
  }
}
