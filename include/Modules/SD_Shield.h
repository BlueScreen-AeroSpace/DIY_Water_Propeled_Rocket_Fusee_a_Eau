#pragma once
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <Arduino.h>
#include "const.h"

class SD_Shield {
private:
    uint8_t m_CSPin;        // Décidé de passer la pin CS à l'intérieur via mon fichier const.h
public:
    SD_Shield();
    void writeFile(
        const String& p_fileName, 
        const String& p_data
        );    
    String readFile(const String& p_fileName);
};
