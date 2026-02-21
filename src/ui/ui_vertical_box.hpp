#ifndef UI_VERTICAL_BOX_HPP
#define UI_VERTICAL_BOX_HPP

#include "ui_window.hpp"

class UIVerticalBox : public UIWindow
{
private:
public:
    UIVerticalBox(const std::string& window_name);
    ~UIVerticalBox() noexcept override = default;

    void operator()() override;
};

#endif //UI_VERTICAL_BOX_HPP