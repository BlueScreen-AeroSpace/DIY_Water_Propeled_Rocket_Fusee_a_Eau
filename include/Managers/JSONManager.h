#pragma once
#include <ArduinoJson.h>
#include <LittleFS.h>
#include "const.h"

class JSONManager {
private:
public:
    bool exists(const char* p_filePath);
    JSONManager();    
    void write(const char* p_filePath, const JsonDocument& p_doc);
    JsonDocument read(const char* p_filePath);
    void remove(const char* p_filePath);  
    JsonDocument getConnectionsConfig();
};