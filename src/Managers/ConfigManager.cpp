#include "Managers/ConfigManager.h"

ConfigManager::ConfigManager() { ; }

void ConfigManager::setDataTypesChosen(const std::vector<String> &p_datatTypesChosen)
{
    if (!p_datatTypesChosen.empty())
    {
        this->m_dataTypesChosen = p_datatTypesChosen;
    }
}

void ConfigManager::setClock(DS1307Clock* p_clock){
    this->m_clock = p_clock;
}

void ConfigManager::setClockTime(){
    this->m_clock->setActualDateAndTime(this->m_dateAndTimeToInit);
}

void ConfigManager::setSensorsToInit(const std::vector<String> &sensors)
{
    this->m_sensorsToInit = sensors;
}

std::vector<String> ConfigManager::getSensorsToInit()
{
    return this->m_sensorsToInit;
}

std::vector<String> ConfigManager::getDataTypesChosen()
{
    return this->m_dataTypesChosen;
}

void ConfigManager::notifyConfigReceived()
{
    this->m_isConfigReceived = true;
}

bool ConfigManager::isConfigReceived()
{
    return this->m_isConfigReceived;
}

void ConfigManager::setDateAndTimeToInit(String p_dateAndTime)
{
    this->m_dateAndTimeToInit = p_dateAndTime;
}

String ConfigManager::getDateAndTimeToInit()
{
    return this->m_dateAndTimeToInit;
}