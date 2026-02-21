#include "ui_player_statistics.hpp"

#include "../third_party/imgui/imgui.h"

UIPlayerStatistics::UIPlayerStatistics(const std::string &window_name)
    : UIWindow(window_name)
{
}

void UIPlayerStatistics::operator()()
{
    this->operator()(0.0f);
}

void UIPlayerStatistics::operator()(float player_health) const
{
    ImGui::Text("HP: ");
    ImGui::SameLine();
    // It's being divided, because app tracks health in 0.0 to 100.0 range,
    // and ImGui expects 0.0 to 1.0 range
    //
    ImGui::ProgressBar(
        player_health/100.0f,
        ImVec2(ImGui::GetMainViewport()->Size.x / 6.0f, 0.0f)
        );
}
