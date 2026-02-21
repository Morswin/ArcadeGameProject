#include "ui_debug_fps_display.hpp"

#include <sstream>
#include <string>
#include "../third_party/imgui/imgui.h"

UIDebugFPSDisplay::UIDebugFPSDisplay(const std::string& window_name)
    : UIWindow(window_name)
{
}

void UIDebugFPSDisplay::operator()()
{
    this->operator()(0);
}

void UIDebugFPSDisplay::operator()(int fps_value) const
{
    std::stringstream ss;
    ss << "FPS: " << fps_value;
    ImGui::Text("%s", ss.str().c_str());
}

