#include "ui_window.hpp"

#include <SDL3/SDL.h>

UIWindow::UIWindow(const std::string& window_name)
    : m_WindowName(window_name)
{
}

void UIWindow::operator()()
{
    // Not sure whether to make this virtual, or put here some debug information.
    // Both are tempting :3
    SDL_LogWarn(SDL_LOG_CATEGORY_ERROR, "Attempting to use a virtual ui window's operator()() ?");
}
