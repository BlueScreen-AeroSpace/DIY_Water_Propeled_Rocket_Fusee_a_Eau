#include "SensorDiscovery.h"

SensorDiscovery::SensorDiscovery(PubSubClient *p_pubSubClient) : m_pubSubClient(p_pubSubClient) { ; }

void SensorDiscovery::createHASSTempSensorViaMSGDiscovery()
{
    const char *payloadTemperature =
        "{"
        "\"name\": \"ESP32 Temperature\", "
        "\"state_topic\": \"homeassistant/sensor/bmp280/temperature\", "
        "\"unit_of_measurement\": \"°C\", "
        "\"device_class\": \"temperature\", "
        "\"icon\": \"mdi:thermometer\", "
        "\"unique_id\": \"bmp280_temperature_001\", "
        "\"payload_available\": \"online\", "
        "\"payload_not_available\": \"offline\""
        "}";

    m_pubSubClient->publish(TEMP_DISCOVERY_TOPIC, payloadTemperature, true);
}

void SensorDiscovery::createHASSPressureSensorViaMSGDiscovery()
{
    const char *payloadPressure =
        "{"
        "\"name\": \"ESP32 Pressure\", "
        "\"state_topic\": \"homeassistant/sensor/bmp280/pression\", "
        "\"unit_of_measurement\": \"hPa\", "
        "\"device_class\": \"pressure\", "
        "\"icon\": \"mdi:gauge\", "
        "\"unique_id\": \"bmp280_pressure_001\", "
        "\"payload_available\": \"online\", "
        "\"payload_not_available\": \"offline\""
        "}";

    m_pubSubClient->publish(PRESSURE_DISCOVERY_TOPIC, payloadPressure, true);
}

void SensorDiscovery::createHASSSpeedSensorViaMSGDiscovery()
{
    const char *payloadSpeed =
        "{"
        "\"name\": \"ESP32 Speed\", "
        "\"state_topic\": \"homeassistant/sensor/esp32_speed\", "
        "\"unit_of_measurement\": \"m/s\", "
        "\"device_class\": \"speed\", "
        "\"icon\": \"mdi:speedometer\", "
        "\"unique_id\": \"esp32_speed_001\", "
        "\"payload_available\": \"online\", "
        "\"payload_not_available\": \"offline\""
        "}";

    m_pubSubClient->publish(SPEED_DISCOVERY_TOPIC, payloadSpeed, true);
}

void SensorDiscovery::createHASSButtonViaMSGDiscovery() {
    const char *payloadButton =
        "{"
        "\"name\": \"Rocket launcher\", "
        "\"state_topic\": \"homeassistant/switch/launch\", "
        "\"device_class\": \"switch\", "
        "\"icon\": \"mdi:speedometer\", "
        "\"unique_id\": \"esp32_rocket_launcher\", "
        "\"payload_available\": \"online\", "
        "\"payload_not_available\": \"offline\""
        "}";
        Serial.println(payloadButton);
    m_pubSubClient->publish(SPEED_DISCOVERY_TOPIC, payloadButton, true);
}

void SensorDiscovery::createSensorsViaMSGDiscovery()
{
    this->createHASSTempSensorViaMSGDiscovery();
    this->createHASSPressureSensorViaMSGDiscovery();
    this->createHASSSpeedSensorViaMSGDiscovery();
    this->createHASSButtonViaMSGDiscovery();
}
