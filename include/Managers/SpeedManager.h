#pragma once
#include "Modules/BME280Sensor.h"

class SpeedManager
{
private:
    BME280Sensor *m_BME280Sensor;
    float m_actualAltitude;
    float m_previousAltitude;
    float m_actualSpeed;
    float m_maxSpeed;
    unsigned long m_previousTimeSpeed;
    unsigned long m_previousTime;
    unsigned long currentTimeTick;
    uint64_t m_interval;
    void computeSpeed();
    void setMaxSpeed();

public:
    SpeedManager(BME280Sensor *p_BME280Sensor);
    float getSpeed();
    float getMaxSpeed();
    void tick();
};