#pragma once
#include "Modules/BME280Sensor.h"
#include "Actions/ActionEjectChute.h"
#include "SpeedManager.h"
#include "const.h"

class ChuteManager
{
private:
    BME280Sensor *m_BME280Sensor;
    SpeedManager *m_speedManager;
    ActionEjectChute *m_actionEjectChute;
    uint64_t m_lastReadTime;
    bool m_isChuteDeployed;
    bool isAltitudeDecreasing();
    bool isSpeedAcceleratingFromApogee();

public:
    ChuteManager(
        BME280Sensor *p_BME280Sensor,
        SpeedManager *p_speedManager,
        ActionEjectChute *m_actionEjectChute);
    void tick();
};
