#ifndef UI_INPUT_HPP
#define UI_INPUT_HPP

#include "ui_window.hpp"

#include <string>

template<typename T>
class UIInput : public UIWindow
{
protected:
    std::string m_Label;
public:
    explicit UIInput(const std::string& window_name, const std::string& label);
    ~UIInput() noexcept override = default;

    virtual T ReceiveData() = 0;
};

template class UIInput<bool>;

#endif //UI_INPUT_HPP