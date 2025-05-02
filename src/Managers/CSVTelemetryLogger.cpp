#include "Managers/CSVTelemetryLogger.h"
#include "Logs/DataLogger.h"

// Constructeur de télimétrie de fichier CSV.
CSV_TelemetryLogger::CSV_TelemetryLogger(
    SD_Shield *p_sdShield,
    DS1307Clock *p_DS1307Clock,
    ConfigManager *p_configManager)
    : m_sdShield(p_sdShield),
      m_DS1307Clock(p_DS1307Clock),
      m_fileName(EMPTY),
      m_header(EMPTY),
      m_configManager(p_configManager)   
{
    init();
}

// Fonction qui initie la création de l'entête et du fichier CSV.
void CSV_TelemetryLogger::init()
{
    createFileName();
    createCSVHeader();
    Logger.log("Module CSVTelemetryLogger initialisé.");
}

// Fonction qui crée le nom du fichier CSV.
void CSV_TelemetryLogger::createFileName()
{
    if (m_DS1307Clock)
    {
        String currentDateTime = "/" + this->m_DS1307Clock->getActualDateTime();
        if (currentDateTime.length() > 1)
        {
            this->m_fileName = currentDateTime + CSV;
            return;
        }
    }
    this->m_fileName = DEFAULT_FILENAME;
}

// Fonction qui crée l'entête du fichier CSV.
void CSV_TelemetryLogger::createCSVHeader()
{
    if (m_sdShield)
    {
        this->m_header = "time;";
        std::vector<String> dataTypesChosen = this->m_configManager->getDataTypesChosen();

        for (uint8_t i = 0; i < dataTypesChosen.size(); i++)
        {
            if (dataTypesChosen[i] == "Température")
            {
                m_header += "temperature;";
            }
            else if (dataTypesChosen[i] == "Humidité")
            {
                m_header += "humidity;";
            }
            else if (dataTypesChosen[i] == "Altitude")
            {
                m_header += "altitude;";
            }
            else if (dataTypesChosen[i] == "Pression Atmosphérique")
            {
                m_header += "pressure;";
            } 
            else if (dataTypesChosen[i] == "Accélération")
            {
                m_header += "axeX;axeY;axeZ;";
            }
        }

        m_header += "speed;";

        this->m_sdShield->writeFile(m_fileName, m_header);
        return;
    }
    this->m_sdShield->writeFile(m_fileName, "Attention : erreur lors de l'écriture du header.");
}

// Fonction qui écrit dans le fichier CSV les données de lecture du BME280.
void CSV_TelemetryLogger::logData(String p_data)
{
    if (m_sdShield)
    {
        this->m_sdShield->writeFile(m_fileName, p_data);
        return;
    }
    this->m_sdShield->writeFile(m_fileName, "Attention : erreur lors de l'écriture des données.");
}

// Ok, basique, mais devrait fonctionner. À l'utilisation:
// 1- (pointeur) m_CSVLogger->init(); m_fileName et m_header créés.
// 2- on envois les lignes: boucle à tout les 500ms (exemple) - m_CSVLogger->logData(time, m_temperature, m_altitude, m_pressure);
// À voir si les données "float" sortiront avec des "," ou des "." Si "."  CSV sera séparé par "," comme originalement sinon ";"
// Le "GO" devrait être déclenché à distance vis HASS pour 1- couper le wifi (fusée va se retrouver hors porté anyway),
// 2- lancer la boucle de log (méthodes 1- et 2- si dessus).
// cette classe devrait donc me créer des fichier .CSV avec comme nom: la date, header: spécifié dans config.h et données des modules embarqués.
