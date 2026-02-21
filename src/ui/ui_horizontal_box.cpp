#include "ui_horizontal_box.hpp"

#include "../third_party/imgui/imgui.h"

UIHorizontalBox::UIHorizontalBox(const std::string &window_name)
    : UIWindow(window_name)
{
}

void UIHorizontalBox::operator()()
{
    // None - does nothing
    // One - just display
    // More - display first, then display the res, prepending each window with 'same line' thing
    if (m_Children.empty()) return;
    else if (m_Children.size() == 1) m_Children.at(0)->operator()();
    else
    {
        // Hopefully I did the index math right :3
        m_Children.at(0)->operator()();
        for (size_t i = 1; i < m_Children.size(); ++i)
        {
            ImGui::SameLine();
            m_Children.at(i)->operator()();
        }
    }
}
