#ifndef UI_MAIN_MENU_HPP
#define UI_MAIN_MENU_HPP

#include "ui_window.hpp"

class UIMainMenu : public UIWindow
{
private:
public:
    UIMainMenu(const std::string& window_name);
    ~UIMainMenu() noexcept override = default;
};


#endif //UI_MAIN_MENU_HPP