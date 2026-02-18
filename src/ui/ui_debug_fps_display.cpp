#include "ui_debug_fps_display.hpp"

#include "../third_party/imgui/imgui.h"
#include "../third_party/imgui/imgui_impl_sdl3.h"
#include "../third_party/imgui/imgui_impl_opengl3.h"
#include <sstream>
#include <string>

UIDebugFPSDisplay::UIDebugFPSDisplay(std::string name)
    : UIWindow(name)
{
}

UIDebugFPSDisplay::~UIDebugFPSDisplay() noexcept
{
}

void UIDebugFPSDisplay::operator()()
{
    this->operator()(0, false);
}

void UIDebugFPSDisplay::operator()(int fps_value, bool provided)
{
    if (provided && ImGui::Begin(m_WindowName.c_str(), &m_WindowOpen, m_WindowFlags))
    {
        std::stringstream ss;
        ss << "FPS: " << fps_value;
        ImGui::Text("%s", ss.str().c_str());
    }
    ImGui::End();
}

