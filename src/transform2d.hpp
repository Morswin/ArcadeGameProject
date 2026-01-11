#ifndef TRANSFORM_2D_H
#define TRANSFORM_2D_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Transform2D {
    glm::vec2 position{0.0f};
    float rotation{0.0f};
    glm::vec2 scale{1.0f};

    glm::mat4 matrix() const {
        glm::mat4 m(1.0f);
        m = glm::translate(m, glm::vec3(position, 0.0f));
        m = glm::rotate(m, rotation, glm::vec3(0, 0, 1));
        m = glm::scale(m, glm::vec3(scale, 1.0f));
        return m;
    }
};

#endif // TRANSFORM_2D_H
