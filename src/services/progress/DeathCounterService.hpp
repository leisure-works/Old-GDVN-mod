#pragma once

#include "../../models/death/DeathDataModel.hpp"
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class DeathCounterService {
  private:
    DeathDataModel deathData;
    bool completed = false;

  public:
    DeathCounterService();
    DeathCounterService(int id, bool completed);
    void add(int percent);
    void submit();
    void setCompleted(bool completed) {
        this->completed = completed;
    }
};
