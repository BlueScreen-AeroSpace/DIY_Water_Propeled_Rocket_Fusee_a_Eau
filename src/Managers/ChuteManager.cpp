#include "Managers/ChuteManager.h"

ChuteManager::ChuteManager(
    BMP280Sensor* p_BMP280Sensor,
    SpeedManager* p_speedManager,
    ActionEjectChute* p_actionEjectChute) 
    : m_BMP280Sensor(p_BMP280Sensor),
      m_actionEjectChute(p_actionEjectChute),
      m_lastReadTime(DEFAULT_ZERO),
      m_interval(INTERVAL_500),
      m_isChuteDeployed(false) { ; }

bool ChuteManager::isAltitudeDecreasing() {
    float altitude = this->m_BMP280Sensor->getAltitude();
    float maxAltitude = this->m_BMP280Sensor->getMaxAltitude();
    bool isAltitudeDecreasing = false;

    if(maxAltitude-altitude > MARGIN_ERROR && !this->m_isChuteDeployed) {
        isAltitudeDecreasing = true;
    }

    return isAltitudeDecreasing;
}

bool ChuteManager::isSpeedAcceleratingFromApogee() {
    bool isSpeedAcceleratingFromApogee = false;
    float speed = this->m_speedManager->getSpeed();

    if(speed + MARGIN_ERROR <= DEFAULT_ZERO && !this->m_isChuteDeployed) {
        isSpeedAcceleratingFromApogee = true;
    }

    return isSpeedAcceleratingFromApogee;
}

void ChuteManager::tick() {
   if (this->m_lastReadTime + this->m_interval < millis()) { 
        this->m_lastReadTime = millis();
        if(this->isAltitudeDecreasing() || isSpeedAcceleratingFromApogee()) {
            this->m_actionEjectChute->execute();
            this->m_isChuteDeployed = true;
        }
    }
}
