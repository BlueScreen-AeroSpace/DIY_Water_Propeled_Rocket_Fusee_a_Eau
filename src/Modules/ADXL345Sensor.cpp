#include "Modules/ADXL345Sensor.h"
#include "config.h"
#include "Logs/DataLogger.h"

// Source utilisation et méthodes librairie: adafruit/Adafruit ADXL345@^1.3.4 depuis "PIO Home/Librairies".
// Aussi guidé par cette exemple: https://www.youtube.com/watch?v=s5Ne0hIaJws

// Constructeur de l'accéléromètre.
ADXL345Sensor::ADXL345Sensor()
{
    Sensor::setName("ADXL345");
    if (!Wire.begin())
    {
        Logger.error("ADXL345 n'a pas pu être démarré");
    }

    if (!this->m_ADXL345.begin())
    {
        Logger.error("Incapable de démarrer le capteur ADXL345. Vérifiez l'adresse et le câblage.");
        Sensor::m_isActive = false;
    }
    else
    {
        Logger.log("Capteur ADXL345 initialisé avec succès.");
        Sensor::m_isActive = true;
    }
}

// Fonction qui vient changer les valeurs membres du ADXL345Sensor.
void ADXL345Sensor::setMembersValues()
{
    sensors_event_t event;
    this->m_ADXL345.getEvent(&event);

    this->m_axeX = event.acceleration.x;
    this->m_axeY = event.acceleration.y;
    this->m_axeZ = event.acceleration.z;
}

// Fonction qui vient changer les valeurs maximales membres du ADXL345Sensor.
void ADXL345Sensor::setMaxValues()
{
    if (this->m_axeX > this->m_maxAccelX)
    {
        this->m_maxAccelX = m_axeX;
    }
    if (this->m_axeY > this->m_maxAccelY)
    {
        this->m_maxAccelY = m_axeY;
    }
    if (this->m_axeZ > this->m_maxAccelZ)
    {
        this->m_maxAccelZ = m_axeZ;
    }
}

// Fonction qui retourne la valeur de l'axe X en float.
float ADXL345Sensor::getAccelAxeX()
{
    return String(this->m_axeX / G_CONST, 1).toFloat(); // Formate facilement le float avec 1 chiffre après la virgule
}

// Fonction qui retourne la valeur de l'axe Y en float.
float ADXL345Sensor::getAccelAxeY()
{
    return String(this->m_axeY / G_CONST, 1).toFloat(); // division par la constante d'accel gravitationnel pour retourner des "G"
}

// Fonction qui retourne la valeur de l'axe Z en float.
float ADXL345Sensor::getAccelAxeZ()
{
    return String(this->m_axeZ / G_CONST, 1).toFloat();
}

// Fonction qui retourne la valeur maximale de l'axe X en float.
float ADXL345Sensor::getMaxAccelAxeX()
{
    return String(this->m_maxAccelX / G_CONST, 1).toFloat();
}

// Fonction qui retourne la valeur maximale de l'axe Y en float.
float ADXL345Sensor::getMaxAccelAxeY()
{
    return String(this->m_maxAccelY / G_CONST, 1).toFloat();
}

// Fonction qui retourne la valeur maximale de l'axe Z en float.
float ADXL345Sensor::getMaxAccelAxeZ()
{
    return String(this->m_maxAccelZ / G_CONST, 1).toFloat();
}

// Fonction qui écoute les changements de valeur des données membre.
void ADXL345Sensor::tick()
{
    if (!Sensor::m_isActive)
    {
        return;
    }

    if (this->m_lastReadTime + this->m_interval < millis())
    {
        this->m_lastReadTime = millis();
        setMembersValues();
        setMaxValues();
    }
}
