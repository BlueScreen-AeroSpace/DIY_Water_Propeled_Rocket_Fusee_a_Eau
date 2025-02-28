#pragma once
#include "Modules/BMP280Sensor.h"
#include "Actions/ActionEjectChute.h"
#include "SpeedManager.h"
#include "const.h"

class ChuteManager {
private:
    BMP280Sensor* m_BMP280Sensor;
    SpeedManager* m_speedManager;
    ActionEjectChute* m_actionEjectChute;
    uint64_t m_lastReadTime;
    uint16_t m_interval;
    bool m_isChuteDeployed;
    bool isAltitudeDecreasing();
    bool isSpeedAcceleratingFromApogee();

public:
    ChuteManager(
        BMP280Sensor* p_BMP280Sensor,
        SpeedManager* p_speedManager,
        ActionEjectChute* m_actionEjectChute);
    void tick();
};
