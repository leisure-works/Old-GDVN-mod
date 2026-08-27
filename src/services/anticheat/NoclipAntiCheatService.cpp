#include "NoclipAntiCheatService.hpp"

void NoclipAntiCheatService::reset(PlayLayer* playLayer) {
    this->playLayer = playLayer;
    cheated = false;
}

void NoclipAntiCheatService::onUpdate(float) {
}

void NoclipAntiCheatService::onPlayerDestroyed(PlayerObject* player) {
    const float progress = playLayer->getCurrentPercent();

    if (progress < 5.0f) {
        return;
    }

    if (!player->m_isDead) {
        cheated = true;

        geode::log::warn(
            "[NoclipAntiCheatService] Noclip detected at {:.2f}%",
            progress
        );
    }
}

bool NoclipAntiCheatService::isCheated() const {
    return cheated;
}

std::string_view NoclipAntiCheatService::getCheatReason() const {
    return "noclip";
}
