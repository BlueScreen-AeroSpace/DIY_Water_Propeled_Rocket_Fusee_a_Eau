#include "Program.h"
#include "LittleFS.h"
#include "WiFi.h"
#include "config.h"
#include "Logs/DataLogger.h"

Program::Program()
{
    if (!LittleFS.begin())
    {
        Logger.error("Erreur d'initialisation de LittleFS !");
        return;
    }
    Logger.log("LittleFS monté avec succès !");

    WiFi.softAP(AP_SSID, AP_PASSWORD);

    Logger.log("Point d'accès créé, IP: " + WiFi.softAPIP().toString());
    this->m_configManager = new ConfigManager();
    this->m_dataLoggerManager = new DataLoggerManager();
    this->m_DS1307Clock = new DS1307Clock();
    this->m_configManager->setClock(this->m_DS1307Clock);
    this->m_dataLoggerManager->setConfigManager(this->m_configManager);
    this->m_DELPanelManager = new DELPanelManager(this->m_DS1307Clock, this->m_dataLoggerManager);
    this->m_launchManager = new LaunchManager(this->m_DELPanelManager);
    this->m_webManager = new WebManager(this->m_configManager, this->m_dataLoggerManager, this->m_DELPanelManager, this->m_launchManager);
    this->m_webSerialManager = new WebSerialManager(new WebSerialCommandInterpreter(m_DELPanelManager));
    Logger.log("Programme initialisé");
}

void Program::initSensors()
{
    std::vector<String> sensorsToInit = this->m_configManager->getSensorsToInit();
    this->m_BME280Sensor = new BME280Sensor();
    this->m_dataLoggerManager->setBME(this->m_BME280Sensor);
    this->m_SD_Shield = new SD_Shield();
    this->m_servoMotor = new ServoMotor();

    for (uint8_t i = 0; i < sensorsToInit.size(); i++)
    {
        if (sensorsToInit[i] == "ADXL345")
        {
            this->m_ADXL345Sensor = new ADXL345Sensor();
            this->m_dataLoggerManager->setADXLSensor(this->m_ADXL345Sensor);
        }
    }
}

void Program::initManagers()
{
    this->m_CSV_Logger = new CSV_TelemetryLogger(this->m_SD_Shield, this->m_DS1307Clock, this->m_configManager);
    this->m_dataLoggerManager->setTelemetryLogger(this->m_CSV_Logger);
    this->m_speedManager = new SpeedManager(this->m_BME280Sensor);
    this->m_dataLoggerManager->setSpeedManager(this->m_speedManager);
    this->m_actionEjectChute = new ActionEjectChute(this->m_servoMotor);
    this->m_chuteManager = new ChuteManager(
        this->m_BME280Sensor,
        this->m_speedManager,
        this->m_actionEjectChute);
    
    
}

void Program::initMembers()
{
    this->initSensors();
    this->initManagers();

    this->m_led = new LED(PIN_LED);
    this->m_led->light(); // Simple mais efficace , si tous les objets sont instanciés, elle s'allume (fusée prête au lancement).

    this->m_areMembersInitialised = true;
}

void Program::loop()
{
    if (this->m_configManager->isConfigReceived())
    {
        if (!this->m_areMembersInitialised)
        {
            this->initMembers();
        }
        else
        {
#ifndef DEBUG
            if (this->m_BME280Sensor != nullptr)
            {
                this->m_BME280Sensor->tick();
            }
            if (this->m_ADXL345Sensor != nullptr)
            {
                this->m_ADXL345Sensor->tick();
            }

            this->m_speedManager->tick();
            this->m_chuteManager->tick();

            this->m_dataLoggerManager->logData();
#endif
            this->m_DELPanelManager->tick();           
        }
    }
    this->m_webSerialManager->tick();
    this->m_webManager->loop();
}
