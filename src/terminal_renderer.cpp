#include "term2d/terminal_renderer.hpp"
#include <cstdlib>
#include <iostream>

namespace term2d {

TerminalRenderer::TerminalRenderer(int width, int height, bool vsync) : 
    buffer(std::make_unique<PixelBuffer>(width, height)),
    vsync_enabled(vsync) {
    configure_terminal();
}

TerminalRenderer::~TerminalRenderer() {
    cleanup_terminal();
}

void TerminalRenderer::configure_terminal() {
    std::system("echo -ne '\\033%G\\033[?25l'");
    std::cout << "\033[2J\033[H" << std::flush;
}

void TerminalRenderer::cleanup_terminal() {
    std::cout << Color::reset() << "\033[2J\033[H\033[?25h" << std::flush;
}

void TerminalRenderer::clear(const Color& color) {
    buffer->clear(color);
}

void TerminalRenderer::draw_pixel(int x, int y, const Color& color) {
    buffer->set_pixel(x, y, color);
}

void TerminalRenderer::present(bool force_full_redraw) {
    buffer->swap_buffers();
    buffer->render(force_full_redraw);
}

} // namespace term2d