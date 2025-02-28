#include "Rocket.h"

Rocket::Rocket() : m_isInFlight(false) { ; }

void Rocket::setIsInFlight(bool p_isInFlight) {
    this->m_isInFlight = p_isInFlight;
}

bool Rocket::inFlightReady() {
    return this->m_isInFlight;
}