#include "StartPositionAntiCheatService.hpp"

void StartPositionAntiCheatService::reset(PlayLayer* playLayer) {
    this->playLayer = playLayer;
}

void StartPositionAntiCheatService::onUpdate(float) {
}

bool StartPositionAntiCheatService::isCheated() const {
    return playLayer && playLayer->m_startPosObject;
}

std::string_view StartPositionAntiCheatService::getCheatReason() const {
    return "start position";
}
