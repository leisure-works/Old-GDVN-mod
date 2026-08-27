#include "StringUtils.hpp"

#include <algorithm>
#include <cctype>
#include <vector>

namespace gdvn::utils::string {

std::string replaceAll(std::string text, std::string const& from, std::string const& to) {
    size_t pos = 0;

    while ((pos = text.find(from, pos)) != std::string::npos) {
        text.replace(pos, from.size(), to);
        pos += to.size();
    }

    return text;
}

std::string toAsciiCompatible(std::string text) {
    std::vector<std::pair<std::string, std::string>> replacements = {
        {"\xC3\xA0", "a"},     {"\xC3\xA1", "a"},     {"\xE1\xBA\xA3", "a"}, {"\xC3\xA3", "a"},
        {"\xE1\xBA\xA1", "a"}, {"\xC4\x83", "a"},     {"\xE1\xBA\xB1", "a"}, {"\xE1\xBA\xAF", "a"},
        {"\xE1\xBA\xB3", "a"}, {"\xE1\xBA\xB5", "a"}, {"\xE1\xBA\xB7", "a"}, {"\xC3\xA2", "a"},
        {"\xE1\xBA\xA7", "a"}, {"\xE1\xBA\xA5", "a"}, {"\xE1\xBA\xA9", "a"}, {"\xE1\xBA\xAB", "a"},
        {"\xE1\xBA\xAD", "a"}, {"\xC3\x80", "A"},     {"\xC3\x81", "A"},     {"\xE1\xBA\xA2", "A"},
        {"\xC3\x83", "A"},     {"\xE1\xBA\xA0", "A"}, {"\xC4\x82", "A"},     {"\xE1\xBA\xB0", "A"},
        {"\xE1\xBA\xAE", "A"}, {"\xE1\xBA\xB2", "A"}, {"\xE1\xBA\xB4", "A"}, {"\xE1\xBA\xB6", "A"},
        {"\xC3\x82", "A"},     {"\xE1\xBA\xA6", "A"}, {"\xE1\xBA\xA4", "A"}, {"\xE1\xBA\xA8", "A"},
        {"\xE1\xBA\xAA", "A"}, {"\xE1\xBA\xAC", "A"}, {"\xC4\x91", "d"},     {"\xC4\x90", "D"},
        {"\xC3\xA8", "e"},     {"\xC3\xA9", "e"},     {"\xE1\xBA\xBB", "e"}, {"\xE1\xBA\xBD", "e"},
        {"\xE1\xBA\xB9", "e"}, {"\xC3\xAA", "e"},     {"\xE1\xBB\x81", "e"}, {"\xE1\xBA\xBF", "e"},
        {"\xE1\xBB\x83", "e"}, {"\xE1\xBB\x85", "e"}, {"\xE1\xBB\x87", "e"}, {"\xC3\x88", "E"},
        {"\xC3\x89", "E"},     {"\xE1\xBA\xBA", "E"}, {"\xE1\xBA\xBC", "E"}, {"\xE1\xBA\xB8", "E"},
        {"\xC3\x8A", "E"},     {"\xE1\xBB\x80", "E"}, {"\xE1\xBA\xBE", "E"}, {"\xE1\xBB\x82", "E"},
        {"\xE1\xBB\x84", "E"}, {"\xE1\xBB\x86", "E"}, {"\xC3\xAC", "i"},     {"\xC3\xAD", "i"},
        {"\xE1\xBB\x89", "i"}, {"\xC4\xA9", "i"},     {"\xE1\xBB\x8B", "i"}, {"\xC3\x8C", "I"},
        {"\xC3\x8D", "I"},     {"\xE1\xBB\x88", "I"}, {"\xC4\xA8", "I"},     {"\xE1\xBB\x8A", "I"},
        {"\xC3\xB2", "o"},     {"\xC3\xB3", "o"},     {"\xE1\xBB\x8F", "o"}, {"\xC3\xB5", "o"},
        {"\xE1\xBB\x8D", "o"}, {"\xC3\xB4", "o"},     {"\xE1\xBB\x93", "o"}, {"\xE1\xBB\x91", "o"},
        {"\xE1\xBB\x95", "o"}, {"\xE1\xBB\x97", "o"}, {"\xE1\xBB\x99", "o"}, {"\xC6\xA1", "o"},
        {"\xE1\xBB\x9D", "o"}, {"\xE1\xBB\x9B", "o"}, {"\xE1\xBB\x9F", "o"}, {"\xE1\xBB\xA1", "o"},
        {"\xE1\xBB\xA3", "o"}, {"\xC3\x92", "O"},     {"\xC3\x93", "O"},     {"\xE1\xBB\x8E", "O"},
        {"\xC3\x95", "O"},     {"\xE1\xBB\x8C", "O"}, {"\xC3\x94", "O"},     {"\xE1\xBB\x92", "O"},
        {"\xE1\xBB\x90", "O"}, {"\xE1\xBB\x94", "O"}, {"\xE1\xBB\x96", "O"}, {"\xE1\xBB\x98", "O"},
        {"\xC6\xA0", "O"},     {"\xE1\xBB\x9C", "O"}, {"\xE1\xBB\x9A", "O"}, {"\xE1\xBB\x9E", "O"},
        {"\xE1\xBB\xA0", "O"}, {"\xE1\xBB\xA2", "O"}, {"\xC3\xB9", "u"},     {"\xC3\xBA", "u"},
        {"\xE1\xBB\xA7", "u"}, {"\xC5\xA9", "u"},     {"\xE1\xBB\xA5", "u"}, {"\xC6\xB0", "u"},
        {"\xE1\xBB\xAB", "u"}, {"\xE1\xBB\xA9", "u"}, {"\xE1\xBB\xAD", "u"}, {"\xE1\xBB\xAF", "u"},
        {"\xE1\xBB\xB1", "u"}, {"\xC3\x99", "U"},     {"\xC3\x9A", "U"},     {"\xE1\xBB\xA6", "U"},
        {"\xC5\xA8", "U"},     {"\xE1\xBB\xA4", "U"}, {"\xC6\xAF", "U"},     {"\xE1\xBB\xAA", "U"},
        {"\xE1\xBB\xA8", "U"}, {"\xE1\xBB\xAC", "U"}, {"\xE1\xBB\xAE", "U"}, {"\xE1\xBB\xB0", "U"},
        {"\xE1\xBB\xB3", "y"}, {"\xC3\xBD", "y"},     {"\xE1\xBB\xB7", "y"}, {"\xE1\xBB\xB9", "y"},
        {"\xE1\xBB\xB5", "y"}, {"\xE1\xBB\xB2", "Y"}, {"\xC3\x9D", "Y"},     {"\xE1\xBB\xB6", "Y"},
        {"\xE1\xBB\xB8", "Y"}, {"\xE1\xBB\xB4", "Y"},
    };

    for (auto const& [from, to] : replacements) {
        text = replaceAll(text, from, to);
    }

    std::string ascii;

    for (unsigned char c : text) {
        if (c < 128) {
            ascii += static_cast<char>(c);
        }
    }

    return ascii;
}

std::string trimCopy(std::string value) {
    auto begin = std::find_if_not(value.begin(), value.end(), [](unsigned char c) { return std::isspace(c); });
    auto end = std::find_if_not(value.rbegin(), value.rend(), [](unsigned char c) { return std::isspace(c); }).base();

    if (begin >= end) {
        return "";
    }

    return std::string(begin, end);
}

std::string trimTrailingSlash(std::string value) {
    while (!value.empty() && value.back() == '/') {
        value.pop_back();
    }
    return value;
}

std::string toTTFSafeText(std::string text) {
    std::string safe;
    safe.reserve(text.size());

    for (unsigned char c : text) {
        if (c == '\n' || c == '\r' || c == '\t') {
            safe.push_back(' ');
        } else if (c >= 32 || c >= 128) {
            safe.push_back(static_cast<char>(c));
        }
    }

    return safe;
}

std::string truncate(std::string text, size_t maxLength) {
    if (text.size() <= maxLength) {
        return text;
    }

    if (maxLength <= 3) {
        return text.substr(0, maxLength);
    }

    return text.substr(0, maxLength - 3) + "...";
}

} // namespace gdvn::utils::string
