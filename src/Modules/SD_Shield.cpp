#include "Modules/SD_Shield.h"

// Source utilisation et méthodes librairie: arduino-libraries/SD@^1.3.0 depuis "PIO Home/Librairies".
// Filage et utilisation: https://www.instructables.com/Using-the-Wifi-D1-Mini-Real-time-Clock-and-Logger/

SD_Shield::SD_Shield() {
    Wire.begin();
    SPI.begin();
    if (!SD.begin()) {                               
    Serial.println("Incapable de démarrer le Data loggar shield. Vérifiez le câblage.");
    while(true);
    }
    Serial.println("Data loggar shield initialisée avec succès !");
}

void SD_Shield::writeFile(
    const String& p_fileName, 
    const String& p_data
    ) {
        File dataFile = SD.open(p_fileName, FILE_APPEND);    
        if (dataFile) {
            dataFile.println(p_data);  
            dataFile.close();
            Serial.println("Écriture réussie dans " + p_fileName); 
        } else {
            Serial.println("Impossible d'ouvrir " + p_fileName); 
        }
}
String SD_Shield::readFile(const String& p_fileName) {
    File dataFile = SD.open(p_fileName, FILE_READ);         
    String fileContent = "";

    if (dataFile) {
        while (dataFile.available()) {
            fileContent += char(dataFile.read());  
        }
        dataFile.close();                                   
        Serial.println("Lecture réussie de " + p_fileName);
    } else {
        Serial.println("Erreur: impossible d'ouvrir le fichier " + p_fileName);
    }

    return fileContent;  
}
