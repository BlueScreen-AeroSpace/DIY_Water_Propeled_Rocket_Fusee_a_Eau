#include "Modules/ADXL345Sensor.h"

// Source utilisation et méthodes librairie: adafruit/Adafruit ADXL345@^1.3.4 depuis "PIO Home/Librairies".
// Aussi guidé par cette exemple: https://www.youtube.com/watch?v=s5Ne0hIaJws  

ADXL345Sensor::ADXL345Sensor() 
  : m_axeX(DEFAULT_ZERO),
    m_axeY(DEFAULT_ZERO),
    m_axeZ(DEFAULT_ZERO),
    m_maxAccelX(DEFAULT_ZERO),
    m_maxAccelY(DEFAULT_ZERO),
    m_maxAccelZ(DEFAULT_ZERO),
    m_lastReadTime(DEFAULT_ZERO),
    m_interval(INTERVAL_100) { 
        Wire.begin();
        if(!this->m_ADXL345.begin()) {
            Serial.println("Incapable de démarrer le capteur ADXL345. Vérifiez l'adresse et le câblage.");
            while(true);
        } else {
             Serial.println("Capteur ADXL345 initialisé avec succès.");
        }
    }

void ADXL345Sensor::setMembersValues() {
    sensors_event_t event;
    this->m_ADXL345.getEvent(&event);

    this->m_axeX = event.acceleration.x;
    this->m_axeY = event.acceleration.y;
    this->m_axeZ = event.acceleration.z;
}

void ADXL345Sensor::setMaxValues() {
    if (this->m_axeX > this->m_maxAccelX) {
        this->m_maxAccelX = m_axeX;
    }
    if (this->m_axeY > this->m_maxAccelY) {
        this->m_maxAccelY = m_axeY;
    }
    if (this->m_axeZ > this->m_maxAccelZ) {
        this->m_maxAccelZ = m_axeZ;
    }
}

// Retour en float exemple: 2,2
float ADXL345Sensor::getAccelAxeX() {
    return String(this->m_axeX / G_CONST, 1).toFloat();             // Formate facilement le float avec 1 chiffre après la virgule
}
float ADXL345Sensor::getAccelAxeY() {
    return String(this->m_axeY / G_CONST, 1).toFloat();             // division par la constante d'accel gravitationnel pour retourner des "G"
}
float ADXL345Sensor::getAccelAxeZ() {
    return String(this->m_axeZ / G_CONST, 1).toFloat();
}

float ADXL345Sensor::getMaxAccelAxeX() {
    return String(this->m_maxAccelX / G_CONST, 1).toFloat();
}
float ADXL345Sensor::getMaxAccelAxeY() {
    return String(this->m_maxAccelY / G_CONST, 1).toFloat();
}
float ADXL345Sensor::getMaxAccelAxeZ() {
    return String(this->m_maxAccelZ / G_CONST, 1).toFloat();
}

void ADXL345Sensor::tick() {
    if (this->m_lastReadTime + this->m_interval < millis()) {       
        this->m_lastReadTime = millis();
        setMembersValues();
        setMaxValues();
    }
}
