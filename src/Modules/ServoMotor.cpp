#include "Modules/ServoMotor.h"

ServoMotor::ServoMotor() {
    this->m_servo.attach(SERVO_PIN);
    RotateToStartPosition();
}

void ServoMotor::RotateToStartPosition() {
    if (this->m_position != START_POS) {
        this->m_servo.write(START_POS);
        this->m_position = START_POS;
        //Serial.println("Position: " + String(this->m_position) + "°");
    }
}
void ServoMotor::Rotate90() {
    if (this->m_position != ROTATE_90) {
        this->m_servo.write(ROTATE_90);
        this->m_position = ROTATE_90;
        //Serial.println("Position: " + String(this->m_position) + "°");
    }
}
