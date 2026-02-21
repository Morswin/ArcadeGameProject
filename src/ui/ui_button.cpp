#include "ui_button.hpp"

#include <SDL3/SDL.h>
#include "../third_party/imgui/imgui.h"

UIButton::UIButton(const std::string& window_name, const std::string& label)
    : UIInput(window_name ,label)
{
}

bool UIButton::ReceiveData() {
    return m_Value;
}

void UIButton::operator()()
{
    if (ImGui::Button(m_Label.c_str()))
    {
        m_Value = true;
    }
    else
    {
        m_Value = false;
    }
}
