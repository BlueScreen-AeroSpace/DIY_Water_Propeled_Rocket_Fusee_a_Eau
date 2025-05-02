#include "Managers/ChuteManager.h"
#include "Logs/DataLogger.h"

// Constructeur du gestionnaire de chute.
ChuteManager::ChuteManager(
    BME280Sensor *p_BME280Sensor,
    SpeedManager *p_speedManager,
    ActionEjectChute *p_actionEjectChute)
    : m_BME280Sensor(p_BME280Sensor),
      m_speedManager(p_speedManager),
      m_actionEjectChute(p_actionEjectChute),
      m_lastReadTime(DEFAULT_ZERO),
      m_isChuteDeployed(false) { Logger.log("Module de parachute initialisé"); }

// Fonction qui vérifie si l'altitude décroit et retourne un boolean.
bool ChuteManager::isAltitudeDecreasing()
{
    float altitude = this->m_BME280Sensor->getAltitude();
    float maxAltitude = this->m_BME280Sensor->getMaxAltitude();

    if (maxAltitude - altitude > MARGIN_ERROR && !this->m_isChuteDeployed)
    {
        return true;
    }

    return false;
}

// Fonction qui vérifie si la fusée a atteint sont apogée et retourne un boolean.
bool ChuteManager::isSpeedAcceleratingFromApogee()
{
    float speed = this->m_speedManager->getSpeed();

    if (speed + MARGIN_ERROR <= DEFAULT_ZERO && !this->m_isChuteDeployed)
    {
        return true;
    }

    return false;
}

// Fonction qui écoute les états de chute de la fusée et qui agit en considération afin de déclencher le parachute.
void ChuteManager::tick()
{
    if (this->m_lastReadTime + INTERVAL_100 < millis())
    {
        this->m_lastReadTime = millis();
        if (isSpeedAcceleratingFromApogee())
        {
            this->m_actionEjectChute->execute();
            this->m_isChuteDeployed = true;
        }
    }
}
