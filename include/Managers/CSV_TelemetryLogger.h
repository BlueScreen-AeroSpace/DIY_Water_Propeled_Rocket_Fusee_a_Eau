#pragma once
#include "Modules/SD_Shield.h"
#include "Modules/DS1307Clock.h"
#include "Managers/ConfigManager.h"

class CSV_TelemetryLogger
{
private:
    SD_Shield *m_sdShield;
    DS1307Clock *m_DS1307Clock;
    String m_fileName;
    String m_header;
    ConfigManager *m_configManager;

    void createFileName();
    void createCSVHeader();

public:
    CSV_TelemetryLogger(
        SD_Shield *p_sdShield,
        DS1307Clock *p_DS1307Clock,
        ConfigManager *p_configManager);
    void init();
    void logData(String p_data);
};
