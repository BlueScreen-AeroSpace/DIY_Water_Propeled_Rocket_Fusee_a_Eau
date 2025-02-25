#pragma once
#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFiClient.h>
#include "Modules/BMP280Sensor.h"
#include "Modules/ADXL345Sensor.h"
#include "Managers/SpeedManager.h"
#include "SensorDiscovery.h"
#include "Managers/JsonManager.h"
#include "config.h"
#include "const.h"
#include "Rocket.h"

class MQTT_Service {
private:
    WiFiClient* m_espClient;
    PubSubClient* m_pubSubClient;
    String m_espUnique;
    uint64_t m_lastSentMessageTime;
    uint16_t m_interval;
    BMP280Sensor* m_BMP280Sensor;
    ADXL345Sensor* m_ADXL345Sensor;
    SpeedManager* m_speedManager;
    SensorDiscovery* m_sensorDiscovery;
    JSONManager* m_jsonManager;
    Rocket* m_rocket;


    const char* m_hassServer;
    uint16_t m_hassPort;
    String m_hassUser;
    String m_hassPass;
    bool m_discoverySent;
    void setupMQTT();
    bool reconnectMQTTIfNeeded();
    void publishData();    
    void listenBroadcast();
    void toggleReadyToLaunch(String p_payload);
public:
    MQTT_Service(
        BMP280Sensor* p_BMP280Sensor,
        ADXL345Sensor* p_ADXL345Sensor,
        SpeedManager* p_speedManager,
        const char* p_hassServer,
        uint16_t p_hassPort,
        String p_hassUser,
        String p_hassPass,
        JSONManager* p_jsonManager,
        Rocket* m_rocket
        );   
    void tick();
};