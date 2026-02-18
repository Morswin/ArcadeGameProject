#include "ui_debug_fps_display.hpp"

#include <sstream>
#include <string>
#include "../third_party/imgui/imgui.h"

UIDebugFPSDisplay::UIDebugFPSDisplay()
    : UIWindow()
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
    if (provided) ImGui::SetNextWindowPos(ImVec2(0.0f, 30.0f), ImGuiCond_Always);
    if (provided && ImGui::Begin("Debug FPS", &m_WindowOpen, m_WindowFlags))
    {
        std::stringstream ss;
        ss << "FPS: " << fps_value;
        ImGui::Text("%s", ss.str().c_str());
    }
    ImGui::End();
}

