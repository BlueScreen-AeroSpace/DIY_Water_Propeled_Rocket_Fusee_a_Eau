#include "Modules/WS2812Panel.h"
#include "const.h"
#include <Fonts/TomThumb.h>
#include <vector>
#include <map>
#include "Animation/Pixel.h"

WS2812Panel::WS2812Panel()
{
    ledsPanel = new CRGB[LED_COUNT_PANEL];

    FastLED.addLeds<WS2812, LED_PIN_PANEL>(this->ledsPanel, LED_COUNT_PANEL);
    FastLED.clear();

    this->matrix = new FastLED_NeoMatrix(this->ledsPanel, MATRIX_WIDTH_PANEL, MATRIX_HEIGHT_PANEL, NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG);
    this->matrix->begin();
    this->matrix->setTextWrap(false);
    this->matrix->setBrightness(25);
}

void WS2812Panel::show()
{
    this->matrix->show(); // Met à jour l'affichage
}

void WS2812Panel::drawFrame(Frame frame)
{
    for (Pixel pixel : frame.getPixels())
    {
        this->matrix->drawPixel(pixel.getX(), pixel.getY(), this->matrix->Color(pixel.getColor()->getG(), pixel.getColor()->getR(), pixel.getColor()->getB())); // Utilise la couleur RGB
    }
}

void WS2812Panel::eraseScreen()
{
    this->matrix->fillScreen(0); // Efface l'écran
}

void WS2812Panel::showTime(String timeString)
{
    static int position = this->matrix->width(); // Position initiale du texte (à droite)

    unsigned long currentMillis = millis(); // Temps actuel

    if (currentMillis - previousMillis >= INTERVAL_200)
    {
        previousMillis = currentMillis; // Mise à jour du dernier temps

        eraseScreen();                                                // Efface l'écran
        this->matrix->setFont(NULL);                                  // Utilise la police par défaut
        this->matrix->setTextSize(1);                                 // Taille du texte
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
    eraseScreen();                                // Efface l'écran
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