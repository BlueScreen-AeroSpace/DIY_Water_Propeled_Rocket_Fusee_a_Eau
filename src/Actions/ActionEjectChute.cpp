#include "Actions/ActionEjectChute.h"
#include "Logs/DataLogger.h"

// Constructeur de l'action d'éjection du parachute.
ActionEjectChute::ActionEjectChute(ServoMotor *p_servoMotor) : m_servoMotor(p_servoMotor) { ; }

// Fonction qui exécute l'action d'éjection
void ActionEjectChute::execute()
{
    this->m_servoMotor->rotate(ROTATE_90);
    Logger.log("Parachute éjecté");
}