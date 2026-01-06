#include <stdexcept>

class sdl_error : public std::runtime_error {
public:
    explicit sdl_error(const std::string& msg) : std::runtime_error(msg) {}
};
