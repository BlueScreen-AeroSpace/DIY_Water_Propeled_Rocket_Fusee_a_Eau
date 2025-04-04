#include "Managers/WebManager.h"
#include "WebServer.h"
#include "LittleFS.h"

WebManager::WebManager(SensorManager *p_sensorManager)
{
    m_webserver = new WebServer(80);
    m_sensorManager = p_sensorManager;
    m_webserver->on("/", [this]()
                    { this->handleRoot(); });

    m_webserver->on("/api/sensors", HTTP_GET, [this]()
                    {
        String jsonResponse = "[";
        std::vector<Sensor*> sensors = m_sensorManager->getSensors();
        
        for(size_t i = 0; i < sensors.size(); i++) {
            if(i > 0) {
                jsonResponse += ",";
            }
            jsonResponse += "{";
            jsonResponse += "\"id\":" + String(sensors[i]->getID()) + ",";
            jsonResponse += "\"state\":" + String(sensors[i]->getState() ? "true" : "false") + ",";
            jsonResponse += "\"name\":\"" + sensors[i]->getName() + "\"";
            jsonResponse += "}";
        }
        jsonResponse += "]";
        
        // Add CORS headers
        m_webserver->sendHeader("Access-Control-Allow-Origin", "*");
        m_webserver->sendHeader("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        m_webserver->sendHeader("Access-Control-Allow-Headers", "Content-Type");
        
        m_webserver->send(200, "application/json", jsonResponse); });

    // Handle OPTIONS requests for CORS preflight
    m_webserver->on("/api/sensors", HTTP_OPTIONS, [this]() {
        m_webserver->sendHeader("Access-Control-Allow-Origin", "*");
        m_webserver->sendHeader("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        m_webserver->sendHeader("Access-Control-Allow-Headers", "Content-Type");
        m_webserver->send(204);
    });

    m_webserver->on("/api/sensors", HTTP_PUT, [this]()
                    {
        // Add CORS headers
        m_webserver->sendHeader("Access-Control-Allow-Origin", "*");
        m_webserver->sendHeader("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        m_webserver->sendHeader("Access-Control-Allow-Headers", "Content-Type");
        
        if (!m_webserver->hasArg("plain")) {
            m_webserver->send(400, "text/plain", "Missing body");
            return;
        }

        String body = m_webserver->arg("plain");
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, body);

        if (error) {
            m_webserver->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
            return;
        }

        if (!doc["id"].is<uint8_t>() || !doc["state"].is<bool>()) {
            m_webserver->send(400, "application/json", "{\"error\":\"Missing id or state in body\"}");
            return;
        }

        uint8_t id = doc["id"];
        bool newState = doc["state"];

        Sensor* sensor = m_sensorManager->getSensor(id);
        if (!sensor) {
            m_webserver->send(404, "application/json", "{\"error\":\"Sensor not found\"}");
            return;
        }

        if (newState != sensor->getState()) {
            m_sensorManager->toggleSensorState(id);
        }

        m_webserver->send(200); });

    m_webserver->serveStatic("/capteurs.js", LittleFS, "/capteurs.js");
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

void WebManager::loop()
{
    m_webserver->handleClient();
}