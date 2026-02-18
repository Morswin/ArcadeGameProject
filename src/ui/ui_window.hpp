#ifndef UI_WINDOW_HPP
#define UI_WINDOW_HPP

#include <string>
#include <vector>
#include "../third_party/imgui/imgui.h"
#include "../third_party/imgui/imgui_impl_sdl3.h"
#include "../third_party/imgui/imgui_impl_opengl3.h"

class UIWindow
{
protected:
    bool m_WindowOpen{true};
    std::string m_WindowName;
    ImGuiWindowFlags m_WindowFlags{0};
    std::vector<UIWindow*> m_Children;
public:
    UIWindow(std::string name);
    virtual ~UIWindow() noexcept;

    virtual void operator()();
};

#endif  // UI_WINDOW_HPP
