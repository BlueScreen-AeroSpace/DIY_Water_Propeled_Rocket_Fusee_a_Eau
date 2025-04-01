#pragma once
#include <Arduino.h>

class Sensor {
private:
    uint8_t m_ID = 0;
    String m_name = "";
protected:
    bool m_isActive = false;
public:
    Sensor();
    String getName();
    bool getState();
    uint8_t getID();
    void setID(uint8_t p_ID);
    virtual void toggleState();
    void setState(bool newState);
    void setName(const String& p_name);
};