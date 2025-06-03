#include "Managers/WebSerialManager.h"
#include "Logs/DataLogger.h"

WebSerialManager::WebSerialManager(WebSerialCommandInterpreter *p_commandInterpreter)
{
    m_commandInterpreter = p_commandInterpreter;
    Logger.log("Module WebSerialManager initialisé");
}

void WebSerialManager::tick()
{
    if (Serial.available() >= 2)
    {
        uint16_t totalLength = (Serial.read() << 8) | Serial.read();

        uint8_t* buffer = new (std::nothrow) uint8_t[totalLength];
        if (!buffer)
        {
            Logger.log("Buffer allocation failed");
            return;
        }
        uint16_t bytesRead = 0;
        unsigned long startTime = millis();

        while (bytesRead < totalLength && millis() - startTime < 10000)
        {
            if (Serial.available())
            {
                buffer[bytesRead++] = Serial.read();
            }
        }

        if (bytesRead == totalLength)
        {
            
            m_commandInterpreter->interpret(buffer);
            Logger.log("Full message received: " + String(bytesRead));
        }
        else
        {
            Logger.log("Timeout or incomplete message");
        }

        
    }
}
