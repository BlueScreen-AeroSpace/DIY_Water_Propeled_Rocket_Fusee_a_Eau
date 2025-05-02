#include "Managers/DataLoggerManager.h"
#include "Logs/DataLogger.h"

DataLoggerManager::DataLoggerManager() : m_bme280Sensor(nullptr),
                                         m_adxlSensor(nullptr),
                                         m_CSV_Logger(nullptr),
                                         m_configManager(nullptr),
                                         m_speedManager(nullptr),
                                         m_isWrittingNewData(false),
                                         m_lastReadTime(0),
                                         m_timeCounter(0),
                                         m_isReadyToLogData(false),
                                         m_interval(INTERVAL_100) { 
                                            Logger.log("Module DataLoggerManager initialisé."); 
                                        }

void DataLoggerManager::setBME(BME280Sensor *p_bme280Sensor)
{
    this->m_bme280Sensor = p_bme280Sensor;
}

void DataLoggerManager::setADXLSensor(ADXL345Sensor *p_adxlSensor)
{
    this->m_adxlSensor = p_adxlSensor;
}

void DataLoggerManager::setTelemetryLogger(CSV_TelemetryLogger *p_csvTelemetryLogger)
{
    this->m_CSV_Logger = p_csvTelemetryLogger;
}

void DataLoggerManager::setConfigManager(ConfigManager *p_configManager)
{
    this->m_configManager = p_configManager;
}

void DataLoggerManager::setSpeedManager(SpeedManager *p_speedManager)
{
    this->m_speedManager = p_speedManager;
}

void DataLoggerManager::setIsReadyToLogData()
{
    this->m_isReadyToLogData = true;
    Logger.log("DataLogger est pret à logger les données");
}

void DataLoggerManager::logData()
{
    if (this->m_timeCounter != MAX_DATA_RECORD_TIME)
    {
        if (this->m_isReadyToLogData)
        {
            if (this->m_configManager == nullptr ||
                this->m_bme280Sensor == nullptr ||
                this->m_speedManager == nullptr ||
                this->m_CSV_Logger == nullptr)
            {
                Serial.println("ERREUR : Un des pointeurs est nul dans logData()");
                return;
            }
            Serial.println("Les capteurs sont initialises");

            if (this->m_lastReadTime + this->m_interval <= millis())
            {
                if (this->m_isWrittingNewData == true)
                    this->m_lastReadTime = millis();
                {
                    String time = String(this->m_timeCounter);

                    std::vector<String> dataTypes = this->m_configManager->getDataTypesChosen();
                    String flightData = time + ";";

                    for (uint8_t i = 0; i < dataTypes.size(); i++)
                    {
                        if (dataTypes[i] == "Température")
                        {
                            String temp = String(this->m_bme280Sensor->getTemperature());
                            flightData += temp + ";";
                        }
                        if (dataTypes[i] == "Humidité")
                        {
                            String hum = String(this->m_bme280Sensor->getHumidite());
                            flightData += hum + ";";
                        }
                        if (dataTypes[i] == "Altitude")
                        {
                            String alt = String(this->m_bme280Sensor->getAltitude());
                            flightData += alt + ";";
                        }
                        if (dataTypes[i] == "Pression Atmosphérique")
                        {
                            String pres = String(this->m_bme280Sensor->getPressure());
                            flightData += pres + ";";
                        }
                        if (dataTypes[i] == "Accélération")
                        {
                            String axeX = String(this->m_adxlSensor->getAccelAxeX());
                            flightData += axeX + ";";

                            String axeY = String(this->m_adxlSensor->getAccelAxeY());
                            flightData += axeY + ";";

                            String axeZ = String(this->m_adxlSensor->getAccelAxeZ());
                            flightData += axeZ + ";";
                        }
                    }
                    String speed = String(this->m_speedManager->getSpeed());
                    flightData += speed + ";";
                    Serial.println(flightData);
                    this->m_CSV_Logger->logData(flightData);
                    this->m_timeCounter += m_interval;
                }
            }
        }
    }
}
