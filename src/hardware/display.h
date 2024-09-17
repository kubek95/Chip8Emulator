#ifndef SRC_HARDWARE_DISPLAY_H
#define SRC_HARDWARE_DISPLAY_H

#include <SDL2/SDL.h>
#include <array>
#include <cstdint>
#include <string>

namespace emu
{
class Display
{
  public:
    Display();
    ~Display();
    Display(const Display&) = delete;
    Display& operator=(const Display&) = delete;

    bool toggle_pixel(std::uint8_t x, std::uint8_t y);
    void clear_screen();
    void draw();

  private:
    struct Color
    {
        std::uint8_t r, g, b, a;
    };
    struct Pixel
    {
        SDL_Rect rectangle;
        bool turned_on{false};
    };

    void init_pixels();
    void draw_pixel(const Pixel& pixel);
    bool coordinates_valid(std::uint8_t x, std::uint8_t y) const;
    Pixel& get_pixel(std::uint8_t x, std::uint8_t y);

    const int pixel_side_;
    const int width_;
    const int height_;
    const std::string window_title_;
    const Color background_color_;
    const Color pixel_color_;
    std::array<Pixel, 64 * 32> pixels_;
    SDL_Renderer* renderer_;
    SDL_Window* window_;
};
}  // namespace emu

#endif  // SRC_HARDWARE_DISPLAY_H