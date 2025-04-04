#include "Rocket.h"

// Constructeur de la fusée.
Rocket::Rocket() : m_isInFlight(false) { ; }

// Fonction qui vient changé l'état de vol de la fusée.
void Rocket::setIsInFlight(bool p_isInFlight) {
    this->m_isInFlight = p_isInFlight;
}

// Fonction qui vérifie si la fusée est prête à s'envoler.
bool Rocket::inFlightReady() {
    return this->m_isInFlight;
}