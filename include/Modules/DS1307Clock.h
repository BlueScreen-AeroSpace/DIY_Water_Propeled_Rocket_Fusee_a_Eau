#pragma once
#include "Modules/Sensor.h"
#include <RTClib.h>
#include <Arduino.h>
#include "const.h"

class DS1307Clock : public Sensor {
private:
    RTC_DS1307 m_RTC;
    DateTime m_lastReadTime;
    uint16_t m_interval;
    String formatTwoDigits(uint8_t p_number);
    public:
    void setActualDateAndTime(const String& p_dateAndTime);
    DS1307Clock();
    void refreshTime();
    String getActualDateTime(); 
    String getActualDate(); 
    String getActualTime();  
    String getActualTimeNoSec();
};
// Une méthode pour mettre la date désiré peut être ajouté pour créer un affichage de date/heure à une valeur désirée.
// Une méthode pour remettre le temp à jour au semaine, mois années pourrait être ajouté.
// Des méthodes de temps écoulé depuis une date en particulier, années, mois etc peuvent être ajouté.
// Voir lib adafruit/RTClib@^2.1.4
