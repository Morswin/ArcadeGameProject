#ifndef UI_HORIZONTAL_BOX_HPP
#define UI_HORIZONTAL_BOX_HPP

#include "ui_window.hpp"

class UIHorizontalBox : public UIWindow
{
private:
public:
    UIHorizontalBox(const std::string& window_name);
    ~UIHorizontalBox() noexcept override = default;

    void operator()() override;
};

#endif //UI_HORIZONTAL_BOX_HPP