#include "Modules/ServoMotor.h"
#include "config.h"

// Constructeur du ServoMoteur qui déclenche le parachute.
ServoMotor::ServoMotor() :
    m_interval(1500)
{
    Sensor::setName("SERVO_MOTOR");

    this->m_servo.attach(SERVO_PIN);
    rotate(START_POS);
}

// Fonction qui rotate le servo de x degré selon le paramètre.
// Servo moteur protégé par le temps, 1500ms pour exécuter la rotation
void ServoMotor::rotate(uint8_t p_position)
{
    this->m_servo.attach(SERVO_PIN); //  Re-attache AVANT d'écrire
    if (this->m_position != p_position)
    {
        this->m_servo.write(p_position);
        this->m_position = p_position;
    }

    uint64_t startTime = millis();
    while (millis() - startTime < this->m_interval) {
        yield();
    }

    this->m_servo.detach(); // Libère la pin  
}
