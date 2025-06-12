#include <Arduino.h>
#include <LoRa.h>

void setup() {
  Serial.begin(115200);
  while (!Serial);

  LoRa.setPins(18, 14, 26);
  if (!LoRa.begin(868E6)) {
    Serial.println("LoRa init failed.");
    while (1);
  }
  Serial.println("LoRa Receiver Ready");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String incoming = "";
    while (LoRa.available()) {
      incoming += (char)LoRa.read();
    }
    Serial.println("Received: " + incoming);
  }
}