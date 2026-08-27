#pragma once

#include "PvpPowerupStateDto.hpp"
#include <string>

struct PvpPowerupCastResponseDto {
    bool valid = false;
    std::string skill;
    std::string targetUid;
    bool blocked = false;
    PvpPowerupStateDto state;
};
