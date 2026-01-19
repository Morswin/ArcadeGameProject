#ifndef COLLISION_H
#define COLLISION_H

#include <glm/glm.hpp>
#include "renderer/transform2d.hpp"

class Collision {
private:
    glm::vec2 m_Size;
    glm::vec2 m_Offset;
public:
    Collision(const glm::vec2& size = glm::vec2(1.0f), const glm::vec2& offset = glm::vec2(0.0f));
    ~Collision();

    glm::vec2 GetMin(const Transform2D& transform) const;
    glm::vec2 GetMax(const Transform2D& transform) const;
    bool Intersects(const Collision& other, const Transform2D& myTransform, const Transform2D& otherTransform) const;
    void SetSize(const glm::vec2& size);
    void SetOffset(const glm::vec2& offset);
    const glm::vec2& GetSize() const;
    const glm::vec2& GetOffset() const;
};

#endif  // COLLISION_H
