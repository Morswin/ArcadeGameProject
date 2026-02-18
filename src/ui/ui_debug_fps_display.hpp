#ifndef UI_DEBUG_FPS_DISPLAY
#define UI_DEBUG_FPS_DISPLAY

#include "ui_window.hpp"

class UIDebugFPSDisplay : public UIWindow
{
private:
public:
    explicit UIDebugFPSDisplay();
    ~UIDebugFPSDisplay() noexcept override;

    void operator()() override;
    void operator()(int fps_value, bool provided=true);
};

#endif  // UI_DEBUG_FPS_DISPLAY
