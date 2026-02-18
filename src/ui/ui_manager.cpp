#include "ui_manager.hpp"

#include "ui_debug_fps_display.hpp"
#include "ui_player_statistics.hpp"

UIManager::~UIManager() noexcept
{
    for (UIWindow* _window : m_Windows) delete _window;
    m_Windows.clear();
}

void UIManager::UseWindows() const
{
    for (UIWindow* _window : m_Windows)
    {
        if (UIDebugFPSDisplay* _ui = dynamic_cast<UIDebugFPSDisplay*>(_window))
        {
            _ui->operator()(m_LastKnownFPS);
        }
        else if (UIPlayerStatistics* _ui = dynamic_cast<UIPlayerStatistics*>(_window))
        {
            _ui->operator()(m_PlayerHealth);
        }
        else
        {
            _window->operator()();;
        }
    }
}
