#include "Managers/ChuteManager.h"

// Constructeur du gestionnaire de chute.
ChuteManager::ChuteManager(
    BME280Sensor *p_BME280Sensor,
    SpeedManager *p_speedManager,
    ActionEjectChute *p_actionEjectChute)
    : m_BME280Sensor(p_BME280Sensor),
      m_actionEjectChute(p_actionEjectChute),
      m_lastReadTime(DEFAULT_ZERO),
      m_interval(INTERVAL_500),
      m_isChuteDeployed(false) { ; }

// Fonction qui vérifie si l'altitude décroit et retourne un boolean.
bool ChuteManager::isAltitudeDecreasing()
{
    float altitude = this->m_BME280Sensor->getAltitude();
    float maxAltitude = this->m_BME280Sensor->getMaxAltitude();
    bool isAltitudeDecreasing = false;

    if (maxAltitude - altitude > MARGIN_ERROR && !this->m_isChuteDeployed)
    {
        isAltitudeDecreasing = true;
    }

    return isAltitudeDecreasing;
}

// Fonction qui vérifie si la fusée a atteint sont apogée et retourne un boolean.
bool ChuteManager::isSpeedAcceleratingFromApogee()
{
    bool isSpeedAcceleratingFromApogee = false;
    float speed = this->m_speedManager->getSpeed();

    if (speed + MARGIN_ERROR <= DEFAULT_ZERO && !this->m_isChuteDeployed)
    {
        isSpeedAcceleratingFromApogee = true;
    }

    return isSpeedAcceleratingFromApogee;
}

// Fonction qui écoute les états de chute de la fusée et qui agit en considération afin de déclencher le parachute.
void ChuteManager::tick()
{
    if (this->m_lastReadTime + this->m_interval < millis())
    {
        this->m_lastReadTime = millis();
        if (this->isAltitudeDecreasing() || isSpeedAcceleratingFromApogee())
        {
            this->m_actionEjectChute->execute();
            this->m_isChuteDeployed = true;
        }
    }
}
