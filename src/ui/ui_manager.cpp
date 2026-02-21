#include "ui_manager.hpp"

#include "ui_debug_fps_display.hpp"
#include "ui_player_statistics.hpp"
#include "ui_button.hpp"

UIManager::UIManager()
{
    auto* player_statistics = new UIPlayerStatistics("Player Statistics");
    player_statistics->AddFlag(ImGuiWindowFlags_NoTitleBar);
    player_statistics->AddFlag(ImGuiWindowFlags_NoBackground);
    player_statistics->AddFlag(ImGuiWindowFlags_NoResize);
    player_statistics->AddFlag(ImGuiWindowFlags_NoMove);
    player_statistics->AddFlag(ImGuiWindowFlags_AlwaysAutoResize);
    RegisterNewWindow(player_statistics);
    auto* debug_fps_display = new UIDebugFPSDisplay("Debug FPS");
    debug_fps_display->AddFlag(ImGuiWindowFlags_NoTitleBar);
    debug_fps_display->AddFlag(ImGuiWindowFlags_NoBackground);
    debug_fps_display->AddFlag(ImGuiWindowFlags_NoResize);
    debug_fps_display->AddFlag(ImGuiWindowFlags_NoDocking);
    debug_fps_display->AddFlag(ImGuiWindowFlags_NoMove);
    debug_fps_display->AddFlag(ImGuiWindowFlags_AlwaysAutoResize);
    RegisterNewWindow(debug_fps_display);
    auto* button = new UIButton("Test Button", "Click me!");
    button->AddFlag(ImGuiWindowFlags_NoTitleBar);
    button->AddFlag(ImGuiWindowFlags_NoBackground);
    button->AddFlag(ImGuiWindowFlags_NoResize);
    button->AddFlag(ImGuiWindowFlags_NoDocking);
    button->AddFlag(ImGuiWindowFlags_NoMove);
    button->AddFlag(ImGuiWindowFlags_AlwaysAutoResize);
    RegisterNewWindow(button);
}

UIManager::~UIManager() noexcept
{
    for (UIWindow* _window : m_Windows) delete _window;
    m_Windows.clear();
}

void UIManager::UseWindows() const
{
    for (UIWindow* _window : m_Windows)
    {
        if (auto* _ui_fps_display = dynamic_cast<UIDebugFPSDisplay*>(_window))
        {
            ImGui::SetNextWindowPos(ImVec2(0.0f, 30.0f), ImGuiCond_Always);
            if (ImGui::Begin(
                _ui_fps_display->GetWindowName().c_str(),
                _ui_fps_display->IsWindowOpen(),
                _ui_fps_display->GetWindowFlags()
                ))
            {
                _ui_fps_display->operator()(m_LastKnownFPS);
            }
            ImGui::End();
        }
        else if (auto* _ui_player_statistics = dynamic_cast<UIPlayerStatistics*>(_window))
        {
            ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
            if (ImGui::Begin(
                _ui_player_statistics->GetWindowName().c_str(),
                _ui_player_statistics->IsWindowOpen(),
                _ui_player_statistics->GetWindowFlags()
                ))
            {
                _ui_player_statistics->operator()(m_PlayerHealth);
            }
            ImGui::End();
        }
        else
        {
            if (ImGui::Begin(
                _window->GetWindowName().c_str(),
                _window->IsWindowOpen(),
                _window->GetWindowFlags()
                ))
            {
                _window->operator()();
            }
            ImGui::End();
        }
    }
}
