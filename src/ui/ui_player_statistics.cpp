#include "ui_player_statistics.hpp"

#include "../third_party/imgui/imgui.h"

UIPlayerStatistics::UIPlayerStatistics()
    : UIWindow()
{
}

UIPlayerStatistics::~UIPlayerStatistics() noexcept
{
}

void UIPlayerStatistics::operator()()
{
    this->operator()(0.0f, false);
}

void UIPlayerStatistics::operator()(float player_health, bool provided)
{
    if (provided) ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
    if (provided && ImGui::Begin("Player Statistics", &m_WindowOpen, m_WindowFlags))
    {
        ImGui::Text("HP: ");
        ImGui::SameLine();
        // It's being divided, because app tracks health in 0.0 to 100.0 range,
        // and ImGui expects 0.0 to 1.0 range
        ImGui::ProgressBar(player_health/100.0f, ImVec2(-1.0f, 0.0f));
    }
    ImGui::End();
}
