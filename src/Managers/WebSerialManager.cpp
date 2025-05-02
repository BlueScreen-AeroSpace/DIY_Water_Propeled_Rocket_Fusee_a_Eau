#include "Managers/WebSerialManager.h"
#include "Logs/DataLogger.h"

WebSerialManager::WebSerialManager(WebSerialCommandInterpreter *p_commandInterpreter)
{
    m_commandInterpreter = p_commandInterpreter;
    Logger.log("Module WebSerialManager initialisé");
}

void WebSerialManager::tick()
{
    if (Serial.available())
    {
        String data = Serial.readStringUntil('\n');
        JsonDocument document;

        DeserializationError error = deserializeJson(document, data);

        if (error)
        {
            Logger.error(String("deserializeJson() failed: ") + error.c_str());
            return;
        }
        String command = document["command"].as<String>();
        JsonArray arguments = document["arguments"].as<JsonArray>();

        m_commandInterpreter->interpret(command, arguments);
    }
}
