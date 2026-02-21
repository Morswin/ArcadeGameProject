#ifndef UI_DEBUG_FPS_DISPLAY
#define UI_DEBUG_FPS_DISPLAY

#include "ui_window.hpp"

class UIDebugFPSDisplay : public UIWindow
{
private:
public:
    explicit UIDebugFPSDisplay(const std::string& window_name);
    ~UIDebugFPSDisplay() noexcept override = default;

    void operator()() override;
    void operator()(int fps_value) const;
};

#endif  // UI_DEBUG_FPS_DISPLAY
