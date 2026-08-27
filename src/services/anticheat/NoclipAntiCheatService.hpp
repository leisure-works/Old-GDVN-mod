#pragma once

#include "../../interfaces/AntiCheatInterface.hpp"
#include <Geode/Geode.hpp>
#include <Geode/binding/PlayLayer.hpp>
#include <Geode/binding/PlayerObject.hpp>

#include <string_view>

class NoclipAntiCheatService : public AntiCheatInterface {
  private:
    PlayLayer* playLayer = nullptr;
    bool cheated = false;
    float prevProgress = 0.0f;

  public:
    void reset(PlayLayer* playLayer) override;
    void onUpdate(float dt) override;
    void onPlayerDestroyed(PlayerObject* player) override;
    bool isCheated() const override;
    std::string_view getCheatReason() const override;
};
