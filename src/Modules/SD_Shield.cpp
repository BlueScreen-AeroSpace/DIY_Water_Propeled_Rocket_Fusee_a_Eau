#include "Modules/SD_Shield.h"
#include "config.h"

// Source utilisation et méthodes librairie: arduino-libraries/SD@^1.3.0 depuis "PIO Home/Librairies".
// Filage et utilisation: https://www.instructables.com/Using-the-Wifi-D1-Mini-Real-time-Clock-and-Logger/

// Constructeur de la carte SD
SD_Shield::SD_Shield()
{
    if (!Wire.begin())
    {
        Serial.println("SD_SHIELD n'a pas pu être démarré");
    }
    
    SPI.begin();
    if (!SD.begin())
    {
        Serial.println("Incapable de démarrer le Data loggar shield. Vérifiez le câblage.");
#ifndef DEBUG
        while (true)
            ;
#endif
    }
    Serial.println("Data logger shield initialisée avec succès !");
}

// Méthode afin d'écrire dans un fichier de la carte SD.
void SD_Shield::writeFile(
    const String &p_fileName,
    const String &p_data)
{
    File dataFile = SD.open(p_fileName, FILE_APPEND);
    if (dataFile)
    {
        dataFile.println(p_data);
        dataFile.close();
        Serial.println("Écriture réussie dans " + p_fileName);
    }
    else
    {
        Serial.println("Impossible d'ouvrir " + p_fileName);
    }
}

// Méthode afin de lire dans un fichier de la carte SD.
String SD_Shield::readFile(const String &p_fileName)
{
    File dataFile = SD.open(p_fileName, FILE_READ);
    String fileContent = "";

    if (dataFile)
    {
        while (dataFile.available())
        {
            fileContent += char(dataFile.read());
        }
        dataFile.close();
        Serial.println("Lecture réussie de " + p_fileName);
    }
    else
    {
        Serial.println("Erreur: impossible d'ouvrir le fichier " + p_fileName);
    }

    return fileContent;
}
