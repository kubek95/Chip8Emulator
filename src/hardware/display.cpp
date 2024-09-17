#include "display.h"
#include <algorithm>
#include <iostream>

namespace emu
{

Display::Display()
    : pixel_side_{10},
      width_{64 * pixel_side_},
      height_{32 * pixel_side_},
      window_title_{"CHIP-8 emulator"},
      background_color_{105, 156, 49, 255},
      pixel_color_{0, 0, 0, 255},
      renderer_{nullptr},
      window_{nullptr}
{
    init_pixels();
    SDL_Init(SDL_INIT_VIDEO);
    window_ =
        SDL_CreateWindow(window_title_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_, height_, 0);
    renderer_ = SDL_CreateRenderer(window_, -1, 0);
    clear_screen();
}

Display::~Display()
{
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

bool Display::toggle_pixel(std::uint8_t x, std::uint8_t y)
{
    if (!coordinates_valid(x, y)) {
        std::puts("invalid coords");
        return false;
    }
    std::cout << "toggling pixel (" << static_cast<int>(x) << ", " << static_cast<int>(y) << ")\n";
    auto& pixel_to_toggle = get_pixel(x, y).turned_on;
    auto will_be_turned_off = pixel_to_toggle;
    pixel_to_toggle = !pixel_to_toggle;
    return will_be_turned_off;
}

void Display::clear_screen()
{
    SDL_SetRenderDrawColor(
        renderer_, background_color_.r, background_color_.g, background_color_.b, background_color_.a);
    SDL_RenderClear(renderer_);
    SDL_RenderPresent(renderer_);
    std::for_each(pixels_.begin(), pixels_.end(), [](auto& pixel) { pixel.turned_on = false; });
}

void Display::draw()
{
    std::for_each(pixels_.begin(), pixels_.end(), [this](const auto& pixel) { draw_pixel(pixel); });
    SDL_RenderPresent(renderer_);
}

void Display::init_pixels()
{
    auto* pixel = pixels_.begin();
    for (int y{0}; y < 320; y += 10) {
        for (int x{0}; x < 640; x += 10) {
            pixel->rectangle.x = x;
            pixel->rectangle.y = y;
            pixel->rectangle.w = pixel_side_;
            pixel->rectangle.h = pixel_side_;
            pixel = std::next(pixel);
        }
    }
}

void Display::draw_pixel(const Pixel& pixel)
{
    const auto color = pixel.turned_on ? pixel_color_ : background_color_;
    SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer_, &pixel.rectangle);
}

bool Display::coordinates_valid(std::uint8_t x, std::uint8_t y) const
{
    return ((x < width_ - 1) && (y < height_ - 1));
}

Display::Pixel& Display::get_pixel(std::uint8_t x, std::uint8_t y)
{
    const auto position = y * 64 + x;
    return pixels_[position];
}

}  // namespace emu
