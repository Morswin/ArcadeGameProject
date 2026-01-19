#include "enemy.hpp"

#include <glm/glm.hpp>

Enemy::Enemy(int spriteColumn, int spriteRow)
    : GameElement(spriteColumn, spriteRow), Entity(spriteColumn, spriteRow)
{}

Enemy::~Enemy() noexcept {
}

void Enemy::FollowPlayer(float deltaTime, const Player& player) {
}

void Enemy::WanderAround(float deltaTime) {
}
