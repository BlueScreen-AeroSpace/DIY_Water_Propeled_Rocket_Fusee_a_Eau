#pragma once
#include "Modules/BME280Sensor.h"
#include "Modules/ADXL345Sensor.h"
#include "Modules/DS1307Clock.h"
#include "Modules/SD_Shield.h"
#include "Managers/CSVTelemetryLogger.h"
#include "Modules/ServoMotor.h"
#include "LED.h"

#include "Actions/ActionEjectChute.h"
#include "Modules/WS2812Panel.h"

#include "Managers/ChuteManager.h"
#include "Managers/SpeedManager.h"
#include "Managers/WebManager.h"
#include "Managers/DELPanelManager.h"
#include "Managers/ConfigManager.h"
#include "Managers/LaunchManager.h"
#include "Managers/DataLoggerManager.h"
#include "Managers/WebSerialManager.h"
#include "Managers/WebSerialCommandInterpreter.h"

class Program
{
private:
    BME280Sensor *m_BME280Sensor = nullptr;
    ADXL345Sensor *m_ADXL345Sensor = nullptr;
    DS1307Clock *m_DS1307Clock = nullptr;
    SD_Shield *m_SD_Shield = nullptr;
    CSV_TelemetryLogger *m_CSV_Logger = nullptr;
    ServoMotor *m_servoMotor = nullptr;
    LED *m_led = nullptr;

    ActionEjectChute *m_actionEjectChute = nullptr;

    ChuteManager *m_chuteManager = nullptr;
    SpeedManager *m_speedManager = nullptr;
    DELPanelManager *m_DELPanelManager = nullptr;
    ConfigManager *m_configManager = nullptr;
    LaunchManager *m_launchManager = nullptr;
    DataLoggerManager *m_dataLoggerManager = nullptr;
    WebManager *m_webManager = nullptr;
    WebSerialManager *m_webSerialManager = nullptr;

    void initMembers();
    void initManagers();
    void initSensors();

public:
    Program();
    void loop();
    bool m_areMembersInitialised = false;
};