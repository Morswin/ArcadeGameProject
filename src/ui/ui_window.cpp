#include "ui_window.hpp"

UIWindow::UIWindow(std::string name)
    : m_WindowName(name)
{
}

UIWindow::~UIWindow() noexcept
{
}

void UIWindow::operator()()
{
    if (ImGui::Begin(m_WindowName.c_str(), &m_WindowOpen, m_WindowFlags))
    {
        for (UIWindow* _child : m_Children)
        {
            _child->operator()();
        }
    }
    ImGui::End();
}
