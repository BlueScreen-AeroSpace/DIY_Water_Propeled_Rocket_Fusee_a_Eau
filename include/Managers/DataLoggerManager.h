#pragma once
#include "Managers/CSVTelemetryLogger.h"
#include "Managers/ConfigManager.h"
#include "Managers/SpeedManager.h"
#include "Modules/BME280Sensor.h"
#include "Modules/ADXL345Sensor.h"
#include "const.h"

class DataLoggerManager
{
private:
    BME280Sensor *m_bme280Sensor;
    CSV_TelemetryLogger *m_CSV_Logger;
    ConfigManager *m_configManager;
    SpeedManager *m_speedManager;
    ADXL345Sensor *m_adxlSensor;
    uint16_t m_interval;
    uint64_t m_lastReadTime;
    uint64_t m_timeCounter;
    bool m_isReadyToLogData;

public:
    bool m_isWrittingNewData;
    void setBME(BME280Sensor *p_bme280Sensor);
    void setADXLSensor(ADXL345Sensor *p_adxlSensor);
    void setTelemetryLogger(CSV_TelemetryLogger *p_csvTelemetryLogger);
    void setConfigManager(ConfigManager *p_configManager);
    void setSpeedManager(SpeedManager *p_speedManager);
    DataLoggerManager();
    void setIsReadyToLogData();
    void logData();
};