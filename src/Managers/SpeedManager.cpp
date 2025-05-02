#include "Managers/SpeedManager.h"
#include "Logs/DataLogger.h"

// Constructeur du gestionnaire de vitesse.
SpeedManager::SpeedManager(BME280Sensor *p_BME280Sensor)
    : m_BME280Sensor(p_BME280Sensor),
      m_actualAltitude(DEFAULT_ZERO),
      m_previousAltitude(DEFAULT_ZERO),
      m_actualSpeed(DEFAULT_ZERO),
      m_maxSpeed(DEFAULT_ZERO),
      m_previousTimeSpeed(DEFAULT_ZERO),
      m_interval(INTERVAL_100),
      m_previousTime(DEFAULT_ZERO)
{
    Logger.log("Module SpeedManager initialisé");
} // interval 100 ms pour l'instant

// Fonction qui calcule la vitesse de la fusée.
void SpeedManager::computeSpeed()
{
    this->m_actualAltitude = this->m_BME280Sensor->getAltitude();

    unsigned long currentTime = millis();

    float deltaTime = (currentTime - this->m_previousTimeSpeed) / 1000.0; // à mettre en const pour convertion ms vers seconde
    float deltaAltitude = this->m_actualAltitude - this->m_previousAltitude;

    if (deltaTime > 0.0f)
    {
        this->m_actualSpeed = deltaAltitude / deltaTime;
    }

    this->m_previousAltitude = this->m_actualAltitude;
    this->m_previousTimeSpeed = currentTime;
}

// Fonction qui change la valeur de la vitesse maximale.
void SpeedManager::setMaxSpeed()
{
    if (this->m_actualSpeed > this->m_maxSpeed)
    {
        this->m_maxSpeed = this->m_actualSpeed;
    }
}

// Fonction qui retourne la vitesse actuel en float.
float SpeedManager::getSpeed()
{ // Exemple 11.2 m/s
    return String(this->m_actualSpeed, 1).toFloat();
}

// Fonction qui retourne la vitesse maximale en float.
float SpeedManager::getMaxSpeed()
{
    return String(this->m_maxSpeed, 1).toFloat();
}

// Fonction qui écoute les état de vitesse de la fusée et qui agit en considération afin de conserver la vitesse maximale.
void SpeedManager::tick()
{
    currentTimeTick = millis();

    if (currentTimeTick - m_previousTime >= m_interval)
    {
        computeSpeed();
        setMaxSpeed();
        m_previousTime = currentTimeTick;
    }
}
