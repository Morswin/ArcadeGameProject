#ifndef TRANSFORM_2D_H
#define TRANSFORM_2D_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform2D {
private:
    glm::vec2 m_Position{0.0f};
    float m_Rotation{0.0f};
    glm::vec2 m_Scale{1.0f};
public:
    Transform2D();
    ~Transform2D();

    glm::mat4 GetMatrix() const;

    inline glm::vec2 GetPosition() const { return m_Position; }
    inline glm::vec2 GetScale() const { return m_Scale; }
    inline void SetPosition(glm::vec2 position) { m_Position = position; }
    inline void SetScale(glm::vec2 scale) { m_Scale = scale; }
};

#endif // TRANSFORM_2D_H
