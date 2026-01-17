#include "settings.hpp"

Settings::Settings() {
}

Settings::~Settings() noexcept {
}

Settings & Settings::GetSettings() {
    static Settings settingsInstance;
    return settingsInstance;
}

void Settings::ZoomIn() {
    switch (m_ZoomLevel) {
    case ZoomLevel::Far:
        m_ZoomLevel = ZoomLevel::Neutral;
        break;
    case ZoomLevel::Neutral:
        m_ZoomLevel = ZoomLevel::Close;
        break;
    case ZoomLevel::Close:
    default:
        break; // Nothing changes
    }
}

void Settings::ZoomOut() {
    switch (m_ZoomLevel) {
    case ZoomLevel::Close:
        m_ZoomLevel = ZoomLevel::Neutral;
        break;
    case ZoomLevel::Neutral:
        m_ZoomLevel = ZoomLevel::Far;
        break;
    case ZoomLevel::Far:
    default:
        break; // Nothing changes
    }
}

