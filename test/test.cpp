#include "term2d/terminal_renderer.hpp"
#include <thread>
#include <chrono>

int main() {
    term2d::TerminalRenderer renderer(80, 40);
    
    // Draw gradient
    for (int y = 0; y < renderer.get_height(); y++) {
        for (int x = 0; x < renderer.get_width(); x++) {
            renderer.draw_pixel(x, y, 
                term2d::Color(
                    x * 255 / renderer.get_width(),
                    y * 255 / renderer.get_height(),
                    (x + y) * 255 / (renderer.get_width() + renderer.get_height())
                ));
        }
        renderer.present();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    
    return 0;
}