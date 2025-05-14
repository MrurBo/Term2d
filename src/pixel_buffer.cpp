#include "term2d/pixel_buffer.hpp"
#include <algorithm>
#include <sstream>
#include <cstring>
#include <iostream>

namespace term2d {

PixelBuffer::PixelBuffer(int w, int h) : width(w), height(h) {
    front_buffer.resize(height, std::vector<Color>(width));
    back_buffer.resize(height, std::vector<Color>(width));
}

void PixelBuffer::clear(const Color& color) {
    for (auto& row : back_buffer) {
        std::fill(row.begin(), row.end(), color);
    }
}

void PixelBuffer::set_pixel(int x, int y, const Color& color) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        back_buffer[y][x] = color;
    }
}

void PixelBuffer::render(bool force_full_redraw) {
    static std::vector<std::vector<Color>> last_frame = front_buffer;
    std::stringstream output;

    if (force_full_redraw) {
        output << "\033[2J\033[H";
        last_frame = std::vector<std::vector<Color>>(
            height, std::vector<Color>(width, Color(-1, -1, -1));
    } else {
        output << "\033[H";
    }

    Color current_fg, current_bg;
    bool color_changed = true;

    for (int y = 0; y < height; y += 2) {
        for (int x = 0; x < width; x++) {
            const Color& top = front_buffer[y][x];
            const Color& bottom = (y + 1 < height) ? front_buffer[y + 1][x] : Color(0, 0, 0);

            if (force_full_redraw || top != last_frame[y][x] || 
                (y + 1 < height && bottom != last_frame[y + 1][x])) {
                
                if (top != current_fg || bottom != current_bg) {
                    output << top.to_ansi_fg() << bottom.to_ansi_bg();
                    current_fg = top;
                    current_bg = bottom;
                }
                output << "▀";
            } else {
                output << " ";
            }
        }
        output << Color::reset() << "\n";
    }

    std::cout << output.str() << std::flush;
    last_frame = front_buffer;
}

void PixelBuffer::swap_buffers() {
    front_buffer.swap(back_buffer);
}

int PixelBuffer::get_width() const { return width; }
int PixelBuffer::get_height() const { return height; }

} // namespace term2d
