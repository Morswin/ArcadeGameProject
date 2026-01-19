#include "collision.hpp"

Collision::Collision(const glm::vec2& size, const glm::vec2& offset)
    : m_Size(size), m_Offset(offset)
{}

Collision::~Collision() {
}

glm::vec2 Collision::GetMin(const Transform2D& transform) const {
    return transform.GetPosition() + m_Offset * transform.GetScale();
}

glm::vec2 Collision::GetMax(const Transform2D& transform) const {
    return GetMin(transform) + m_Size * transform.GetScale();
}

bool Collision::Intersects(const Collision& other, const Transform2D& myTransform, const Transform2D& otherTransform) const {
    glm::vec2 aMin = GetMin(myTransform);
    glm::vec2 aMax = GetMax(myTransform);
    glm::vec2 bMin = other.GetMin(otherTransform);
    glm::vec2 bMax = other.GetMax(otherTransform);
    return aMin.x < bMax.x && aMax.x > bMin.x && aMin.y < bMax.y && aMax.y > bMin.y;
}

void Collision::SetSize(const glm::vec2& size) {
    m_Size = size;
}

void Collision::SetOffset(const glm::vec2& offset) {
    m_Offset = offset;
}

const glm::vec2 & Collision::GetSize() const {
    return m_Size;
}

const glm::vec2 & Collision::GetOffset() const {
    return m_Offset;
}

