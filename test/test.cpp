#include <SPI.h>
#include <LoRa.h>

#define SS 18
#define RST 14
#define DI0 26

void setup() {
    Serial.begin(115200);
    while (!Serial);

    Serial.println("LoRa Receiver");

    LoRa.setPins(SS, RST, DI0);
    if (!LoRa.begin(868E6)) {
        Serial.println("Erreur de démarrage LoRa !");
        while (1);
    }

    Serial.println("LoRa en écoute..."); 
    LoRa.receive(); 
}

void loop() {
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        Serial.print("Message reçu : ");
        while (LoRa.available()) {
            Serial.print((char)LoRa.read());
        }
        Serial.println();
        LoRa.receive(); 
    }
}
