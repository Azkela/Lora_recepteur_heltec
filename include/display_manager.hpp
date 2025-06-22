#pragma once
#include <Arduino.h>

namespace DisplayManager
{
    void init();
    void log(const String &message);
    void clear();
}
