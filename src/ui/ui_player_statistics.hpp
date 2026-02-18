#ifndef UI_PLAYER_STATISTICS_HPP
#define UI_PLAYER_STATISTICS_HPP

#include "ui_window.hpp"

class UIPlayerStatistics : public UIWindow
{
private:
public:
    explicit UIPlayerStatistics();
    ~UIPlayerStatistics() noexcept override;

    void operator()() override;
    void operator()(float player_health, bool provided=true);
};

#endif  // UI_PLAYER_STATISTICS_HPP
