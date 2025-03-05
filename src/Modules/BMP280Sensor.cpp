#include "Modules/BMP280Sensor.h"

BMP280Sensor::BMP280Sensor()
  : m_temperature(DEFAULT_ZERO),
    m_altitude(DEFAULT_ZERO),                              // Pour afficher un altitude réel depuis le sol du lancement, devra créer une classe pour le clacul.  Prendre l'altitude
    m_pressure(DEFAULT_ZERO),                              // stable avant le lancement, la conserver dans une données membre et relancer l'altitude moins la donnée enregistrée. 
    m_maxTemperature(DEFAULT_ZERO),
    m_maxPressure(DEFAULT_ZERO),
    m_maxAltitude(DEFAULT_ZERO),  
    m_groundAltitude(DEFAULT_ZERO),
    m_lastReadTime(DEFAULT_ZERO),                           // Comme ça l'altitude depuis le sol sera visible. Ou bien dans une donnée membre à l'intérieur de cette classe directement.
    m_interval(INTERVAL_100) {
        Wire.begin(SDA_PIN,SCL_PIN);                                        
        if (!m_BMP280.begin(BMP_ADD)) {                     // Simple vérification affiché dans le port série. A servi à détecter que je n'avais pas un BME mais un BMP.
            Serial.println("Incapable de démarrer le capteur BMP280. Vérifiez l'adresse et le câblage.");
            while(true);                                    // La librairie de ADXL345 m'a montré que c'est une manière de créer une boucle infinie pour arrèter le programme sans cracher mais boucle dans le vide à l'infinie.
        } else {                                            // Sera utilisé dans tout les objets, à la mise en route de l'esp32 avant le lancement. On pourrait utiliser le LCD. Si problème d'un objet, on connaitra la cause.
                                                            // Au lieu d'un Serial.println() dans le port série COM4, puisque l'esp32 ne sera pas physiquement connecté, on aurait les infos sur le LCD placé sur la fusée. 
            Serial.println("Capteur BMP280 initialisé avec succès.");
        } 
        setGroundAltitude();                         
    }               

void BMP280Sensor::setMembersValues() {                                     
    this->m_temperature = this->m_BMP280.readTemperature();                 
    this->m_altitude = this->m_BMP280.readAltitude(SEALEVELPRESSURE_HPA) - this->m_groundAltitude;   
    this->m_pressure = this->m_BMP280.readPressure() / KILOPASCAL;          // divisé par 1000.0f pour passer de Pascal (Pa) à Kilo Pascal (kPa)
}                                                                           

void BMP280Sensor::setGroundAltitude() {
    this->m_groundAltitude = this->m_BMP280.readAltitude(SEALEVELPRESSURE_HPA);
}

void BMP280Sensor::setMaxValues() {
    if (this->m_temperature > this->m_maxTemperature) {
        this->m_maxTemperature = m_temperature;
    }
    if (this->m_altitude > this->m_maxAltitude) {
        this->m_maxAltitude = m_altitude;
    }
    if (this->m_pressure > this->m_maxPressure) {
        this->m_maxPressure = m_pressure;
    }
}

float BMP280Sensor::getTemperature() {
    return this->m_temperature;
}
float BMP280Sensor::getAltitude() {
    return this->m_altitude;
}
float BMP280Sensor::getPressure() {
    return this->m_pressure;
}

float BMP280Sensor::getMaxTemperature() {
    return this->m_maxTemperature;
}
float BMP280Sensor::getMaxAltitude() {
    return this->m_maxAltitude;
}
float BMP280Sensor::getMaxPressure() {
    return this->m_maxPressure;
}

void BMP280Sensor::tick() { 
    if (this->m_lastReadTime + this->m_interval < millis()) {
        this->m_lastReadTime = millis();
        this->setMembersValues();
        this->setMaxValues();
    }
}
