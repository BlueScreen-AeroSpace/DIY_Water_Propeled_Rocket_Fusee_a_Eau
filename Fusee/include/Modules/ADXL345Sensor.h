#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include "const.h"           

class ADXL345Sensor {
private:
    float m_axeX;               
    float m_axeY;
    float m_axeZ;               // L'axe Z sera l'axe important puisqu'il représente l'axe vertical.
    float m_maxAccelX;
    float m_maxAccelY;
    float m_maxAccelZ;
    Adafruit_ADXL345_Unified m_ADXL345 = Adafruit_ADXL345_Unified();

    uint64_t m_lastReadTime;
    uint16_t m_interval;
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
