#include "Modules/ServoMotor.h"
#include "config.h"

// Constructeur du ServoMoteur qui déclenche le parachute.
ServoMotor::ServoMotor()
{
    Sensor::setName("SERVO_MOTOR");

#ifndef DEBUG
    this->m_servo.attach(SERVO_PIN);
    RotateToStartPosition();
#endif
}

//Fonction qui rotate a sa positon initiale 0 degré.
void ServoMotor::RotateToStartPosition()
{
    if (this->m_position != START_POS)
    {
        this->m_servo.write(START_POS);
        this->m_position = START_POS;
        // Serial.println("Position: " + String(this->m_position) + "°");
    }
}

// Fonction qui rotate de 90 degré pour l'ouverture du parachute.
void ServoMotor::Rotate90()
{
    if (this->m_position != ROTATE_90)
    {
        this->m_servo.write(ROTATE_90);
        this->m_position = ROTATE_90;
        // Serial.println("Position: " + String(this->m_position) + "°");
    }
}
