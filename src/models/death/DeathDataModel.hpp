#pragma once

#include <array>
#include <cstddef>
#include <string>

class DeathDataModel {
  public:
    int levelID = 0;
    bool completed = false;
    std::array<size_t, 100> cnt = {};

    DeathDataModel();
    DeathDataModel(int id, bool a, std::array<size_t, 100> b);
    std::string serialize();
    void addDeathCount(int percent);
    bool isCompleted();
    void setCompleted();
};
