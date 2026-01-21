#include "projectile.hpp"

#include <cmath>

Projectile::Projectile(int spriteColumn, int spriteRow)
    : GameElement(spriteColumn, spriteRow), Entity(spriteColumn, spriteRow)
{}

Projectile::~Projectile() noexcept {
}

void Projectile::Simulate(float deltaTime, const std::map<MapPosition, unsigned int>& mapData) {
    m_CurrentLife += deltaTime;
    Entity::Simulate(deltaTime, mapData);
    const glm::vec2 velocity = GetVelocity();
    if (glm::length(velocity) > 0.0001f) {
        const glm::vec2 dir = glm::normalize(velocity);
        const float angle = std::atan2(dir.y, dir.x) - glm::half_pi<float>();
        GetTransform().SetRotation(angle);
    }
}
