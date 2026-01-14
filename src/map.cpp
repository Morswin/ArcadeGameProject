#include "map.hpp"

Map::Map() : m_VisibleRange(glm::vec2(5.0f, 4.0f)) {
}

Map::~Map() {
}

void Map::DisplayFloorAndWall(Player& player) const {
}

void Map::RegisterNewEnvironment(unsigned int id, Environment&& environment) {
    m_EnvironmentDictionary.emplace(id, std::move(environment));
}
