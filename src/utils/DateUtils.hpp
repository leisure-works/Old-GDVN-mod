#pragma once

#include <cstdint>
#include <string>

namespace gdvn::utils::date {

std::int64_t currentEpochSeconds();
std::int64_t parseIsoEpochSeconds(std::string const& value);
std::string formatCountdown(std::int64_t seconds);

} // namespace gdvn::utils::date
