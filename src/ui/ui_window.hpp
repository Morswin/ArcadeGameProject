#ifndef UI_WINDOW_HPP
#define UI_WINDOW_HPP

#include <vector>
#include "../third_party/imgui/imgui.h"

class UIWindow
{
protected:
    bool m_WindowOpen{true};
    ImGuiWindowFlags m_WindowFlags{0};
    std::vector<UIWindow*> m_Children;
public:
    explicit UIWindow();
    virtual ~UIWindow() noexcept;

    virtual void operator()();

    inline void AddFlag(const ImGuiWindowFlags flag) { m_WindowFlags |= flag; }
};

#endif  // UI_WINDOW_HPP
