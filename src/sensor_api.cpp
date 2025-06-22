#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "sensor_api.hpp"
#include "display_manager.hpp"

const char *GLOBAL_SENSOR_ID = "esp32-7355608";

void sendToSensorCommunity(
    const String &xPin,
    const String &softwareVersion,
    const std::vector<std::pair<String, String>> &dataValues)
{
    if (WiFi.status() != WL_CONNECTED)
    {
        DisplayManager::log("WiFi not connected.");
        return;
    }

    HTTPClient http;
    http.begin("http://api.sensor.community/v1/push-sensor-data/");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("X-Sensor", GLOBAL_SENSOR_ID);
    http.addHeader("X-Pin", xPin);

    JsonDocument doc;
    doc["software_version"] = softwareVersion;
    JsonArray array = doc["sensordatavalues"].to<JsonArray>();

    for (const auto &pair : dataValues)
    {
        JsonObject obj = array.add<JsonObject>();
        obj["value_type"] = pair.first;
        obj["value"] = pair.second;
    }

    String jsonPayload;
    serializeJson(doc, jsonPayload);

    DisplayManager::log("Payload: " + jsonPayload);
    int httpCode = http.POST(jsonPayload);

    if (httpCode > 0)
    {
        DisplayManager::log("Sent (" + String(httpCode) + ")");
    }
    else
    {
        DisplayManager::log("Send error: " + http.errorToString(httpCode));
    }

    http.end();
}
