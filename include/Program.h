#pragma once
#include "Modules/ADXL345Sensor.h"
#include "Modules/BME280Sensor.h"
#include "Modules/DS1307Clock.h"
#include "Modules/ServoMotor.h"
#include "Modules/SD_Shield.h"
#include "Managers/CSV_TelemetryLogger.h"
#include "Managers/ChuteManager.h"
#include "Managers/SpeedManager.h"
#include "Managers/WebManager.h"
#include "Actions/ActionEjectChute.h"
#include "LED.h"
#include "Rocket.h"
#include "Managers/DELPanelManager.h"
#include "Modules/WS2812Panel.h"
#include "Managers/SensorManager.h"
#include "Managers/ConfigManager.h"

class Program
{
private:
    BME280Sensor *m_BME280Sensor = nullptr;
    ADXL345Sensor *m_ADXL345Sensor = nullptr;
    DS1307Clock *m_DS1307Clock = nullptr;
    SD_Shield *m_SD_Shield = nullptr;
    CSV_TelemetryLogger *m_CSV_Logger = nullptr;
    ActionEjectChute *m_actionEjectChute = nullptr;
    ChuteManager *m_chuteManager = nullptr;
    ServoMotor *m_servoMotor = nullptr;
    SpeedManager *m_speedManager = nullptr;
    LED *m_led = nullptr;
    Rocket *m_dahRocket = nullptr;
    bool m_isWrittingNewData = false;
    DELPanelManager *m_DELPanelManager = nullptr;
    SensorManager *m_sensorManager = nullptr;
    ConfigManager *m_configManager = nullptr;

    void initMembers();
    void initManagers();
    void initSensors();
    void logData();
    uint16_t m_interval = INTERVAL_200;
    uint64_t m_lastReadTime = 0;
    uint64_t m_timeCounter = 0;
    WebManager *m_webManager = nullptr;

public:
    bool m_areMembersInitialised = false;
    Program();
    void loop();
};