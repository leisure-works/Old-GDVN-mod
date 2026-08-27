#include "DateUtils.hpp"

#include <algorithm>
#include <charconv>
#include <chrono>
#include <cstddef>

namespace {
std::int64_t daysFromCivil(int year, unsigned month, unsigned day) {
    year -= month <= 2;
    const auto era = (year >= 0 ? year : year - 399) / 400;
    const auto yoe = static_cast<unsigned>(year - era * 400);
    const auto doy = (153 * (month + (month > 2 ? -3 : 9)) + 2) / 5 + day - 1;
    const auto doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    return era * 146097 + static_cast<int>(doe) - 719468;
}

bool parseFixedInt(std::string const& value, size_t offset, size_t length, int& output) {
    if (offset + length > value.size()) {
        return false;
    }

    auto begin = value.data() + offset;
    auto end = begin + length;
    auto result = std::from_chars(begin, end, output);
    return result.ec == std::errc() && result.ptr == end;
}
} // namespace

namespace gdvn::utils::date {

std::int64_t currentEpochSeconds() {
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch())
        .count();
}

std::int64_t parseIsoEpochSeconds(std::string const& value) {
    if (value.size() < 19) {
        return 0;
    }

    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    int second = 0;

    if (value[4] != '-' || value[7] != '-' || value[10] != 'T' || value[13] != ':' || value[16] != ':' ||
        !parseFixedInt(value, 0, 4, year) || !parseFixedInt(value, 5, 2, month) || !parseFixedInt(value, 8, 2, day) ||
        !parseFixedInt(value, 11, 2, hour) || !parseFixedInt(value, 14, 2, minute) ||
        !parseFixedInt(value, 17, 2, second) || month < 1 || month > 12 || day < 1 || day > 31 || hour < 0 ||
        hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 60) {
        return 0;
    }

    return daysFromCivil(year, static_cast<unsigned>(month), static_cast<unsigned>(day)) * 86400 + hour * 3600 +
           minute * 60 + second;
}

std::string formatCountdown(std::int64_t seconds) {
    seconds = std::max<std::int64_t>(0, seconds);
    const auto minutes = seconds / 60;
    const auto secs = seconds % 60;

    auto text = std::to_string(minutes) + ":";
    if (secs < 10) {
        text += "0";
    }
    text += std::to_string(secs);
    return text;
}

} // namespace gdvn::utils::date
