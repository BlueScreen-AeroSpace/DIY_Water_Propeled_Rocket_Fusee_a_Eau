#pragma once
#include <Arduino.h>
#include "Color.h"

class Pixel
{
private:
    uint8_t x;
    uint8_t y;
    Color *color;

public:
    Pixel(uint8_t x, uint8_t y, Color *color);
    void setColor(Color *color);
    void setX(uint8_t x);
    void setY(uint8_t y);
    Color *getColor();
    uint8_t getX();
    uint8_t getY();
};