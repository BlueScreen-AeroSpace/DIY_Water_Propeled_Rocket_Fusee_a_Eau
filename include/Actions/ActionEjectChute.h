#pragma once
#include "Action.h"
#include "Modules/ServoMotor.h"

class ActionEjectChute : public Action {
private:
    ServoMotor* m_servoMotor;
public:
    ActionEjectChute(ServoMotor* p_servoMotor);
    void execute() override;   
};