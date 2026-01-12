#include "player.hpp"

Player::Player() : GameElement(), Entity() {
}

Player::~Player() noexcept {
}

void Player::SetMovementInputForce(glm::vec2 input) {
    if (glm::length(input) > 0.0f) {
        AddForce(input * m_MovementSpeed);
        m_IsMoving = true;
    }
}

void Player::Simulate(float deltaTime) {
    if (!m_IsMoving) {
        float friction = 5.0f * deltaTime;
        glm::vec2 target = glm::vec2(0.0f);
        glm::vec2 delta = target - m_Velocity;
        float distance = glm::length(delta);
        if (distance <= friction || distance == 0.0f) {
            m_Velocity = target;
        }
        else {
            m_Velocity = m_Velocity + delta / distance * friction;
        }
    }
    Entity::Simulate(deltaTime);
    m_IsMoving = false;
}
