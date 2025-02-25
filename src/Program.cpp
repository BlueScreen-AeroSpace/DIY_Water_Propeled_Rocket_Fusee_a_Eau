#include "Program.h"

Program::Program() :   
     m_hassServer(nullptr),
     m_jsonManager(nullptr),
     m_connection(nullptr),
     m_WiFiManager(nullptr),
     m_MQTT_service(nullptr),
     m_BMP280Sensor(nullptr),
     m_ADXL345Sensor(nullptr),
      m_DS1307Clock(nullptr),        
      m_SD_Shield(nullptr),         
     m_CSV_Logger(nullptr),         
     m_actionEjectChute(nullptr),
     m_chuteManager(nullptr),
     m_speedManager(nullptr),
     m_led(nullptr),
     m_dahRocket(nullptr),
     m_isWrittingNewData(false),
     m_interval(INTERVAL_200),
     m_lastReadTime(DEFAULT_ZERO),
     m_timeCounter(DEFAULT_ZERO)
{
    this->m_jsonManager = new JSONManager();  

    if(!this->m_jsonManager->exists(JSON_FILE_PATH)) {
        this->m_WiFiManager = new WIFI_Manager(
            PORTAL_SSID,
            PORTAL_PASSWWORD,
            this->m_jsonManager
            );
    }
        
    JsonDocument configDoc = this->m_jsonManager->getConnectionsConfig(); 

    this->m_sssidWifi = configDoc["WiFiSSID"].as<String>();                         
    this->m_wifiPass = configDoc["WiFiPassword"].as<String>();                         
    this->m_hassUser = configDoc["HASSUser"].as<String>();                              
    this->m_hassPass = configDoc["HASSPasword"].as<String>();                          
    this->m_hassServer = configDoc["HASSIP"].as<const char*>();                                 

    this->m_connection = new Connection(                                  
        this->m_sssidWifi,
        this->m_wifiPass);

    if (!this->m_connection->connectToNetwork()) {                        
        this->m_WiFiManager = new WIFI_Manager(
            PORTAL_SSID,
            PORTAL_PASSWWORD,
            this->m_jsonManager);
    }

    this->m_BMP280Sensor = new BMP280Sensor();                               
    this->m_ADXL345Sensor = new ADXL345Sensor();
     this->m_DS1307Clock = new DS1307Clock();            
     this->m_SD_Shield = new SD_Shield();                
     this->m_CSV_Logger = new CSV_TelemetryLogger(       
         this->m_SD_Shield,
         this->m_DS1307Clock
     );
    this->m_speedManager = new SpeedManager(this->m_BMP280Sensor);           
    this->m_MQTT_service = new MQTT_Service(                              
        this->m_BMP280Sensor,
        this->m_ADXL345Sensor,
        this->m_speedManager,
        this->m_hassServer,
        this->m_hassPort,
        this->m_hassUser,
        this->m_hassPass,
        this->m_jsonManager,
        this->m_dahRocket);
    this->m_servoMotor = new ServoMotor();
    this->m_actionEjectChute = new ActionEjectChute(this->m_servoMotor);
    this->m_chuteManager = new ChuteManager(
        this->m_BMP280Sensor,
        this->m_speedManager,
        this->m_actionEjectChute);
        this->m_dahRocket = new Rocket();
        this->m_led = new LED(PIN_LED);
        this->m_led->light();       // Simple mais efficace , si tous les objets sont instanciés, elle s'allume (fusée prête au lancement). 
}

void Program::loop()
{
    this->m_connection->tick();
    this->m_BMP280Sensor->tick();
    this->m_ADXL345Sensor->tick();
    
    this->m_speedManager->tick();
    this->m_MQTT_service->tick();
    this->logData();
    this->m_chuteManager->tick();
}

void Program::logData() {
    if (this->m_lastReadTime + this->m_interval < millis()) {
        this->m_lastReadTime = millis();

        if(this->m_dahRocket->inFlightReady()) {
            if(!this->m_isWrittingNewData) {
                this->m_CSV_Logger->init();
                this->timeCounter = DEFAULT_ZERO;
                this->m_isWrittingNewData = true;
            }
            String time = String(this->m_timeCounter);
            String temp = String(this->m_BMP280Sensor->getTemperature());
            String alt = String(this->m_BMP280Sensor->getAltitude());
            String pres = String(this->m_BMP280Sensor->getPressure());
            String speed = this->m_speedManager->getSpeed(); 
            String z = this->m_ADXL345Sensor->getAccelAxeZ();
            String y = this->m_ADXL345Sensor->getAccelAxeY();
            String x = this->m_ADXL345Sensor->getAccelAxex();

            String flightData = time+";"+temp+";"+alt+";"+pres+";"+speed+";"+z+";"+y+";"+x;
            this->m_CSV_Logger->logData(flightData);
            this->timeCounter += m_interval;
        }
    }
}
