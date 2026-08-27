#pragma once

#include <Geode/binding/PlayerObject.hpp>

class GameEventInterface {
  public:
    virtual ~GameEventInterface() = default;

    virtual void onUpdate(float dt) {
    }

    virtual void onPlayerDestroyed(PlayerObject* player) {
    }
};
