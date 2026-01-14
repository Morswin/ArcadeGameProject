#ifndef MAP_H
#define MAP_H

#include <map>
#include <glm/glm.hpp>
#include "environment.hpp"
#include "player.hpp"

// Glm vectors don't want to cooperate, so I may be forced to work with this handcrafted atrocity below. I'm sorry that you have to look at this
struct TilePosition {
    int x, y;

    bool operator<(const TilePosition& other) const {
        return std::tie(x, y) < std::tie(other.x, other.y);
    }
};

class Map
{
private:
    glm::vec2 m_VisibleRange;
    std::map<TilePosition, unsigned int> m_PresentMapData;  // Keeps all of the data related to the corrently loaded level map
    std::map<unsigned int, Environment> m_EnvironmentDictionary;  // Assigns unsigned int "IDs" for all Environment entries needed for the level map to work properly
public:
    Map();
    ~Map();

    void DisplayFloorAndWall(Player& player, Renderer& renderer);
    void RegisterNewEnvironment(unsigned int id, Environment&& environment);
};

#endif //MAP_H
