#pragma once
#include <PubSubClient.h>
#include "const.h"

class SensorDiscovery {
private:
PubSubClient* m_pubSubClient;
private:
    void createHASSTempSensorViaMSGDiscovery();
    void createHASSPressureSensorViaMSGDiscovery();
    void createHASSSpeedSensorViaMSGDiscovery();
    void createHASSButtonViaMSGDiscovery();
public:
    SensorDiscovery(PubSubClient* p_pubsubClient);
    void createSensorsViaMSGDiscovery();
};