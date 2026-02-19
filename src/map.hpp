#ifndef MAP_H
#define MAP_H

#include <map>
#include <vector>
#include <glm/glm.hpp>
#include "map_position.hpp"
#include "environment.hpp"
#include "player.hpp"
#include "room.hpp"
#include "enemy.hpp"

class Map
{
private:
    glm::vec2 m_VisibleRange;
    std::map<MapPosition, unsigned int> m_PresentMapData;  // Keeps all of the data related to the corrently loaded level map
    std::map<unsigned int, Environment> m_EnvironmentDictionary;  // Assigns unsigned int "IDs" for all Environment entries needed for the level map to work properly
    bool m_RelocatePlayer = false;  // This will be set to true at the end of each map generation; after which player should get relocated to the m_RelocatePlayerLocation value. The relocation should happen somewhere in Game class.
    glm::vec2 m_RelocatePlayerLocation = glm::vec2{0.0f, 0.0f};  // For more explanation see comment by the m_RelocatePlayer.

    // Data for generating a new map:
    int m_NumberOfRooms{150};
    std::map<MapPosition, Room> m_Rooms;
public:
    Map();
    ~Map() = default;

    void DisplayFloorAndWall(Player& player, Renderer& renderer);
    void RegisterNewEnvironment(unsigned int id, Environment&& environment);
    void GenerateNewMap();
    std::vector<glm::vec2> PopulateMapWithEnemies(double percentage);

    inline bool ShouldPlayerRelocate() { return m_RelocatePlayer; }
    inline glm::vec2 GetPlayerStartLocation() { m_RelocatePlayer = false; return m_RelocatePlayerLocation; }
    inline std::map<MapPosition, unsigned int>& GetMapData() { return m_PresentMapData; }
};

#endif //MAP_H
