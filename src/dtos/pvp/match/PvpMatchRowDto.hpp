#pragma once

#include <string>

struct PvpMatchRowDto {
    int levelID = 0;
    std::string mode;
    std::string scoringMode = "progress";
    int targetScore = 0;
    int startingHp = 0;
    int finalizeAliveCount = 0;
    std::string endsAt;
    std::string status;
};
