#pragma once
#include "DELPanelManager.h"

class LaunchManager {
private:
    DELPanelManager* m_delPanelManager;
public: 
    LaunchManager(DELPanelManager* p_delPanelManager);
    void activateCountdown();
    bool getCountDownActive();
};