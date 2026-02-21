#ifndef UI_WINDOW_HPP
#define UI_WINDOW_HPP

#include <vector>
#include <string>
#include "../third_party/imgui/imgui.h"

class UIWindow
{
protected:
    bool m_WindowOpen{true};
    ImGuiWindowFlags m_WindowFlags{0};
    std::vector<UIWindow*> m_Children;
    std::string m_WindowName;
public:
    explicit UIWindow(const std::string& window_name);
    virtual ~UIWindow() noexcept = default;

    virtual void operator()();

    inline void AddFlag(const ImGuiWindowFlags flag) { m_WindowFlags |= flag; }
    inline void AddChild(UIWindow* child) { m_Children.push_back(child); }
    inline ImGuiWindowFlags GetWindowFlags() const { return m_WindowFlags; }
    inline bool* IsWindowOpen() { return &m_WindowOpen; }
    inline std::string GetWindowName() const { return m_WindowName; }
};

#endif  // UI_WINDOW_HPP
