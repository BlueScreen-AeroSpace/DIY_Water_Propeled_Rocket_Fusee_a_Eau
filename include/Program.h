#pragma once
#include "Modules/ADXL345Sensor.h"
#include "Modules/BMP280Sensor.h"
#include "Modules/DS1307Clock.h"
#include "Modules/ServoMotor.h"
#include "Modules/SD_Shield.h"
#include "Managers/CSV_TelemetryLogger.h"
#include "Managers/ChuteManager.h"
#include "Managers/SpeedManager.h"
#include "Managers/WIFI_Manager.h"
#include "Managers/JSONManager.h"
#include "Actions/ActionEjectChute.h"
#include "Connection.h"
#include "MQTT_Service.h"
#include "LED.h"
#include "Rocket.h"

class Program {
private:
    String m_sssidWifi;
    String m_wifiPass;
    String m_hassUser;
    String m_hassPass;
    const char* m_hassServer;
    uint16_t m_hassPort;
    
    JSONManager* m_jsonManager;
    Connection* m_connection;
    WIFI_Manager* m_WiFiManager;
    MQTT_Service* m_MQTT_service;
    BMP280Sensor* m_BMP280Sensor;
    ADXL345Sensor* m_ADXL345Sensor;
    DS1307Clock* m_DS1307Clock;             
    SD_Shield* m_SD_Shield;                
    CSV_TelemetryLogger* m_CSV_Logger;      
    ActionEjectChute* m_actionEjectChute;
    ChuteManager* m_chuteManager;
    ServoMotor* m_servoMotor;
    SpeedManager* m_speedManager;
    LED* m_led;
    Rocket* m_dahRocket;
    bool m_isWrittingNewData;
    void logData();
    uint16_t m_interval;
    uint64_t m_lastReadTime;
    uint64_t m_timeCounter;
public:
    Program();
    void loop();                           
};