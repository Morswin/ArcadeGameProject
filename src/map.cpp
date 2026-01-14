#include "map.hpp"

#include <cmath>

Map::Map() : m_VisibleRange(glm::vec2(5.0f, 4.0f)) {
    for (int i = -3; i <= 3; i++) {
        for (int j = -3; j <= 3; j++) {
            m_PresentMapData.emplace(TilePosition{i, j}, 0);
        }
    }
}

Map::~Map() {
}

void Map::DisplayFloorAndWall(Player& player, Renderer& renderer) {
    int lowX, highX, lowY, highY;
    glm::vec2 playerPosition = player.GetTransform().GetPosition();
    lowX = static_cast<int>(std::floor(playerPosition.x - m_VisibleRange.x));
    lowY = static_cast<int>(std::floor(playerPosition.y - m_VisibleRange.y));
    highX = static_cast<int>(std::ceil(playerPosition.x + m_VisibleRange.x));
    highY = static_cast<int>(std::ceil(playerPosition.y + m_VisibleRange.y));
    for (int x = lowX; x <= highX; x++) {
        for (int y = lowY; y <= highY; y++) {
            TilePosition _position{x, y};
            auto _dictionaryKey = m_PresentMapData.find(_position);
            if (_dictionaryKey != m_PresentMapData.end()) {
                m_EnvironmentDictionary.at(_dictionaryKey->second).GetTransform().SetPosition(glm::vec2(1.0f * x, 1.0f * y));
                m_EnvironmentDictionary.at(_dictionaryKey->second).Display(renderer);
            }
        }
    }
}

void Map::RegisterNewEnvironment(unsigned int id, Environment&& environment) {
    m_EnvironmentDictionary.emplace(id, std::move(environment));
}
