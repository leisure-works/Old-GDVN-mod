#pragma once

#include "../../interfaces/AntiCheatInterface.hpp"
#include <Geode/Geode.hpp>
#include <Geode/binding/PlayLayer.hpp>

#include <string_view>

class StartPositionAntiCheatService : public AntiCheatInterface {
  private:
    PlayLayer* playLayer = nullptr;

  public:
    void reset(PlayLayer* playLayer) override;
    void onUpdate(float dt) override;
    bool isCheated() const override;
    std::string_view getCheatReason() const override;
};
