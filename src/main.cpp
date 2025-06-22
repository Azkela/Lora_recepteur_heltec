#include <Arduino.h>
#include "wifi_manager.h"
#include "sensor_api.hpp"

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;

  connectToWiFi();
  Serial.printf("Connected to WiFi");
  // Test : message brut JSON
  String testPayload = R"rawliteral(
{
  "sensordatavalues": [
    { "value_type": "temperature", "value": "23.4" }
  ]
}
)rawliteral";

  sendToSensorCommunityRawPayload(testPayload);
}

void loop()
{
  // vide pour le test
}
