#pragma once
#include "WebSerialCommandInterpreter.h"
#include <ArduinoJson.h>

class WebSerialManager
{
private:
    WebSerialCommandInterpreter *m_commandInterpreter;

public:
    WebSerialManager(WebSerialCommandInterpreter *p_commandInterpreter);
    void tick();
};