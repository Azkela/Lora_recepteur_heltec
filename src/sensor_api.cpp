#include <WiFi.h>
#include <HTTPClient.h>
#include "sensor_api.hpp"
#include "display_manager.hpp"

// Remplace par l'ID unique de ton capteur
const char *SENSOR_ID = "esp32-4502E02F";

// void sendToSensorCommunity(const String &type, const String &value)
// {
//     if (WiFi.status() == WL_CONNECTED)
//     {
//         HTTPClient http;
//         http.begin("https://api.sensor.community/v1/push-sensor-data/");
//         http.addHeader("Content-Type", "application/json");
//         http.addHeader("X-Sensor", SENSOR_ID);

//         String payload = "{\"sensordatavalues\":[{\"value_type\":\"" + type + "\",\"value\":\"" + value + "\"}]}";
//         int httpResponseCode = http.POST(payload);

//         if (httpResponseCode > 0)
//         {
//             Serial.printf("Data sent. Response: %d\n", httpResponseCode);
//         }
//         else
//         {
//             Serial.printf("Error sending data: %s\n", http.errorToString(httpResponseCode).c_str());
//         }
//         http.end();
//     }
//     else
//     {
//         Serial.println("WiFi not connected, cannot send data.");
//     }
// }

void sendToSensorCommunityRawPayload(const String &jsonPayload)
{
    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;
        const char *SENSOR_ID = "esp8266-12345678";

        http.begin("https://api.sensor.community/v1/push-sensor-data/");
        http.addHeader("Content-Type", "application/json");
        http.addHeader("X-Sensor", SENSOR_ID);

        int httpResponseCode = http.POST(jsonPayload);

        if (httpResponseCode > 0)
        {
            DisplayManager::log("Data sent: " + String(httpResponseCode));
        }
        else
        {
            DisplayManager::log("Send error: " + http.errorToString(httpResponseCode));
        }

        http.end();
    }
    else
    {
        DisplayManager::log("WiFi not connected.");
    }
}
