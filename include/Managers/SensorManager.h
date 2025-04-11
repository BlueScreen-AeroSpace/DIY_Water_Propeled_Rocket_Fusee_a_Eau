#pragma once
#include <vector>
#include "Modules/Sensor.h"
#include <LittleFS.h>
#include <ArduinoJson.h>

class SensorManager
{
public:
    static constexpr uint8_t MAX_SENSORS = 3;
    SensorManager();
    void addSensor(Sensor *p_sensor);
    Sensor *getSensor(uint8_t p_ID);
    void toggleSensorState(uint8_t p_ID);
    const std::vector<Sensor *> &getSensors();
    std::vector<Sensor *> getActivatedSensors();

private:
    uint8_t m_sensorCount = 0;
    std::vector<Sensor *> m_sensors;
};
