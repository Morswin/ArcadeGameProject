#ifndef UI_INPUT_HPP
#define UI_INPUT_HPP

#include "ui_window.hpp"

#include <string>

class UIInput : public UIWindow
{
protected:
    std::string m_Label;
public:
    explicit UIInput(const std::string& window_name, const std::string& label);
    ~UIInput() noexcept override = default;
};

#endif //UI_INPUT_HPP