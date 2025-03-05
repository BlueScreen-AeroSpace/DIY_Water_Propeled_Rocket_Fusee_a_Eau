#pragma once
#include "Modules/BMP280Sensor.h"

class SpeedManager {
private:
    BMP280Sensor* m_BMP280Sensor;
    float m_actualAltitude;
    float m_previousAltitude;
    float m_actualSpeed;
    float m_maxSpeed;
    uint16_t m_previousTime; 
    uint64_t m_interval;
    void computeSpeed();
    void setMaxSpeed();
public:
    SpeedManager(BMP280Sensor* p_BMP280Sensor);   
    float getSpeed();
    float getMaxSpeed();
    void tick();
};