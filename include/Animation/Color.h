#pragma once
#include <Arduino.h>

class Color
{
private:
    uint8_t r;
    uint8_t g;
    uint8_t b;

public:
    Color(uint8_t r, uint8_t g, uint8_t b);
    void setR(uint8_t r);
    void setG(uint8_t g);
    void setB(uint8_t b);
    uint8_t getR();
    uint8_t getG();
    uint8_t getB();
};