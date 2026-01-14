#ifndef SDL_ERROR_H
#define SDL_ERROR_H

#include <stdexcept>

class sdl_error : public std::runtime_error {
public:
    explicit sdl_error(const std::string& msg) : std::runtime_error(msg) {}
};

#endif  // SDL_ERROR_H
