#pragma once
#include "color.hpp"
#include <vector>

namespace term2d {
class PixelBuffer {
    std::vector<std::vector<Color>> front_buffer;
    std::vector<std::vector<Color>> back_buffer;
    int width, height;

public:
    PixelBuffer(int w, int h);
    void clear(const Color& color = Color(0, 0, 0));
    void set_pixel(int x, int y, const Color& color);
    void render(bool force_full_redraw = false);
    void swap_buffers();
    int get_width() const;
    int get_height() const;
};
} // namespace term2d