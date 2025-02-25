#include "MQTT_Service.h"

MQTT_Service::MQTT_Service(
    BMP280Sensor* p_BMP280Sensor,
    ADXL345Sensor* p_ADXL345Sensor,
    SpeedManager* p_speedManager,
    const char* p_hassServer,
    uint16_t p_hassPort,
    String p_hassUser,
    String p_hassPass,
    JSONManager* p_jsonManager,
    Rocket* p_rocket
    )
      : 
        m_BMP280Sensor(p_BMP280Sensor),                 
        m_ADXL345Sensor(p_ADXL345Sensor),
        m_speedManager(p_speedManager),
        m_hassServer(p_hassServer),
        m_hassPort(p_hassPort),
        m_hassUser(p_hassUser),
        m_hassPass(p_hassPass),
        m_espClient(nullptr),     
        m_pubSubClient(nullptr),
        m_discoverySent(false),
        m_jsonManager(p_jsonManager),
        m_rocket(p_rocket) {  
        setupMQTT();           
    }

void MQTT_Service::setupMQTT() {    
    m_espClient = new WiFiClient(); 
    m_pubSubClient = new PubSubClient(*m_espClient);    
    m_pubSubClient->setBufferSize(1024);       
    m_pubSubClient->setServer(m_hassServer, m_hassPort); 
    m_espUnique = String("ESP32Client") + String(ESP.getEfuseMac(), HEX);
    m_lastSentMessageTime = DEFAULT_ZERO;   
    m_interval = INTERVAL_5;   
    m_sensorDiscovery = new SensorDiscovery(this->m_pubSubClient);
} 

bool MQTT_Service::reconnectMQTTIfNeeded() {    
    if (!m_pubSubClient->connected()) { 
        if(m_pubSubClient->connect(m_espUnique.c_str(), m_hassUser.c_str(), m_hassPass.c_str(),
                                  (m_espUnique + "/status").c_str(), 0, 0,"offline")) {
            Serial.println("Connecté au broker MQTT");
            m_pubSubClient->publish((m_espUnique + "/status").c_str(), "online");
            m_pubSubClient->subscribe(SWITCH_TOPIC);
            m_pubSubClient->setCallback(
                [](char*topic, byte*payload, uint16_t length) {
                     Serial.print("Message reçu...");
                });
            listenBroadcast();
            if (!this->m_discoverySent)
            {
                this->m_sensorDiscovery->createSensorsViaMSGDiscovery();
                m_discoverySent = true; 
            }
        } else {
             Serial.print("Echec de connexion au broker MQTT : ");
             this->m_jsonManager->remove(JSON_FILE_PATH);
             ESP.restart();
        }
    }
    return m_pubSubClient->connected();
}

void MQTT_Service::publishData() {
    uint64_t messageId = DEFAULT_ZERO;
    if (reconnectMQTTIfNeeded()) {
        m_pubSubClient->loop(); 
        if (m_lastSentMessageTime + m_interval < millis()) { 
            m_lastSentMessageTime = millis();      

            this->m_pubSubClient->publish(TEMP_TOPIC, 
                                    String(this->m_BMP280Sensor->getTemperature()).c_str());
            this->m_pubSubClient->publish(PRESSURE_TOPIC, 
                                    String(this->m_BMP280Sensor->getPressure()).c_str());
            this->m_pubSubClient->publish(ALTITUDE_TOPIC, 
                                    String(this->m_BMP280Sensor->getAltitude()).c_str());        
            this->m_pubSubClient->publish(AXEX_TOPIC, 
                                    String(this->m_ADXL345Sensor->getAccelAxeX()).c_str());
            this->m_pubSubClient->publish(AXEY_TOPIC, 
                                    String(this->m_ADXL345Sensor->getAccelAxeY()).c_str());
            this->m_pubSubClient->publish(AXEZ_TOPIC, 
                                    String(this->m_ADXL345Sensor->getAccelAxeZ()).c_str());
            this->m_pubSubClient->publish(SPEED_TOPIC, 
                                    String(this->m_speedManager->getSpeed()).c_str());
        }
    }
}

void MQTT_Service::listenBroadcast() {
    this->m_pubSubClient->setCallback(
        [this](char*topic, byte*payload, uint16_t length) {
        String payloadString = EMPTY;
        for (uint8_t i = 0; i < length; ++i) {
            payloadString += (char)payload[i];
        }
        if (String(topic) == SWITCH_TOPIC) {
            toggleReadyToLaunch(payloadString);
        }
    });
}

void MQTT_Service::toggleReadyToLaunch(String p_payload) {
    if (p_payload == "ON") {
        this->m_rocket->setIsInFlight(true);
        this->m_pubSubClient->publish(SWITCH_CONFIRMATION_TOPIC,"ON received");
    }
    else if (p_payload == "OFF") {
        this->m_rocket->setIsInFlight(false);
        this->m_pubSubClient->publish(SWITCH_CONFIRMATION_TOPIC,"OFF received");
    }
}

void MQTT_Service::tick() {
    publishData();
}
