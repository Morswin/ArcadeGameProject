#include "entity.hpp"

Entity::Entity(int spriteColumn, int spriteRow)
    : GameElement(spriteColumn, spriteRow), m_Velocity(glm::vec2(0.0f)), m_Acceleration(glm::vec2(0.0f)), m_Forces(std::vector<glm::vec2>())
{}

Entity::~Entity() noexcept {
}

void Entity::Simulate(float deltaTime) {
    m_Acceleration = glm::vec2(0.0f);
    for (glm::vec force : m_Forces) {
        m_Acceleration += force;
    }
    m_Velocity += m_Acceleration * deltaTime;
    m_Transform.SetPosition(m_Transform.GetPosition() + m_Velocity * deltaTime);
    m_Forces.clear();
}

void Entity::AddForce(glm::vec2 force) {
    m_Forces.push_back(force);
}

