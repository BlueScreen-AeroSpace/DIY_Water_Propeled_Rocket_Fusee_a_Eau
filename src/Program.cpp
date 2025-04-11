#include "Program.h"
#include "LittleFS.h"
#include "WiFi.h"
#include "config.h"

Program::Program()
{
    if (!LittleFS.begin())
    {
        Serial.println("Erreur d'initialisation de LittleFS !");
        return;
    }
    Serial.println("LittleFS monté avec succès !");

    WiFi.softAP(AP_SSID, AP_PASSWORD);

    Serial.print("Point d'accès créé, IP: ");
    Serial.println(WiFi.softAPIP());
    this->m_configManager = new ConfigManager();
    this->m_webManager = new WebManager(this->m_configManager);
}

void Program::initSensors()
{
    std::vector<String> sensorsToInit = this->m_configManager->getSensorsToInit();
    this->m_sensorManager = new SensorManager();
    this->m_BME280Sensor = new BME280Sensor();
    this->m_sensorManager->addSensor(this->m_BME280Sensor);
    this->m_SD_Shield = new SD_Shield();
    this->m_servoMotor = new ServoMotor();

    for (uint8_t i = 0; i < sensorsToInit.size(); i++)
    {
        if (sensorsToInit[i] == "ADXL345")
        {
            this->m_ADXL345Sensor = new ADXL345Sensor();
            this->m_sensorManager->addSensor(this->m_ADXL345Sensor);
        }
        else if (sensorsToInit[i] == "DS1307Clock")
        {
            String dateAndTime = this->m_configManager->getDateAndTimeToInit();
            this->m_DS1307Clock = new DS1307Clock();
            this->m_DS1307Clock->setActualDateAndTime(dateAndTime);
            this->m_sensorManager->addSensor(this->m_DS1307Clock);
        }
    }
}

void Program::initManagers()
{
    this->m_CSV_Logger = new CSV_TelemetryLogger(this->m_SD_Shield, this->m_DS1307Clock, this->m_configManager);
    this->m_speedManager = new SpeedManager(this->m_BME280Sensor);
    this->m_actionEjectChute = new ActionEjectChute(this->m_servoMotor);
    this->m_chuteManager = new ChuteManager(
        this->m_BME280Sensor,
        this->m_speedManager,
        this->m_actionEjectChute);
    this->m_DELPanelManager = new DELPanelManager(this->m_DS1307Clock); // Manager du panneau de DEL
}

void Program::initMembers()
{
    this->initSensors();
    this->initManagers();

    this->m_dahRocket = new Rocket();
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
            if (this->m_BME280Sensor != nullptr)
            {
                this->m_BME280Sensor->tick();
            }
            if (this->m_ADXL345Sensor != nullptr)
            {
                this->m_ADXL345Sensor->tick();
            }
            this->m_DELPanelManager->tick();
            this->m_speedManager->tick();
            this->m_chuteManager->tick();
            this->logData();
        }
    }
    this->m_webManager->loop();
}

void Program::logData()
{
    if (this->m_lastReadTime + this->m_interval < millis())
    {
        this->m_lastReadTime = millis();

        if (this->m_dahRocket->inFlightReady())
        {
            if (!this->m_isWrittingNewData)
            {
                this->m_CSV_Logger->init();
                this->m_timeCounter = DEFAULT_ZERO;
                this->m_isWrittingNewData = true;
            }
            String time = String(this->m_timeCounter);
            std::vector<String> dataTypes = this->m_configManager->getDataTypesChosen();
            String flightData = time + ";";

            for (uint8_t i = 0; i < dataTypes.size(); i++)
            {
                if (dataTypes[i] == "Température")
                {
                    String temp = String(this->m_BME280Sensor->getTemperature());
                    flightData += temp + ";";
                }
                if (dataTypes[i] == "Humidité")
                {
                    String hum = String(this->m_BME280Sensor->getHumidite());
                    flightData += hum + ";";
                }
                if (dataTypes[i] == "Altitude")
                {
                    String alt = String(this->m_BME280Sensor->getAltitude());
                    flightData += alt + ";";
                }
                if (dataTypes[i] == "Pression Atmosphérique")
                {
                    String pres = String(this->m_BME280Sensor->getPressure());
                    flightData += pres + ";";
                }
                if (dataTypes[i] == "Accélération")
                {
                    String speed = String(this->m_speedManager->getSpeed());
                    flightData += speed + ";";
                } // else if(dataTypes[i] == "Axe z") {
                //     String z = String(this->m_ADXL345Sensor->getAccelAxeZ());
                //     flightData += z + ";";
                // } else if(dataTypes[i] == "Axe y") {
                //     String y = String(this->m_ADXL345Sensor->getAccelAxeY());
                //     flightData += y + ";";
                // } else if(dataTypes[i] == "Axe x") {
                //     String x = String(this->m_ADXL345Sensor->getAccelAxeX());
                //     flightData += x + ";";
            }

            this->m_CSV_Logger->logData(flightData);
            this->m_timeCounter += m_interval;
        }
    }
}
