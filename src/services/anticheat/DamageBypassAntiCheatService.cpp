#include "DamageBypassAntiCheatService.hpp"

void DamageBypassAntiCheatService::reset(PlayLayer* playLayer) {
    this->playLayer = playLayer;
}

void DamageBypassAntiCheatService::onUpdate(float) {
}

bool DamageBypassAntiCheatService::isCheated() const {
    return playLayer && (playLayer->m_isIgnoreDamageEnabled || playLayer->m_ignoreDamage);
}

std::string_view DamageBypassAntiCheatService::getCheatReason() const {
    return "damage bypass";
}
