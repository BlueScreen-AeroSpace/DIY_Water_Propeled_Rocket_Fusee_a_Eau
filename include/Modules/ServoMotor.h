#pragma once
#include "Modules/Sensor.h"
#include <Arduino.h>
#include <ESP32Servo.h>
#include "const.h"

class ServoMotor : public Sensor {
private:
    Servo m_servo;
    uint8_t m_position;
    uint16_t m_interval;
    
public:
    ServoMotor();
    void rotate(uint8_t p_position);
};
