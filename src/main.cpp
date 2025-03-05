#include <Arduino.h>
#include "Program.h"

Program* program = nullptr;
void setup() {
    Serial.begin(SERIAL_SPEED);

    Serial.println("Initialisation...");
    program = new Program();
    Serial.println("Programme initialisé");
 }

void loop() { 
    program->loop();
}
