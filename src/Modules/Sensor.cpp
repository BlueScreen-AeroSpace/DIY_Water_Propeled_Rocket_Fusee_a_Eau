#include "Modules/Sensor.h"

Sensor::Sensor() { ; }

uint8_t Sensor::getID()
{
    return this->m_ID;
}

void Sensor::setID(uint8_t p_ID)
{
    this->m_ID = p_ID;
}

String Sensor::getName()
{
    return this->m_name;
}

void Sensor::setName(const String &p_name)
{
    this->m_name = p_name;
}

bool Sensor::getState()
{
    return this->m_isActive;
}

void Sensor::toggleState()
{
    this->m_isActive = !this->m_isActive;
}

void Sensor::setState(bool newState)
{
    this->m_isActive = newState;
}