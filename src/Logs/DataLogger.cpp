#include "Logs/DataLogger.h"

DataLogger Logger;

void DataLogger::log(const String& log)
{
    Serial.println("Log: " + log);
    this->logs.push_back({LogType::Message, log});
}

void DataLogger::error(const String& error)
{
    Serial.println("Error: " + error);
    this->logs.push_back({LogType::Error, error});
}

const std::vector<LogEntry>& DataLogger::getLogs() const
{
    return this->logs;
}