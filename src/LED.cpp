#include "LED.h"
#include <Arduino.h>

// Constructeur de lumière LED.
LED::LED(const uint8_t p_pin) : m_pin(p_pin){
  pinMode(this->m_pin, OUTPUT);
}

// Fonction qui allume la lumière LED.
void LED::light() const {  
  digitalWrite(this->m_pin, HIGH);  
}

// Fonction qui éteint la lumière.

void LED::shut() const { 
  digitalWrite(this->m_pin, LOW); 
}
