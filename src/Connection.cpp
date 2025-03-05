#include "Connection.h"

Connection::Connection(
    String p_ssid,
    String p_pass)
    : m_ssid(p_ssid),
      m_password(p_pass),
      m_lastUpdate(DEFAULT_ZERO),
      m_intervalUpdate(TIMEOUT),
      m_url("inconnu"),
      m_isConnected(false) { ; }

bool Connection::isConnected()
{
  return (WiFi.status() == WL_CONNECTED);
}

String Connection::getURL()
{
  return this->m_url;
}

void Connection::tick()
{
  uint64_t actualTime = millis();
  if (actualTime - this->m_lastUpdate >= this->m_intervalUpdate)
  {
    this->m_lastUpdate = actualTime;
    if (!isConnected())
    {
      Serial.println("Connexion perdue! Tentative de reconnexion...");
      connectToNetwork();
    }
  }
}

bool Connection::connectToNetwork() {                                                 
  uint8_t nbTry = 0;
  Serial.print("Connexion au réseau WiFi: ");
  Serial.println(this->m_ssid);
  WiFi.begin(this->m_ssid, this->m_password);

  Serial.print("Connexion: [");
  uint16_t lastDisplayUpdate = 0;
  while (nbTry < NB_TRY_MAX && WiFi.status() != WL_CONNECTED)
  {
    uint16_t currentMillis = millis();
    if (currentMillis - lastDisplayUpdate >= INTERVAL_500)
    {
      lastDisplayUpdate = currentMillis;
      Serial.print("=");
      ++nbTry;
    }
  }
  Serial.print("]");
  Serial.println("");

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.print("Connecté au réseau WiFi: ");
    Serial.println(this->m_ssid);
    Serial.print("Adresse IP: ");
    Serial.println(WiFi.localIP());
    Serial.println("");
    this->m_isConnected = true;                                                              
  }
  else
  {
    Serial.print("Échec de connexion au réseau: ");
    Serial.println(this->m_ssid);
  }

  return this->m_isConnected;                                                         
}
