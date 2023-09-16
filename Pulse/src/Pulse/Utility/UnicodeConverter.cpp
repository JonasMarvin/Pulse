#include "pch.h"

#include "UnicodeConverter.h"

std::string Pulse::Utility::UnicodeConverter::ToUTF8(unsigned int codepoint)
{
    std::string utf8String;
    if (codepoint <= 0x7F) {
        utf8String += static_cast<char>(codepoint);
    }
    else if (codepoint <= 0x7FF) {
        utf8String += static_cast<char>(0xC0 | ((codepoint >> 6) & 0x1F));
        utf8String += static_cast<char>(0x80 | (codepoint & 0x3F));
    }
    else if (codepoint <= 0xFFFF) {
        utf8String += static_cast<char>(0xE0 | ((codepoint >> 12) & 0x0F));
        utf8String += static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F));
        utf8String += static_cast<char>(0x80 | (codepoint & 0x3F));
    }
    else if (codepoint <= 0x10FFFF) {
        utf8String += static_cast<char>(0xF0 | ((codepoint >> 18) & 0x07));
        utf8String += static_cast<char>(0x80 | ((codepoint >> 12) & 0x3F));
        utf8String += static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F));
        utf8String += static_cast<char>(0x80 | (codepoint & 0x3F));
    }
    else {
        PLS_CORE_WARN("UnicodeConverter::ToUTF8: Invalid codepoint: {0}", codepoint);
    }

    return utf8String;
}