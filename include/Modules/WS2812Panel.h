#pragma once
#include <FastLED.h>
#include <FastLED_NeoMatrix.h>

class WS2812Panel
{
private:
    CRGB *ledsPanel;
    FastLED_NeoMatrix *matrix;

    unsigned long previousMillis = 0;

public:
    WS2812Panel();
    void showTime(String timeString);
    void showCountdown(int countdownValue);
    void drawRocket();
    uint16_t randomFireColor();
    void tick();
};