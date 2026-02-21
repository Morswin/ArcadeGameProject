#ifndef UI_PLAYER_STATISTICS_HPP
#define UI_PLAYER_STATISTICS_HPP

#include "ui_window.hpp"

class UIPlayerStatistics : public UIWindow
{
private:
public:
    explicit UIPlayerStatistics(const std::string& window_name);
    ~UIPlayerStatistics() noexcept override = default;

    void operator()() override;
    void operator()(float player_health) const;
};

#endif  // UI_PLAYER_STATISTICS_HPP
