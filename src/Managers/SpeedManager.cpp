#include "Managers/SpeedManager.h"

SpeedManager::SpeedManager(BMP280Sensor* p_BMP280Sensor) 
  :    
    m_BMP280Sensor(p_BMP280Sensor),
    m_actualAltitude(DEFAULT_ZERO),
    m_previousAltitude(DEFAULT_ZERO),
    m_actualSpeed(DEFAULT_ZERO),
    m_maxSpeed(DEFAULT_ZERO),
    m_previousTime(DEFAULT_ZERO),
    m_interval(INTERVAL_100) { ; }     //interval 100 ms pour l'instant

void SpeedManager::computeSpeed() {
    this->m_actualAltitude = this->m_BMP280Sensor->getAltitude();

    uint64_t currentTime = millis();
    float deltaTime = (currentTime - this->m_previousTime) / TO_SEC;            // à mettre en const pour convertion ms vers seconde
    float deltaAltitude = this->m_actualAltitude - this->m_previousAltitude;

    if (deltaTime > DEFAULT_ZERO) {
        this->m_actualSpeed = deltaAltitude / deltaTime;
    }

     this->m_previousAltitude = this->m_actualAltitude;
     this->m_previousTime = currentTime;
}
void SpeedManager::setMaxSpeed() {
    if (this->m_actualSpeed > this->m_maxSpeed) {
        this->m_maxSpeed = this->m_actualSpeed;
    }
}

float SpeedManager::getSpeed() {                                                // Exemple 11.2 m/s
    return String(this->m_actualSpeed, 1).toFloat();
}
float SpeedManager::getMaxSpeed() {
    return String(this->m_maxSpeed, 1).toFloat();
}
void SpeedManager::tick() {
    if (this->m_previousTime + this->m_interval > millis()) {                   // lecture au 100 ms pour l'instant     
        this->m_previousTime = millis();
        computeSpeed();
        setMaxSpeed();
    }
}
