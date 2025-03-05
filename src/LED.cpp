#include "LED.h"
#include <Arduino.h>

LED::LED(const uint8_t p_pin) : m_pin(p_pin){
  pinMode(this->m_pin, OUTPUT);
}
void LED::light() const {  
  digitalWrite(this->m_pin, HIGH);  
}

void LED::shut() const { 
  digitalWrite(this->m_pin, LOW); 
}
