#ifndef UI_BUTTON_HPP
#define UI_BUTTON_HPP

#include "ui_input.hpp"

#include <string>

class UIButton : public UIInput<bool>
{
private:
    bool m_Value{false};
public:
    explicit UIButton(const std::string& window_name, const std::string& label);
    ~UIButton() noexcept override = default;

    void operator()() override;
    bool ReceiveData() override;
};

#endif //UI_BUTTON_HPP