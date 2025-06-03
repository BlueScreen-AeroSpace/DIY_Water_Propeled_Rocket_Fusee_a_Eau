#pragma once
#include "Modules/Sensor.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "const.h"

// Le module que j'ai est un "semblant" de BME280, il calcule la température, la pression atmosphérique, l'humidité et il peut donc aussi
// donner une approximation de l'altitude. Le module a besoin d'être connecté au pins SCL (clock) SDA (data) et SDO doit être connecté au GND
// pour obtenir l'adresse 0x76 ou VCC pour l'adresse 0x77. Bien sure les GND et VCC doivent être connectées pour son fonctionnement.

class BME280Sensor : public Sensor
{
private:
    float m_temperature = 0;
    float m_humidite = 0;
    float m_altitude = 0;
    float m_pressure = 0;

    float m_maxTemperature = 0;
    float m_minTemperature = 0;
    float m_maxHumidite = 0;
    float m_minHumidite = 0;
    float m_maxAltitude = 0;
    float m_maxPressure = 0;

    float m_groundAltitude = 0;

    Adafruit_BME280 m_BME280;
    uint64_t m_lastReadTime = 0;
    uint16_t m_interval = INTERVAL_50;

    void setMembersValues();
    void setMaxValues();
    void setMinValues();
    void setGroundAltitude();

public:
    BME280Sensor();
    void tick();
    void toggleState() override {} ;
    float getTemperature();
    float getHumidite();
    float getAltitude();
    float getPressure();

    float getMaxTemperature();
    float getMinTemperature();
    float getMaxHumidite();
    float getMinHumidite();
    float getMaxAltitude();
    float getMaxPressure();
};
