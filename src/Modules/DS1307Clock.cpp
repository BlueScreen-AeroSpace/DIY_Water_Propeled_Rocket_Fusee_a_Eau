#include "Modules/DS1307Clock.h"
#include "config.h"
#include "Logs/DataLogger.h"

// Source utilisation et méthodes librairie: adafruit/RTClib@^2.1.4 depuis "PIO Home/Librairies".
// Filage et utilisation: https://www.instructables.com/Using-the-Wifi-D1-Mini-Real-time-Clock-and-Logger/

// Constructeur de l'heure actuel.
DS1307Clock::DS1307Clock() : m_lastReadTime()
{
    Sensor::setName("DS1307");

    if (!this->m_RTC.begin())
    {
        Logger.error("Incapable de démarrer le module DS1307. Vérifiez le câblage.");
        Sensor::m_isActive = false;
    }
    Logger.log("Module DS1307 initialisé avec succès");
    Sensor::m_isActive = true;  
}

// Fonction qui rafraîchie le temps.
void DS1307Clock::refreshTime()               // L'idée derrière cette méthode est de mettre à jours la donnée membre.
                                              // 1- Permet d'alléger le code et d'éviter de répéter "m_RTC.now();" dans toutes les méthodes.
{                                             // 2- Cohérence des données. Si on appel en succession, exemple besoin de minute et seconde,
    this->m_lastReadTime = this->m_RTC.now(); // le temps pourrait avoir le temp de changer. Exemple temp réel à l'appel 2:59 et résultat 2:00.
                                              // Appel de minute (2) à 2:59 et appel de seconde (00) à 3:00 donc résultat 2:00 au lieu de 2:59.
                                              // Donc avant d'appeler une série de méthodes qui retourne uintx_t, on doit appeler refreshTime().
}

// Fonction qui retourne la date et l'heure actuel en String.
String DS1307Clock::getActualDateTime()
{
    if (!Sensor::m_isActive)
    {
        return "0000-00-00T00m00s00";
    }
    // Format: 2025-01-18T03m35s29
    refreshTime(); // Pour des appels de date ou heure préformatés, refreshTime() est appelé automatiquement.
    String dateString = String(this->m_lastReadTime.year()) + "-" +
                        formatTwoDigits(this->m_lastReadTime.month()) + "-" +
                        formatTwoDigits(this->m_lastReadTime.day()) + "T" +
                        formatTwoDigits(this->m_lastReadTime.hour()) + "m" +
                        formatTwoDigits(this->m_lastReadTime.minute()) + "s" +
                        formatTwoDigits(this->m_lastReadTime.second());
    return dateString;
}
// Fonction qui retourne la date actuel en String.
String DS1307Clock::getActualDate()
{
    // Format: 2025-01-18
    refreshTime();
    String dateString = String(this->m_lastReadTime.year()) + "-" +
                        String(this->m_lastReadTime.month()) + "-" +
                        String(this->m_lastReadTime.day());
    return dateString;
}
// Fonction qui retourne l'heure actuel avec les secondes en String.
String DS1307Clock::getActualTime()
{
    // Format: 03:35:29
    refreshTime();
    String timeString = formatTwoDigits(this->m_lastReadTime.hour()) + "m" +
                        formatTwoDigits(this->m_lastReadTime.minute()) + "s" +
                        formatTwoDigits(this->m_lastReadTime.second());
    return timeString;
}
// Fonction qui retourne l'heure actuel sans les secondes en String.
String DS1307Clock::getActualTimeNoSec()
{
    // Format: 03:35
    refreshTime();
    String timeString = formatTwoDigits(this->m_lastReadTime.hour()) + ":" +
                        formatTwoDigits(this->m_lastReadTime.minute());
    return timeString;
}

// Fonction qui retourne un nombre en format deux digit en String.
String DS1307Clock::formatTwoDigits(uint8_t p_number)
{
    // Format: 01:00:00
    if (p_number < 10)
    {
        return "0" + String(p_number);
    }
    return String(p_number);
}

void DS1307Clock::setActualDateAndTime(const String& dateTimeStr)
{
    int year = dateTimeStr.substring(0, 4).toInt();
    int month = dateTimeStr.substring(5, 7).toInt();
    int day = dateTimeStr.substring(8, 10).toInt();
    int hour = dateTimeStr.substring(11, 13).toInt();
    int minute = dateTimeStr.substring(14, 16).toInt();
    int second = dateTimeStr.substring(17, 19).toInt();

    DateTime newDateTime(year, month, day, hour, minute, second);
    this->m_RTC.adjust(newDateTime);
}