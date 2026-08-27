#pragma once

#include <cstddef>
#include <string>

namespace gdvn::utils::string {

std::string replaceAll(std::string text, std::string const& from, std::string const& to);
std::string toAsciiCompatible(std::string text);
std::string trimCopy(std::string value);
std::string trimTrailingSlash(std::string value);
std::string toTTFSafeText(std::string text);
std::string truncate(std::string text, size_t maxLength);

} // namespace gdvn::utils::string
