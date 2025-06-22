#ifndef SENSOR_API_HPP
#define SENSOR_API_HPP

// Envoi structuré
void sendToSensorCommunity(const String &type, const String &value);

// ✅ Ajout pour l’envoi brut (JSON déjà formaté)
void sendToSensorCommunityRawPayload(const String &jsonPayload);

#endif // SENSOR_API_HPP
