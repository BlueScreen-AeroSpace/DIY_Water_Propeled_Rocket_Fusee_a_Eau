#pragma once
#include <Arduino.h>
#include <map>
#include "LogType.h"
#include <vector>

struct LogEntry {
    LogType type;
    String message;
};

class DataLogger {
    public:
        void error(const String& error);
        void log(const String& log);

        const std::vector<LogEntry>& getLogs() const; 
    private:
        std::vector<LogEntry> logs;
};

extern DataLogger Logger;