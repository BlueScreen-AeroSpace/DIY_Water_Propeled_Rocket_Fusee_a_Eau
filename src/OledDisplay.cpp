#include "OledDisplay.h"

OledDisplay::OledDisplay(SensorManager* p_sensorManager) 
    : m_OledDisplay(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1),
      m_sensorManager(p_sensorManager)
{
    Wire.begin();
    if (!m_OledDisplay.begin(SSD1306_SWITCHCAPVCC,OLED_ADDR))
    {
        Serial.println("Incapable de démarrer l'écran Oled. Vérifiez l'adresse et le câblage.");
#ifndef DEBUG
        while (true)
            ;
#endif
    }
    this->m_OledDisplay.setTextSize(1);
    this->m_OledDisplay.setTextColor(WHITE);
    this->m_OledDisplay.setCursor(0, 0);
    this->m_OledDisplay.clearDisplay();
    this->m_OledDisplay.display();
    this->displayActivatedSensors();
}

void OledDisplay::displayActivatedSensors()
{
    std::vector<Sensor*> sensors = this->m_sensorManager->getActivatedSensors();
    m_OledDisplay.println("Capteurs Actifs : ");
#ifndef DEBUG
    Serial.println("Capteurs Actifs : ");
#endif

    for (uint8_t i = 0; i < sensors.size(); i++)
    {
        m_OledDisplay.println(sensors[i]->getName());
#ifndef DEBUG
        Serial.println(sensors[i]->getName());
#endif
    }
    this->m_OledDisplay.display();
}