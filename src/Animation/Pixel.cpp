#include "Animation/Pixel.h"

Pixel::Pixel(uint8_t x, uint8_t y, Color *color)
{
    this->x = x;
    this->y = y;
    this->color = color;
}

Color *Pixel::getColor()
{
    return this->color;
}

uint8_t Pixel::getX()
{
    return this->x;
}

uint8_t Pixel::getY()
{
    return this->y;
}

void Pixel::setColor(Color *color)
{
    this->color = color;
}

void Pixel::setX(uint8_t x)
{
    this->x = x;
}

void Pixel::setY(uint8_t y)
{
    this->y = y;
}