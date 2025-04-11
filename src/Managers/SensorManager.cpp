#include "Managers/SensorManager.h"
#include "config.h"

SensorManager::SensorManager() { ; }

void SensorManager::addSensor(Sensor *p_sensor)
{
    if (p_sensor)
    {
        this->m_sensors.push_back(p_sensor);
        p_sensor->setID(this->m_sensorCount);
        this->m_sensorCount++;
        p_sensor->setState(true);
    }
}

Sensor *SensorManager::getSensor(uint8_t p_ID)
{
    if (p_ID >= MAX_SENSORS)
    {
        return nullptr;
    }

    return this->m_sensors[p_ID];
}

void SensorManager::toggleSensorState(uint8_t p_ID)
{
    if (p_ID < MAX_SENSORS)
    {
        this->m_sensors[p_ID]->toggleState();
    }
}

const std::vector<Sensor *> &SensorManager::getSensors()
{
    return this->m_sensors;
}

std::vector<Sensor *> SensorManager::getActivatedSensors()
{
    std::vector<Sensor *> activatedSensors;

    for (uint8_t i = 0; i < m_sensors.size(); i++)
    {
        if (m_sensors[i]->getState())
        {
            activatedSensors.push_back(m_sensors[i]);
        }
    }

    return activatedSensors;
}
