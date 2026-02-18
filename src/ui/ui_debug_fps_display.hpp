#ifndef UI_DEBUG_FPS_DISPLAY
#define UI_DEBUG_FPS_DISPLAY

#include <string>
#include "ui_window.hpp"

class UIDebugFPSDisplay : public UIWindow
{
private:
public:
    UIDebugFPSDisplay(std::string name);
    ~UIDebugFPSDisplay() noexcept;

    void operator()() override;
    void operator()(int fps_value, bool provided=true);
};

#endif  // UI_DEBUG_FPS_DISPLAY
