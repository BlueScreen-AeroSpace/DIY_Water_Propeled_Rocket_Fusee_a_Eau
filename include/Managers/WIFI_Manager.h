#pragma once 
#include <Arduino.h>
#include <WiFiManager.h>
#include <uri/UriRegex.h>
#include "const.h"
#include "JSONManager.h"

class WIFI_Manager {
private:   
    char const* m_portalSSID;
    char const* m_portalPassWord;    
    WiFiManager m_WiFiManager;   
    uint8_t m_timeout;
    bool m_debugOutput;
    JSONManager* m_JSONManager;
    IPAddress m_portalIP;
    IPAddress m_gatewayIP;
    IPAddress m_portalMask;
    WiFiManagerParameter m_HASS_USER;
    WiFiManagerParameter m_HASS_PASS;
    WiFiManagerParameter m_HASS_IP;
    WiFiManagerParameter m_HASS_PORT;
    void setupManager();

public:
    WIFI_Manager(
        char const* p_portalSSID,
        char const* p_portalPassWord,  
        JSONManager* p_JSONManager
        );
    void toggleDebugMode();
    void startConfigPortal();
    void eraseWIFIConfig();
    void tick();
};
