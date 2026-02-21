#include "ui_input.hpp"

template <typename T>
UIInput<T>::UIInput(const std::string& window_name, const std::string& label)
    : UIWindow(window_name), m_Label(label)
{
}
