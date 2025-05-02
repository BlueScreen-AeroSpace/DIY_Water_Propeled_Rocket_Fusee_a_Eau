#pragma once

#include <Arduino.h>
#include "DELPanelManager.h"

class WebSerialCommandInterpreter
{
private:
    DELPanelManager *m_delPanelManager = nullptr;
public:
    WebSerialCommandInterpreter(DELPanelManager *p_delPanelManager);
    bool interpret(const String& command, const JsonArray& arguments);
    void sendMessage(const String& message);
};