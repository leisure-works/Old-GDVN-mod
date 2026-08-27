#pragma once

#include "PvpMatchPlayerProgressDto.hpp"
#include <string>
#include <vector>

struct PvpMatchSnapshotDto {
    int matchID = 0;
    std::string currentUid;
    std::string mode = "classic";
    std::string scoringMode = "progress";
    int targetScore = 0;
    int startingHp = 0;
    int finalizeAliveCount = 0;
    std::string context = "versus";
    std::string roomName;
    std::string endsAt;
    std::string status;
    std::vector<PvpMatchPlayerProgressDto> participants;
    std::vector<PvpMatchPlayerProgressDto> results;
};
