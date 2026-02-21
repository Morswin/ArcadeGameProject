#ifndef UI_SETTINGS_HPP
#define UI_SETTINGS_HPP

#include "ui_window.hpp"

class UISettings : public UIWindow
{
private:
public:
    UISettings(const std::string& window_name);
    ~UISettings() noexcept override = default;
};

#endif //UI_SETTINGS_HPP