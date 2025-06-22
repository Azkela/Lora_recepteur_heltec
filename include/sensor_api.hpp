#pragma once
#include <Arduino.h>
#include <vector>

void sendToSensorCommunity(
    const String &xPin,
    const String &softwareVersion,
    const std::vector<std::pair<String, String>> &dataValues);
