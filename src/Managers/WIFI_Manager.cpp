#include "Managers/WIFI_Manager.h"
#include "config.h"

WIFI_Manager::WIFI_Manager(
    char const *p_portalSSID,
    char const *p_portalPassWord,
    JSONManager *p_JSONManager) : m_portalSSID(p_portalSSID),
                                  m_portalPassWord(p_portalPassWord),
                                  m_timeout(TIMEOUT),
                                  m_debugOutput(false),
                                  m_JSONManager(p_JSONManager),
                                  // déclaré à l'interne:
                                  m_portalIP(192, 168, 24, 1),
                                  m_gatewayIP(192, 168, 24, 1),
                                  m_portalMask(255, 255, 255, 0),
                                  m_HASS_USER(HASS_USER_PARAM_1, HASS_USER_PARAM_2, HASS_USER_PARAM_3, HASS_USER_PARAM_4),
                                  m_HASS_PASS(HASS_PASS_PARAM_1, HASS_PASS_PARAM_2, HASS_PASS_PARAM_3, HASS_PASS_PARAM_4),
                                  m_HASS_IP(HASS_IP_PARAM_1, HASS_IP_PARAM_2, HASS_IP_PARAM_3, HASS_IP_PARAM_4),
                                  m_HASS_PORT(HASS_PORT_PARAM_1, HASS_PORT_PARAM_2, HASS_PORT_PARAM_3, HASS_PORT_PARAM_4)
{
    this->m_WiFiManager.resetSettings();
    setupManager();
    //   Serial.println("WiFi SSID dans param de wifiman : ");
    // Serial.println(String(WiFi.SSID()));
    JsonDocument jsonDoc;

    jsonDoc["WiFiSSID"] = WiFi.SSID();
    // Serial.println("WiFi SSID dans jsonDoc : ");
    // Serial.println(jsonDoc["WiFiSSID"].as<String>());
    jsonDoc["WiFiPassword"] = WiFi.psk();
    jsonDoc["HASSUser"] = this->m_HASS_USER.getValue();

    jsonDoc["HASSPasword"] = this->m_HASS_PASS.getValue();
    jsonDoc["HASSIP"] = this->m_HASS_IP.getValue();
    jsonDoc["HASSPORT"] = this->m_HASS_PORT.getValue();

    this->m_JSONManager->write(JSON_FILE_PATH, jsonDoc);
    ESP.restart();
}

void WIFI_Manager::setupManager()
{
    this->m_WiFiManager.setDebugOutput(this->m_debugOutput);
    this->m_WiFiManager.setAPCallback([](WiFiManager *p_wiFiManager)
                                      { Serial.println("Échec config. Lancement portail"); });
    this->m_WiFiManager.setConfigPortalTimeout(this->m_timeout);

    this->m_WiFiManager.setSaveParamsCallback([this]() {});

    this->m_WiFiManager.addParameter(&this->m_HASS_USER);
    this->m_WiFiManager.addParameter(&this->m_HASS_PASS);
    this->m_WiFiManager.addParameter(&this->m_HASS_IP);
    this->m_WiFiManager.addParameter(&this->m_HASS_PORT);

    this->m_WiFiManager.setAPStaticIPConfig(
        this->m_portalIP,
        this->m_gatewayIP,
        this->m_portalMask);

    this->m_WiFiManager.setParamsPage(true);
    this->m_WiFiManager.autoConnect(
        this->m_portalSSID,
        this->m_portalPassWord);

    Serial.println(WiFi.localIP());
}
