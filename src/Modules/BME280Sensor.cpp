#include "Modules/BME280Sensor.h"
#include "config.h"
#include "Logs/DataLogger.h"

// Constructeur du capteur BME280.
BME280Sensor::BME280Sensor()
{
    Sensor::setName("BME280");
    Sensor::m_isActive = true;
    if (!Wire.begin(SDA_PIN, SCL_PIN))
    {
        Logger.error("BME280 n'a pas pu être connecté");
    }

    if (!m_BME280.begin(BME_ADD))
    { // Simple vérification affiché dans le port série. A servi à détecter que je n'avais pas un BME mais un BMP.
        Sensor::m_isActive = false;
        Logger.error("Incapable de démarrer le capteur BME280. Vérifiez l'adresse et le câblage.");
    }
    else
    { // Sera utilisé dans tout les objets, à la mise en route de l'esp32 avant le lancement. On pourrait utiliser le LCD. Si problème d'un objet, on connaitra la cause.
      // Au lieu d'un Serial.println() dans le port série COM4, puisque l'esp32 ne sera pas physiquement connecté, on aurait les infos sur le LCD placé sur la fusée.
      Logger.log("Capteur BME280 initialisé avec succès.");
    }
    m_BME280.setSampling(
        Adafruit_BME280::MODE_NORMAL, // Mode de mesure (FORCED ou NORMAL)
        Adafruit_BME280::SAMPLING_X8, // Température
        Adafruit_BME280::SAMPLING_X8, // Pression
        Adafruit_BME280::SAMPLING_X8, // Humidité (non utilisée ici)
        Adafruit_BME280::FILTER_X4   // Filtrage matériel
    );
    setGroundAltitude();
}

// Fonction qui vient changer les données membres du BME280.
void BME280Sensor::setMembersValues()
{
    this->m_temperature = this->m_BME280.readTemperature();
    this->m_humidite = this->m_BME280.readHumidity();
    this->m_altitude = this->m_BME280.readAltitude(SEALEVELPRESSURE_HPA) - this->m_groundAltitude;
    this->m_pressure = this->m_BME280.readPressure() / KILOPASCAL; // divisé par 1000.0f pour passer de Pascal (Pa) à Kilo Pascal (kPa)
}

// Fonction qui change la valeur de l'altitude au sol.
void BME280Sensor::setGroundAltitude()
{
    this->m_groundAltitude = this->m_BME280.readAltitude(SEALEVELPRESSURE_HPA);
}

// Fonction qui vient changer les données maximales membres du BME280.
void BME280Sensor::setMaxValues()
{
    if (this->m_temperature > this->m_maxTemperature)
    {
        this->m_maxTemperature = m_temperature;
    }
    if (this->m_humidite > this->m_maxHumidite)
    {
        this->m_maxHumidite = m_humidite;
    }
    if (this->m_altitude > this->m_maxAltitude)
    {
        this->m_maxAltitude = m_altitude;
    }
    if (this->m_pressure > this->m_maxPressure)
    {
        this->m_maxPressure = m_pressure;
    }
}

// Fonction qui vient changer les données minimales membres du BME280.
void BME280Sensor::setMinValues()
{
    if (this->m_temperature < this->m_minTemperature)
    {
        this->m_minTemperature = m_temperature;
    }
    if (this->m_humidite < this->m_minHumidite)
    {
        this->m_minHumidite = m_humidite;
    }
}

// Fonction qui retourne la valeur de température en float.
float BME280Sensor::getTemperature()
{
    return this->m_temperature;
}
// Fonction qui retourne la valeur de l'humidité en float.
float BME280Sensor::getHumidite()
{
    return this->m_humidite;
}
// Fonction qui retourne la valeur de l'altitude en float.
float BME280Sensor::getAltitude()
{
    if (this->m_altitude < 0)
    {
        return 0;
    }
    return this->m_altitude;
}
// Fonction qui retourne la valeur de pression atmosphérique en float.
float BME280Sensor::getPressure()
{
    return this->m_pressure;
}

// Fonction qui retourne la valeur maximale de la température en float.
float BME280Sensor::getMaxTemperature()
{
    return this->m_maxTemperature;
}
// Fonction qui retourne la valeur minimale de la température en float.
float BME280Sensor::getMinTemperature()
{
    return this->m_maxTemperature;
}
// Fonction qui retourne la valeur maximale de l'humidité en float.
float BME280Sensor::getMaxHumidite()
{
    return this->m_maxHumidite;
}
// Fonction qui retourne la valeur minimale de l'humidité en float.
float BME280Sensor::getMinHumidite()
{
    return this->m_minHumidite;
}
// Fonction qui retourne la valeur maximale de l'altitude en float.
float BME280Sensor::getMaxAltitude()
{
    return this->m_maxAltitude;
}
// Fonction qui retourne la valeur maximale de la pression atmosphérique en float.
float BME280Sensor::getMaxPressure()
{
    return this->m_maxPressure;
}

// Fonction qui écoute les changements de valeur des données membre.
void BME280Sensor::tick()
{
    if (!Sensor::m_isActive)
    {
        return;
    }
    if (this->m_lastReadTime + this->m_interval < millis())
    {
        this->m_lastReadTime = millis();
        this->setMembersValues();
        this->setMaxValues();
    }
}
