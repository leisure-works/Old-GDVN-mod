#pragma once

#include "GameEventInterface.hpp"
#include <Geode/binding/PlayLayer.hpp>

#include <string_view>

class AntiCheatInterface : public GameEventInterface {
  public:
    virtual ~AntiCheatInterface() = default;

    virtual void reset(PlayLayer* playLayer) = 0;
    virtual bool isCheated() const = 0;
    virtual std::string_view getCheatReason() const = 0;
};
