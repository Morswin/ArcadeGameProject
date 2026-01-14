#ifndef MAP_H
#define MAP_H

#include <map>
#include <glm/glm.hpp>
#include "environment.hpp"
#include "player.hpp"

inline bool operator<(const glm::ivec2& a, const glm::ivec2& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

class Map
{
private:
    glm::vec2 m_VisibleRange;
    std::map<glm::ivec2, unsigned int> m_PresentMapData;  // Keeps all of the data related to the corrently loaded level map
    std::map<unsigned int, Environment> m_EnvironmentDictionary;  // Assigns unsigned int "IDs" for all Environment entries needed for the level map to work properly
public:
    Map();
    ~Map();

    void DisplayFloorAndWall(Player& player) const;
    void RegisterNewEnvironment(unsigned int id, Environment&& environment);
};

#endif //MAP_H
