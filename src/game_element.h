#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

#include "glm/glm.hpp"
#include "renderer/renderer.h"
#include "renderer/render_mesh.h"
#include "transform2d.h"

class GameElement
{
protected:
    Transform2D m_Transform;
    bool m_Visible = true;
    RenderMesh* m_Mesh = nullptr;
public:
    // virtual ~GameElement() = default;

    // virtual void Simulate(float deltaTime);// = 0;

    void Display(const Renderer& renderer) const;

    void SetMesh(RenderMesh* mesh);
    void SetPosition(glm::vec2 position);
    void SetRotation(float rotation);
    void SetScale(glm::vec2 scale);
    Transform2D GetTransform() const { return m_Transform; }
    glm::vec2 GetPosition() const { return m_Transform.position; }
    glm::mat4 GetTransformMatrix() const { return m_Transform.matrix(); }
};

#endif //GAME_ELEMENT_H
