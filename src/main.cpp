#include <Arduino.h>
#include "Program.h"
#include "Logs/DataLogger.h"

Program *program = nullptr;
void setup()
{
  Serial.begin(SERIAL_SPEED);

  Logger.log("Initialisation...");
  program = new Program();
}

void loop()
{
  program->loop();
}
