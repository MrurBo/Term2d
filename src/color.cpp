#include "term2d/color.hpp"
#include <cstdio>
#include <algorithm>

namespace term2d {

Color::Color(int r, int g, int b) : 
    r(static_cast<uint8_t>(std::clamp(r, 0, 255))),
    g(static_cast<uint8_t>(std::clamp(g, 0, 255))),
    b(static_cast<uint8_t>(std::clamp(b, 0, 255))) {}

bool Color::operator==(const Color& other) const {
    return r == other.r && g == other.g && b == other.b;
}

bool Color::operator!=(const Color& other) const {
    return !(*this == other);
}

std::string Color::to_ansi_fg() const {
    char buf[32];
    snprintf(buf, sizeof(buf), "\033[38;2;%d;%d;%dm", r, g, b);
    return buf;
}

std::string Color::to_ansi_bg() const {
    char buf[32];
    snprintf(buf, sizeof(buf), "\033[48;2;%d;%d;%dm", r, g, b);
    return buf;
}

const std::string Color::reset() {
    return "\033[0m";
}

} // namespace term2d