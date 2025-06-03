#pragma once
#include "Modules/Sensor.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include "const.h"           

// ADXL345 est un module qui capte l'accélération de la fusée grâce au trois axes.

class ADXL345Sensor : public Sensor {
private:
    float m_axeX = 0;               
    float m_axeY = 0;
    float m_axeZ = 0;               // L'axe Z sera l'axe important puisqu'il représente l'axe vertical.
    float m_maxAccelX = 0;
    float m_maxAccelY = 0;
    float m_maxAccelZ = 0;
    Adafruit_ADXL345_Unified m_ADXL345 = Adafruit_ADXL345_Unified();

    uint64_t m_lastReadTime = 0;
    uint16_t m_interval = INTERVAL_75;
    void setMembersValues();
    void setMaxValues();
public:
    ADXL345Sensor();
    void tick();
    float getAccelAxeX();     
    float getAccelAxeY();
    float getAccelAxeZ();

    float getMaxAccelAxeX();
    float getMaxAccelAxeY();
    float getMaxAccelAxeZ();
};
