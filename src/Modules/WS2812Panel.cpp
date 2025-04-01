#include "Modules/WS2812Panel.h"
#include "const.h"
#include <Fonts/TomThumb.h>

WS2812Panel::WS2812Panel()
{
    ledsPanel = new CRGB[LED_COUNT_PANEL];

    FastLED.addLeds<WS2812, LED_PIN_PANEL>(this->ledsPanel, LED_COUNT_PANEL);
    FastLED.clear();

    this->matrix = new FastLED_NeoMatrix(this->ledsPanel, MATRIX_WIDTH_PANEL, MATRIX_HEIGHT_PANEL, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG);
    this->matrix->begin();
    this->matrix->setTextWrap(false);
    this->matrix->setBrightness(25);
}

void WS2812Panel::showTime(String timeString)
{
    static int position = this->matrix->width(); // Position initiale du texte (à droite)

    unsigned long currentMillis = millis(); // Temps actuel

    if (currentMillis - previousMillis >= INTERVAL_200)
    {
        previousMillis = currentMillis; // Mise à jour du dernier temps

        this->matrix->fillScreen(0); // Efface l'écran
        this->matrix->setFont(NULL); // Utilise la police par défaut
        this->matrix->setTextSize(1); // Taille du texte
        this->matrix->setCursor(position, 4);                         // Position dynamique du texte
        this->matrix->setTextColor(this->matrix->Color(0, 255, 255)); // Texte mauve (GRB)
        this->matrix->print(timeString);
        this->matrix->show(); // Met à jour l'affichage

        --position; // Déplace le texte vers la gauche

        // Quand le texte sort complètement, on le remet à droite
        if (position < -((int)timeString.length() * 6))
        {
            position = this->matrix->width();
        }
    }
}

void WS2812Panel::showCountdown(int countdownValue)
{
    this->matrix->fillScreen(0);                                // Efface l'écran
    this->matrix->setTextColor(this->matrix->Color(0, 255, 0)); // Texte mauve (GRB)
    this->matrix->setFont(&TomThumb);                           // Utilise la police TomThumb
    this->matrix->setTextSize(2);                               // Taille du texte

    if (countdownValue == 10)
    {
        this->matrix->setCursor(2, 13);      // Position du texte
        this->matrix->print(countdownValue); // Affiche le texte
    }
    else if (countdownValue == 0)
    {
        this->matrix->setCursor(1, 13);
        this->matrix->print("GO");
    }
    else
    {
        this->matrix->setCursor(5, 13);
        this->matrix->print(countdownValue);
    }

    this->matrix->show(); // Met à jour l'affichage
}

void WS2812Panel::drawRocket()
{
    this->matrix->fillScreen(0); // Efface l'écran

    // Nuage de gauche
    this->matrix->drawPixel(2, 5, this->matrix->Color(180, 180, 180));
    this->matrix->drawPixel(3, 5, this->matrix->Color(200, 200, 200));
    this->matrix->drawPixel(2, 6, this->matrix->Color(220, 220, 220));
    this->matrix->drawPixel(3, 6, this->matrix->Color(200, 200, 200));
    this->matrix->drawPixel(4, 6, this->matrix->Color(180, 180, 180));

    // Nuage de droite
    this->matrix->drawPixel(12, 5, this->matrix->Color(180, 180, 180));
    this->matrix->drawPixel(13, 5, this->matrix->Color(200, 200, 200));
    this->matrix->drawPixel(12, 6, this->matrix->Color(220, 220, 220));
    this->matrix->drawPixel(13, 6, this->matrix->Color(200, 200, 200));
    this->matrix->drawPixel(11, 6, this->matrix->Color(180, 180, 180));

    // Tete de la fusée

    this->matrix->drawPixel(7, 2, this->matrix->Color(0, 0, 255));
    this->matrix->drawPixel(8, 2, this->matrix->Color(0, 0, 255));

    this->matrix->drawPixel(6, 3, this->matrix->Color(0, 0, 255));
    this->matrix->drawPixel(7, 3, this->matrix->Color(0, 0, 255));
    this->matrix->drawPixel(8, 3, this->matrix->Color(0, 0, 255));
    this->matrix->drawPixel(9, 3, this->matrix->Color(0, 0, 255));

    this->matrix->drawPixel(6, 4, this->matrix->Color(0, 0, 255));
    this->matrix->drawPixel(7, 4, this->matrix->Color(0, 0, 255));
    this->matrix->drawPixel(8, 4, this->matrix->Color(0, 0, 255));
    this->matrix->drawPixel(9, 4, this->matrix->Color(0, 0, 255));

    // Corps de la fusée (blanc/gris)
    this->matrix->drawPixel(6, 5, this->matrix->Color(255, 255, 255));
    this->matrix->drawPixel(7, 5, this->matrix->Color(255, 255, 255));
    this->matrix->drawPixel(8, 5, this->matrix->Color(255, 255, 255));
    this->matrix->drawPixel(9, 5, this->matrix->Color(255, 255, 255));

    this->matrix->drawPixel(6, 6, this->matrix->Color(255, 255, 255));
    this->matrix->drawPixel(7, 6, this->matrix->Color(255, 255, 255));
    this->matrix->drawPixel(8, 6, this->matrix->Color(255, 255, 255));
    this->matrix->drawPixel(9, 6, this->matrix->Color(255, 255, 255));

    this->matrix->drawPixel(6, 7, this->matrix->Color(255, 255, 255));
    this->matrix->drawPixel(7, 7, this->matrix->Color(255, 255, 255));
    this->matrix->drawPixel(8, 7, this->matrix->Color(255, 255, 255));
    this->matrix->drawPixel(9, 7, this->matrix->Color(255, 255, 255));

    this->matrix->drawPixel(6, 8, this->matrix->Color(255, 255, 255));
    this->matrix->drawPixel(7, 8, this->matrix->Color(255, 255, 255));
    this->matrix->drawPixel(8, 8, this->matrix->Color(255, 255, 255));
    this->matrix->drawPixel(9, 8, this->matrix->Color(255, 255, 255));

    this->matrix->drawPixel(6, 9, this->matrix->Color(255, 255, 255));
    this->matrix->drawPixel(7, 9, this->matrix->Color(255, 255, 255));
    this->matrix->drawPixel(8, 9, this->matrix->Color(255, 255, 255));
    this->matrix->drawPixel(9, 9, this->matrix->Color(255, 255, 255));

    // Ailerons (rouge)
    this->matrix->drawPixel(6, 9, this->matrix->Color(0, 255, 0));
    this->matrix->drawPixel(5, 9, this->matrix->Color(0, 255, 0));
    this->matrix->drawPixel(9, 9, this->matrix->Color(0, 255, 0));
    this->matrix->drawPixel(10, 9, this->matrix->Color(0, 255, 0));

    this->matrix->drawPixel(5, 10, this->matrix->Color(0, 255, 0));
    this->matrix->drawPixel(4, 10, this->matrix->Color(0, 255, 0));
    this->matrix->drawPixel(10, 10, this->matrix->Color(0, 255, 0));
    this->matrix->drawPixel(11, 10, this->matrix->Color(0, 255, 0));

    // Flamme animée
    int flameType = millis() / 200 % 3; // Alterne entre 3 formes
    int flameY = 11;                    // Position de la flamme

    if (flameType == 0)
    {
        this->matrix->drawPixel(7, flameY, randomFireColor());
        this->matrix->drawPixel(8, flameY, randomFireColor());
    }
    else if (flameType == 1)
    {
        this->matrix->drawPixel(7, flameY + 1, randomFireColor());
        this->matrix->drawPixel(8, flameY, randomFireColor());
    }
    else
    {
        this->matrix->drawPixel(8, flameY + 1, randomFireColor());
        this->matrix->drawPixel(7, flameY, randomFireColor());
    }

    this->matrix->show();
}

uint16_t WS2812Panel::randomFireColor()
{
    int r = random(200, 256);
    int g = random(50, 150);
    return this->matrix->Color(g, r, 0);
}