#include "enemy.hpp"

#include <numbers>
#include <cmath>
#include <glm/glm.hpp>
#include "utils/rng.hpp"

Enemy::Enemy(int spriteColumn, int spriteRow)
    : GameElement(spriteColumn, spriteRow), Entity(spriteColumn, spriteRow)
{
    m_Transform.SetScale(glm::vec2(0.9f));
}

Enemy::~Enemy() noexcept {
}

void Enemy::Simulate(float deltaTime , const std::map<MapPosition, unsigned int>& mapData, const Player& player) {
    if (IsProvoked(player)) {
        ChasePlayer(deltaTime, player);
    }
    else {
        WanderAround(deltaTime);
    }
    Entity::Simulate(deltaTime, mapData);
}

void Enemy::ChasePlayer(float deltaTime, const Player& player) {
    glm::vec2 _distanceToPlayer = player.GetTransform().GetPosition() - GetTransform().GetPosition();
    float _distanceLength = glm::length(_distanceToPlayer);
    if (_distanceLength < 0.0001f) {
        m_Velocity = glm::vec2(0.0f);
        return;
    }
    glm::vec2 _direction = _distanceToPlayer / _distanceLength;
    float _speed = std::min(m_ChaseSpeed, _distanceLength);
    m_Velocity = _direction * _speed;
}

void Enemy::WanderAround(float deltaTime) {
    if (m_WanderCounter >= m_WanderCounterTarget) {
        float _angle = RNG::GetRNG().GetNextFloat(0.0f, 2.0f * std::numbers::pi_v<float>);
        glm::vec2 _direction(std::cos(_angle), std::sin(_angle));
        m_Velocity = _direction * m_WanderSpeed;
        m_WanderCounter = 0.0f;
    }
    else {
        m_WanderCounter += deltaTime;
    }
}
