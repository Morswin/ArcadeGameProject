#ifndef UI_MANAGER_HPP
#define UI_MANAGER_HPP

#include <vector>
#include "ui_window.hpp"

class UIManager
{
private:
    std::vector<UIWindow*> m_Windows{};
    int m_LastKnownFPS{0};
    float m_PlayerHealth{0.0f};
public:
    UIManager();
    ~UIManager() noexcept;

    void UseWindows() const;
    void RegisterNewWindow(UIWindow* window) { m_Windows.push_back(window); }

    inline void UpdateLastKnownFPS(const int fps) { m_LastKnownFPS = fps; }
    inline void UpdatePlayerHealth(const float health) { m_PlayerHealth = health; }
};

#endif  // UI_MANAGER_HPP
