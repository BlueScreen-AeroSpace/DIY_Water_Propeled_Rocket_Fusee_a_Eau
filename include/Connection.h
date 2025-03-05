#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include "const.h"
#include "config.h"

class Connection
{
private:
    uint16_t m_lastUpdate;
    uint16_t m_intervalUpdate;
    String m_url;
    bool m_isConnected;
    String m_ssid;
    String m_password;

public:
    Connection(
        String p_ssid,
        String p_password
    );
    bool isConnected();
    bool connectToNetwork();
    String getURL();
    void tick();
};