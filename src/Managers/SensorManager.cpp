#include "Managers/SensorManager.h"
#include "config.h"

SensorManager::SensorManager() { ; }

void SensorManager::addSensor(Sensor *p_sensor)
{
    if (p_sensor)
    {
        this->m_sensors.push_back(p_sensor);
        p_sensor->setID(this->m_sensorCount);
        this->m_sensorCount++;
    }
}

Sensor *SensorManager::getSensor(uint8_t p_ID)
{
    if (p_ID >= MAX_SENSORS)
    {
        return nullptr;
    }

    return this->m_sensors[p_ID];
}

void SensorManager::toggleSensorState(uint8_t p_ID)
{
    if (p_ID < MAX_SENSORS)
    {
        this->m_sensors[p_ID]->toggleState();
        this->writeToConfig();
    }
}

const std::vector<Sensor *> &SensorManager::getSensors()
{
    return this->m_sensors;
}

std::vector<Sensor *> SensorManager::getActivatedSensors()
{
    std::vector<Sensor *> activatedSensors;

    for (uint8_t i = 0; i < m_sensors.size(); i++)
    {
        if (m_sensors[i]->getState())
        {
            activatedSensors.push_back(m_sensors[i]);
        }
    }

    return activatedSensors;
}

void SensorManager::writeToConfig()
{
    File file = LittleFS.open("/config.json", "w");

    if (!file)
    {
        Serial.println("Erreur : impossible d'ouvrir le fichier de configuration.");
        file.close();
        return;
    }

    JsonDocument doc;
    JsonObject rootObj = doc.to<JsonObject>();
    JsonObject sensorConfig = rootObj["sensorConfig"].to<JsonObject>();

    for (int i = 0; i < m_sensors.size(); i++)
    {
        Sensor *sensor = m_sensors[i];
        String sensorName = sensor->getName();
        JsonObject sensorObj = sensorConfig[sensorName].to<JsonObject>();
        sensorObj["active"] = m_sensors[i]->getState();
#ifdef DEBUG
        Serial.println("Capteur sauvegardé " + String(m_sensors[i]->getID()) + String(m_sensors[i]->getName()) + String(m_sensors[i]->getState()));
#endif
    }

    if (serializeJson(doc, file) == 0)
    {
#ifdef DEBUG
        Serial.println("Tentative de séréalisation des capteurs échoué...");
#endif
    }
    else
    {
#ifdef DEBUG
        Serial.println("Capteurs sauvegardés.");
#endif
    }

    file.close();
}

void SensorManager::loadSensors()
{
    File file = LittleFS.open("/config.json");

    if (!file)
    {
        Serial.println("Erreur : impossible d'ouvrir le fichier de configuration.");
        file.close();
        return;
    }

    JsonDocument doc;

    DeserializationError error = deserializeJson(doc, file);

    if (error)
    {
        Serial.println("Erreur lors de la désérialisation.");
        Serial.println(error.c_str());
        return;
    }

    JsonObject sensorConfig = doc["sensorConfig"].as<JsonObject>();

    for (int i = 0; i < this->m_sensors.size(); i++)
    {
        Sensor *sensor = this->m_sensors[i];
        bool isActive = sensorConfig[sensor->getName()]["active"].as<bool>();

        sensor->setState(isActive);
#ifdef DEBUG
        Serial.println("Sensor " + sensor->getName() + " set to state" + String(isActive));
#endif
    }
}
