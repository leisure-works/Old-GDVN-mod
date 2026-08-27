#include "DeathDataModel.hpp"

DeathDataModel::DeathDataModel() {
}

DeathDataModel::DeathDataModel(int id, bool a, std::array<size_t, 100> b) {
    levelID = id;
    completed = a;
    cnt = b;
}

std::string DeathDataModel::serialize() {
    std::string res;

    for (size_t i : cnt) {
        res += std::to_string(i) + '|';
    }

    res.pop_back();

    return res;
}

void DeathDataModel::addDeathCount(int percent) {
    if (completed) {
        return;
    }

    if (!(0 <= percent && percent < 100)) {
        return;
    }

    cnt[percent]++;
}

bool DeathDataModel::isCompleted() {
    return completed;
}

void DeathDataModel::setCompleted() {
    completed = true;
}
