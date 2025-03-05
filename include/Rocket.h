#pragma once

class Rocket {
private:
    bool m_isInFlight;
public:
    Rocket();
    void setIsInFlight(bool p_isInFlight);
    bool inFlightReady();
};