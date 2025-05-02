#include "Modules/ServoMotor.h"
#include "config.h"

// Constructeur du ServoMoteur qui déclenche le parachute.
ServoMotor::ServoMotor() :
    m_interval(1500)
{
    Sensor::setName("SERVO_MOTOR");

    this->m_servo.attach(SERVO_PIN);
    RotateToStartPosition();
}

//Fonction qui rotate a sa positon initiale 0 degré.
// Servo moteur protégé par le temps, 1500ms pour exécuter la rotation
void ServoMotor::RotateToStartPosition()
{
    this->m_servo.attach(SERVO_PIN); //  Re-attache AVANT d'écrire
    if (this->m_position != START_POS)
    {
        this->m_servo.write(START_POS);
        this->m_position = START_POS;
    }

    uint64_t startTime = millis();
    while (millis() - startTime < this->m_interval) {
        yield();
    }

    this->m_servo.detach(); // Libère la pin, stop l
}
// Fonction qui rotate de 90 degré pour l'ouverture du parachute.
// Servo moteur protégé par le temps, 1500ms pour exécuter la rotation
void ServoMotor::Rotate90()
{
    this->m_servo.attach(SERVO_PIN); //  Re-attache AVANT d'écrire
    if (this->m_position != ROTATE_90)
    {
        this->m_servo.write(ROTATE_90);
        this->m_position = ROTATE_90;
    }

    uint64_t startTime = millis();
    while (millis() - startTime < this->m_interval) {
        yield();
    }

    this->m_servo.detach(); // Libère la pin  
}
