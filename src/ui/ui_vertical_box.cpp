#include "ui_vertical_box.hpp"

UIVerticalBox::UIVerticalBox(const std::string &window_name)
    : UIWindow(window_name)
{
}

void UIVerticalBox::operator()()
{
    for (auto& _child : m_Children)
    {
        _child->operator()();
    }
}
