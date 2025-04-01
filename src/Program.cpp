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
    this->m_BME280Sensor = new BME280Sensor();
    this->m_ADXL345Sensor = new ADXL345Sensor();
    this->m_DS1307Clock = new DS1307Clock();
    this->m_sensorManager = new SensorManager();
    this->m_webManager = new WebManager(this->m_sensorManager);
    this->m_sensorManager->addSensor(this->m_BME280Sensor);
    this->m_sensorManager->addSensor(this->m_ADXL345Sensor);
    this->m_sensorManager->addSensor(this->m_DS1307Clock);
    this->m_sensorManager->loadSensors();
    this->m_SD_Shield = new SD_Shield();
    this->m_CSV_Logger = new CSV_TelemetryLogger(
        this->m_SD_Shield,
        this->m_DS1307Clock);
    this->m_speedManager = new SpeedManager(this->m_BME280Sensor);
    this->m_servoMotor = new ServoMotor();
    this->m_actionEjectChute = new ActionEjectChute(this->m_servoMotor);
    this->m_chuteManager = new ChuteManager(
        this->m_BME280Sensor,
        this->m_speedManager,
        this->m_actionEjectChute);
    this->m_dahRocket = new Rocket();
    this->m_led = new LED(PIN_LED);
    this->m_led->light(); // Simple mais efficace , si tous les objets sont instanciés, elle s'allume (fusée prête au lancement).
    this->m_oledDisplay = new OledDisplay(this->m_sensorManager);
#ifdef DEBUG
    Serial.println(this->m_ADXL345Sensor->getName());
    Serial.println(this->m_ADXL345Sensor->getID());
    Serial.println(this->m_ADXL345Sensor->getState());
#endif

    WS2812Panel *m_WS2812Panel = new WS2812Panel();
    this->m_DELPanelManager = new DELPanelManager(m_WS2812Panel, m_DS1307Clock); // Manager du panneau de DEL
}

void Program::loop()
{
#ifndef DEBUG
    this->m_BME280Sensor->tick();
    this->m_ADXL345Sensor->tick();
    this->m_speedManager->tick();
    this->logData();
    this->m_chuteManager->tick();
    
#endif
    this->m_webManager->loop();
    this->m_DELPanelManager->tick();
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

            String speed = String(this->m_speedManager->getSpeed());
            String z = String(this->m_ADXL345Sensor->getAccelAxeZ());
            String y = String(this->m_ADXL345Sensor->getAccelAxeY());
            String x = String(this->m_ADXL345Sensor->getAccelAxeX());
            String temp = String(this->m_BME280Sensor->getTemperature());
            String alt = String(this->m_BME280Sensor->getAltitude());
            String pres = String(this->m_BME280Sensor->getPressure());

            String flightData = time + ";" + temp + ";" + alt + ";" + pres + ";" + speed + ";" + z + ";" + y + ";" + x;
            this->m_CSV_Logger->logData(flightData);
            this->m_timeCounter += m_interval;
        }
    }
}
