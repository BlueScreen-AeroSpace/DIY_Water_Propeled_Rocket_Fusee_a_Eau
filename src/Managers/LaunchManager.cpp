#include "Managers/LaunchManager.h"
#include "Logs/DataLogger.h"

LaunchManager::LaunchManager(DELPanelManager* p_delPanelManager) 
    : m_delPanelManager(p_delPanelManager) {
        Logger.log("Module LaunchManager initialisé");
    }

void LaunchManager::activateCountdown() {
    if (this->m_delPanelManager == nullptr) {
        return;
    }
    this->m_delPanelManager->setCountdownActive();
}

bool LaunchManager::getCountDownActive() {
    return this->m_delPanelManager->getCountDownActive();
}