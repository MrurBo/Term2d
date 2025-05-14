#pragma once
#include "pixel_buffer.hpp"
#include <memory>

namespace term2d {
class TerminalRenderer {
    std::unique_ptr<PixelBuffer> buffer;
    bool vsync_enabled;

public:
    TerminalRenderer(int width, int height, bool vsync = true);
    ~TerminalRenderer();
    void configure_terminal();
    void cleanup_terminal();
    void clear(const Color& color = Color(0, 0, 0));
    void draw_pixel(int x, int y, const Color& color);
    void present(bool force_full_redraw = false);
};
} // namespace term2d