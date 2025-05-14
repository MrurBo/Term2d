#pragma once
#include <cstdint>
#include <string>
#include <algorithm>

namespace term2d {
class Color {
public:
    uint8_t r, g, b;
    
    Color(int r = 0, int g = 0, int b = 0);
    bool operator==(const Color& other) const;
    bool operator!=(const Color& other) const;
    std::string to_ansi_fg() const;
    std::string to_ansi_bg() const;
    static const std::string reset();
};
} // namespace term2d