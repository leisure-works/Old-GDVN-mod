#pragma once

#include <cstdint>
#include <string>

struct PvpOverlayChatMessageModel {
    std::int64_t id = 0;
    std::string senderUid;
    std::string type;
    std::string content;
    bool senderAnonymous = false;
};
