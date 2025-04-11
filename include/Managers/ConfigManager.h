#pragma once
#include <vector>
#include <ArduinoJson.h>

class ConfigManager
{
private:
    std::vector<String> m_sensorsToInit = {};
    std::vector<String> m_dataTypesChosen = {};
    String m_dateAndTimeToInit = "";
    bool m_isConfigReceived = false;

public:
    ConfigManager();
    void setSensorsToInit(const std::vector<String> &p_sensorsToInit);
    void setDataTypesChosen(const std::vector<String> &p_dataTypesChosen);
    void setDateAndTimeToInit(String p_dateAndTime);
    String getDateAndTimeToInit();
    void notifyConfigReceived();
    std::vector<String> getSensorsToInit();
    std::vector<String> getDataTypesChosen();
    bool isConfigReceived();
};