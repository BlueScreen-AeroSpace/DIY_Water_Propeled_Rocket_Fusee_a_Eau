#include "Managers/JSONManager.h"

JSONManager::JSONManager()
{
    LittleFS.begin(true);
}

bool JSONManager::exists(const char *p_filePath)
{
    return LittleFS.exists(p_filePath);
}

void JSONManager::write(const char *p_filePath, const JsonDocument &p_doc)
{

    File file = LittleFS.open(p_filePath, FILE_WRITE);
    if (!file)
    {
        Serial.println(String("Erreur : Impossible d'ouvrir le fichier pour écrire: ") + p_filePath);
        return;
    }

    if (serializeJson(p_doc, file) == 0)
    {
        Serial.println("Erreur : Échec de l'écriture dans le fichier!");
        file.close();
        return;
    }

    file.close();
    Serial.println(String("Fichier écrit avec succès: ") + p_filePath);
}

JsonDocument JSONManager::read(const char *p_filePath)
{
    JsonDocument doc;

    if (!exists(p_filePath))
    {
        Serial.println("Erreur : Le fichier n'existe pas!");
        doc = "error";
        return doc;
    }

    File file = LittleFS.open(p_filePath, FILE_READ);
    if (!file)
    {
        Serial.println(String("Erreur : Impossible d'ouvrir le fichier pour lecture: ") + p_filePath);
        doc = "error";
        return doc;
    }

    DeserializationError error = deserializeJson(doc, file);
    file.close();
    if (error)
    {
        Serial.println(String("Erreur : Échec de la désérialisation JSON: ") + error.c_str());
        doc = "error";
        return doc;
    }

    return doc;
}

void JSONManager::remove(const char *p_filePath)
{

    if (!exists(p_filePath))
    {
        Serial.println(String("Erreur : Le fichier n'existe pas: ") + p_filePath);
        return;
    }
    if (!LittleFS.remove(p_filePath))
    {
        Serial.println(String("Erreur : Échec de la suppression du fichier: ") + p_filePath);
        return;
    }

    Serial.println(String("Fichier supprimé avec succès: ") + p_filePath);
}

JsonDocument JSONManager::getConnectionsConfig()
{
    JsonDocument config;
    File configFile = LittleFS.open(JSON_FILE_PATH, FILE_READ);

    if (!configFile)
    {  
        Serial.println(String("Erreur : Impossible d'ouvrir le fichier de config pour lecture"));
        return config;
    }

    JsonDocument doc;

    DeserializationError error = deserializeJson(doc, configFile);
    configFile.close();
    if (error)
    {
        Serial.println(String("Erreur : Échec de la désérialisation JSON: ") + error.c_str());
        return config;
    }

    config["WiFiSSID"] = doc["WiFiSSID"];
    config["WiFiPassword"] = doc["WiFiPassword"];

    config["HASSUser"] = doc["HASSUser"];
    config["HASSPasword"] = doc["HASSPasword"];
    config["HASSIP"] = doc["HASSIP"];
    config["HASSPORT"] = doc["HASSPORT"];

    return config;
}