#include "Managers/DELPanelManager.h"
#include "const.h"

DELPanelManager::DELPanelManager(WS2812Panel *_panel, DS1307Clock *_clock)
{
    panel = _panel;
    clock = _clock;
    previousMillis = millis();
}

void DELPanelManager::setCountdownActive() // Active le compte à rebours
{
    countdownActive = true;
}

void DELPanelManager::showTime() // Affiche l'heure sur le panneau
{
   /*  String time = clock->getActualTimeNoSec();
    panel->showTime(time); */ // Décommenter pour afficher l'heure actuelle et commenter la ligne suivante

    panel->showTime("13:37");
}

void DELPanelManager::theFinalCountdown() // Compte à rebours
{
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= INTERVAL_1)
    {
        previousMillis = currentMillis;

        panel->showCountdown(countdownValue); // Affiche le nombre sur le panneau

        if (countdownValue == 0)
        {
            countdownActive = false; // Arrête le compte à rebours
            countdownValue = 10;
        }
        else
        {
            countdownValue--; // Décrémente le compte à rebours
        }
    }
}

void DELPanelManager::showAnimationOne()
{
    panel->drawRocket(); // Défini dans WS2812Panel
                               
}

void DELPanelManager::tick()
{
    unsigned long currentTime = millis();

    if (currentTime - lastUpdateTime >= 15000)
    {
        lastUpdateTime = currentTime;

        // Appeler la fonction en fonction de l'index

        currentFunctionIndex = (currentFunctionIndex + 1) % 3;
    }

    switch (currentFunctionIndex)
    {
    case 0:
        this->theFinalCountdown();
        break;
    case 1:
        this->showTime();
        break;
    case 2:
        this->showAnimationOne();
        break;
    }
}