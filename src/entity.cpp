#include "entity.hpp"

Entity::Entity(int spriteColumn, int spriteRow)
    : GameElement(spriteColumn, spriteRow), m_Velocity(glm::vec2(0.0f)), m_Acceleration(glm::vec2(0.0f)), m_Forces(std::vector<glm::vec2>()), m_Collision(glm::vec2(1.0f, 1.0f))
{}

Entity::~Entity() noexcept {
}

void Entity::Simulate(float deltaTime, const std::map<MapPosition, unsigned int>& mapData) {
    m_Acceleration = glm::vec2(0.0f);
    for (glm::vec force : m_Forces) {
        m_Acceleration += force;
    }
    m_Velocity += m_Acceleration * deltaTime;
    // m_Transform.SetPosition(m_Transform.GetPosition() + m_Velocity * deltaTime);
    // m_Forces.clear();
    glm::vec2 oldPosition = m_Transform.GetPosition();
    m_Transform.SetPosition(oldPosition + glm::vec2(m_Velocity.x * deltaTime, 0.0f));
    if (CollidesWithMap(mapData)) {
        m_Transform.SetPosition(oldPosition);
        m_Velocity.x = 0.0f;
    }
    oldPosition = m_Transform.GetPosition();
    m_Transform.SetPosition(oldPosition + glm::vec2(0.0f, m_Velocity.y * deltaTime));
    if (CollidesWithMap(mapData)) {
        m_Transform.SetPosition(oldPosition);
        m_Velocity.y = 0.0f;
    }
    m_Forces.clear();
}

void Entity::AddForce(glm::vec2 force) {
    m_Forces.push_back(force);
}

bool Entity::CollidesWithMap(const std::map<MapPosition, unsigned int>& mapData) const
{
    constexpr float tileSize = 1.0f;
    glm::vec2 min = m_Collision.GetMin(m_Transform);
    glm::vec2 max = m_Collision.GetMax(m_Transform);
    int minTileX = static_cast<int>(std::floor(min.x));
    int minTileY = static_cast<int>(std::floor(min.y));
    int maxTileX = static_cast<int>(std::ceil(max.x)) - 1;
    int maxTileY = static_cast<int>(std::ceil(max.y)) - 1;

    for (int y = minTileY; y <= maxTileY; ++y)
    {
        for (int x = minTileX; x <= maxTileX; ++x)
        {
            MapPosition pos{ x, y };
            auto it = mapData.find(pos);

            if (it != mapData.end() && it->second == 10)
            {
                return true;
            }
        }
    }
    return false;
}

bool Entity::Overlaps(const Entity& other) const
{
    return m_Collision.Intersects(other.m_Collision, m_Transform, other.m_Transform);
}
