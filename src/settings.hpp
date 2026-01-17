#ifndef SETTINGS_H
#define SETTINGS_H

enum class ZoomLevel { Close, Neutral, Far };

class Settings
{
private:
    ZoomLevel m_ZoomLevel{ZoomLevel::Neutral};  // Remainder to self: this only tracks the state. The projection in RenderMesh has to get this state and react to it accordingly; not other way around.
public:
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

    static Settings& GetSettings();

    void ZoomIn();
    void ZoomOut();

    inline ZoomLevel GetCurrentZoom() const { return m_ZoomLevel; }
private:
    Settings();
    ~Settings() noexcept;
};

#endif //SETTINGS_H
