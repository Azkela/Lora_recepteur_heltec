#include <Arduino.h>
#include <ArduinoJson.h>
#include "heltec.h"

#include "display_manager.hpp"
#include "sensor_api.hpp"
#include "variables.hpp"

#define BAND LORA_BAND

void initLoRa()
{
    Heltec.begin(true /*DisplayEnable*/, true /*LoRaEnable*/, true /*SerialEnable*/, true /*PABOOST*/, BAND);

    LoRa.setSpreadingFactor(7);
    LoRa.setSyncWord(0x34);
    LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);

    DisplayManager::log("LoRa initialisé");
}

void processIncomingLoRaMessage()
{
    int packetSize = LoRa.parsePacket();
    if (packetSize == 0)
        return;

    String payload = "";
    while (LoRa.available())
        payload += (char)LoRa.read();

    Serial.println("Received: " + payload);
    DisplayManager::log("Reçu: " + payload);

    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, payload);
    if (err)
    {
        DisplayManager::log("Erreur JSON");
        return;
    }

    if (!doc["groupID"].is<const char *>() || String(doc["groupID"].as<const char *>()) != "MAR-2")
    {
        DisplayManager::log("GroupID ignoré");
        return;
    }

    float temperature = doc["temperature"] | -1.0;
    float humidity = doc["humidity"] | -1.0;
    float pressure = doc["pressure"] | -1.0;
    float dust_v = doc["dust_v"] | -1.0;
    float sound_db = doc["sound_db"] | -1.0;

    if (temperature > 0.1 || humidity > 0.1 || pressure > 0.1)
    {
        sendToSensorCommunity(
            PIN_BME280,
            "esp32_bme280_1.0",
            {{"temperature", String(temperature, 2)},
             {"humidity", String(humidity, 2)},
             {"pressure", String(pressure, 2)}});
    }
    else
    {
        DisplayManager::log("BME280: données invalides");
    }

    if (dust_v > 0.01)
    {
        sendToSensorCommunity(
            PIN_GP2Y1010,
            "esp32_gp2y1010_1.0",
            {{"P1", String(dust_v, 3)}});
    }
    else
    {
        DisplayManager::log("GP2Y1010: donnée invalide");
    }

    if (sound_db > 0.01)
    {
        sendToSensorCommunity(
            PIN_INMP441,
            "esp32_inmp441_1.0",
            {{"noise_LAeq", String(sound_db, 2)}});
    }
    else
    {
        DisplayManager::log("INMP441: donnée invalide");
    }
}
