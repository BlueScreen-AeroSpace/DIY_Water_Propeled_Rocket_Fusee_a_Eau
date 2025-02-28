#pragma once
#include <Arduino.h>
#include "const.h"

class LED {
private:
    uint8_t m_pin;
public:
    LED(const uint8_t p_pin);
    void light() const;
    void shut() const;
};