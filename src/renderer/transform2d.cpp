#include "transform2d.hpp"

Transform2D::Transform2D() {
}

Transform2D::~Transform2D() {
}

glm::mat4 Transform2D::GetMatrix() const {
    glm::mat4 m(1.0f);
    m = glm::translate(m, glm::vec3(m_Position, 0.0f));
    m = glm::rotate(m, m_Rotation, glm::vec3(0, 0, 1));
    m = glm::scale(m, glm::vec3(m_Scale, 1.0f));
    return m;
}
