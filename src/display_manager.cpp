#include "display_manager.hpp"
#include "heltec.h"

namespace DisplayManager
{

    const int maxLines = 6;
    String lines[maxLines];
    int lineIndex = 0;

    void init()
    {
        Heltec.begin(true /*DisplayEnable*/, false /*LoRaEnable*/, true /*SerialEnable*/);
        Heltec.display->clear();
        Heltec.display->display();
    }

    void clear()
    {
        for (int i = 0; i < maxLines; i++)
            lines[i] = "";
        lineIndex = 0;
        Heltec.display->clear();
        Heltec.display->display();
    }

    void log(const String &message)
    {
        lines[lineIndex] = message;
        lineIndex = (lineIndex + 1) % maxLines;

        Heltec.display->clear();
        for (int i = 0; i < maxLines; i++)
        {
            int index = (lineIndex + i) % maxLines;
            if (lines[index].length() > 0)
            {
                Heltec.display->drawString(0, i * 10, lines[index]);
            }
        }
        Heltec.display->display();

        Serial.println(message);
    }
}
