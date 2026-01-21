#include "player.hpp"

Player::Player(int spriteColumn, int spriteRow)
    : GameElement(spriteColumn, spriteRow), Entity(spriteColumn, spriteRow)
{
    m_Transform.SetScale(glm::vec2(0.8f));
}

Player::~Player() noexcept {
}

void Player::SetMovementInputForce(glm::vec2 input) {
    if (glm::length(input) > 0.0f) {
        m_Velocity = input * m_MovementSpeed;
        m_IsMoving = true;
    }
}

void Player::Simulate(float deltaTime, const std::map<MapPosition, unsigned int>& mapData) {
    m_CurrentProjectileReadiness += deltaTime;
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
    Entity::Simulate(deltaTime, mapData);
    m_View = m_Transform.GetPosition();
    m_IsMoving = false;
}

glm::mat4 Player::GetViewMatrix() const {
    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(-GetView(), 0.0f));
    return view;
}

void Player::HealByAmount(double amount) {
    m_CurrentHealthPoints += amount;
    if (m_CurrentHealthPoints > m_InitialHealthPoints) m_CurrentHealthPoints = m_InitialHealthPoints;
}

