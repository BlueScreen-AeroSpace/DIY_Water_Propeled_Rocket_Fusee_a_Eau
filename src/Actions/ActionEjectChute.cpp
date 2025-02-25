#include "Actions/ActionEjectChute.h"

ActionEjectChute::ActionEjectChute(ServoMotor* p_servoMotor) : m_servoMotor(p_servoMotor) { ; }

void ActionEjectChute::execute() {
    this->m_servoMotor->Rotate90();
}