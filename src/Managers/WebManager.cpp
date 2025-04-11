#include "Managers/WebManager.h"
#include "WebServer.h"
#include "LittleFS.h"

WebManager::WebManager(ConfigManager *p_configManager)
{
    m_webserver = new WebServer(80);
    m_configManager = p_configManager;
    m_webserver->on("/", [this]()
                    { this->handleRoot(); });

    m_webserver->on("/api/config", HTTP_POST, [this]()
                    { this->sendConfigToManager(); });

    m_webserver->serveStatic("/script.js", LittleFS, "/script.js");
    m_webserver->serveStatic("/bootstrap/js/bootstrap.min.js", LittleFS, "/bootstrap/js/bootstrap.min.js");
    m_webserver->serveStatic("/bootstrap/css/bootstrap.min.css", LittleFS, "/bootstrap/css/bootstrap.min.css");
    m_webserver->serveStatic("/bootstrap/js/bootstrap.min.js.map", LittleFS, "/bootstrap/js/bootstrap.min.js.map");
    m_webserver->serveStatic("/bootstrap/css/bootstrap.min.css.map", LittleFS, "/bootstrap/css/bootstrap.min.css.map");

    m_webserver->onNotFound([this]()
                            { Serial.println(this->m_webserver->uri()); });

    m_webserver->begin();
}

void WebManager::handleRoot()
{
    File file = LittleFS.open("/index.html", "r");
    if (!file)
    {
        m_webserver->send(500, "text/plain", "Failed to open index.html");
        Serial.println("Failed to open index.html");
        return;
    }

    m_webserver->streamFile(file, "text/html");
    file.close();
}

#include <ArduinoJson.h>

void WebManager::sendConfigToManager()
{
    String jsonRequest = this->m_webserver->arg("plain");

    JsonDocument doc;

    std::vector<String> sensorsToInit = {};
    std::vector<String> dataTypesChosen = {};

    DeserializationError error = deserializeJson(doc, jsonRequest);
    Serial.println("Requête POST reçue !");

    if (!error)
    {

        JsonArray sensorsName = doc["capteurs"].as<JsonArray>();
        for (JsonVariant sensor : sensorsName)
        {
            sensorsToInit.push_back(sensor.as<String>());
            Serial.println(sensor.as<String>());
        }

        JsonArray datasName = doc["donnees"].as<JsonArray>();
        for (JsonVariant dataName : datasName)
        {
            dataTypesChosen.push_back(dataName.as<String>());
            Serial.println(dataName.as<String>());
        }

        this->m_configManager->setDateAndTimeToInit(doc["dateEtHeure"]);
        this->m_configManager->setSensorsToInit(sensorsToInit);
        this->m_configManager->setDataTypesChosen(dataTypesChosen);

        JsonDocument responseDoc;
        responseDoc["Status"] = "success";
        responseDoc["message"] = "Configuration traitée";
        String responseJson;
        serializeJson(responseDoc, responseJson);

        this->m_webserver->send(200, "application/json", responseJson);
    }
    else
    {
        Serial.println("Erreur de désérialisation JSON : " + String(error.c_str()));
        this->m_webserver->send(400, "application/json", R"({"status":"error","message":"JSON invalide"})");
    }

    this->m_configManager->notifyConfigReceived();
}

void WebManager::loop()
{
    m_webserver->handleClient();
}