#include "Managers/CSV_TelemetryLogger.h"

CSV_TelemetryLogger::CSV_TelemetryLogger(
    SD_Shield* p_sdShield,
    DS1307Clock* p_DS1307Clock
    )
      : m_sdShield(p_sdShield),
        m_DS1307Clock(p_DS1307Clock),
        m_fileName(EMPTY),
        m_header(EMPTY)  {

}   

void CSV_TelemetryLogger::init() {
    createFileName();
    createCSVHeader(CSV_TELEMETRY_HEADER);
}
void CSV_TelemetryLogger::createFileName() {
    String currentDateTime = "/" + this->m_DS1307Clock->getActualDateTime();
    this->m_fileName = currentDateTime + CSV;
}
void CSV_TelemetryLogger::createCSVHeader(String p_header) {
    this->m_header = p_header;
    this->m_sdShield->writeFile(m_fileName, m_header);
}
void CSV_TelemetryLogger::logData(String p_data) {
    this->m_sdShield->writeFile(m_fileName, p_data);
}

// Ok, basique, mais devrait fonctionner. À l'utilisation: 
// 1- (pointeur) m_CSVLogger->init(); m_fileName et m_header créés.
// 2- on envois les lignes: boucle à tout les 500ms (exemple) - m_CSVLogger->logData(time, m_temperature, m_altitude, m_pressure);
// À voir si les données "float" sortiront avec des "," ou des "." Si "."  CSV sera séparé par "," comme originalement sinon ";"
// Le "GO" devrait être déclenché à distance vis HASS pour 1- couper le wifi (fusée va se retrouver hors porté anyway), 
// 2- lancer la boucle de log (méthodes 1- et 2- si dessus).
// cette classe devrait donc me créer des fichier .CSV avec comme nom: la date, header: spécifié dans config.h et données des modules embarqués.
