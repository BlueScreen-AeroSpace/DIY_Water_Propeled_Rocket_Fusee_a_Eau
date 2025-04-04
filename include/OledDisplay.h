#pragma once
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "Managers/SensorManager.h"
#include "const.h"

class OledDisplay
{
private:
    Adafruit_SSD1306 m_OledDisplay;
    SensorManager *m_sensorManager;

public:
    OledDisplay(SensorManager* p_sensorManager);
    void displayActivatedSensors();
};