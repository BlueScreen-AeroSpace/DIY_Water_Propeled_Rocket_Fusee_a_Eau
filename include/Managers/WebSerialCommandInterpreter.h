#pragma once

#include <Arduino.h>
#include "DELPanelManager.h"

class WebSerialCommandInterpreter
{
private:
    const uint8_t START_MARKER = 0x7E;
    const uint8_t END_MARKER = 0x7F;
    const uint8_t ESCAPE_BYTE = 0x7D;
    
    DELPanelManager *m_delPanelManager = nullptr;
    const size_t CHUNK_SIZE = 256;

    std::vector<uint8_t> escapeData(const uint8_t* data, size_t length);
public:
    WebSerialCommandInterpreter(DELPanelManager *p_delPanelManager);
    bool interpret(const uint8_t *commandBytes);
};