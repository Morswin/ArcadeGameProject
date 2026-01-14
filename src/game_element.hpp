#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

#include <glm/glm.hpp>
#include "renderer/renderer.hpp"
#include "renderer/render_mesh.hpp"
#include "renderer/transform2d.hpp"

class GameElement
{
protected:
    Transform2D m_Transform;
    bool m_Visible = true;
    RenderMesh* m_Mesh = nullptr;
    int m_SpriteColumn{0};
    int m_SpriteRow{0};
public:
    GameElement(int spriteColumn, int spriteRow);
    virtual ~GameElement() = default;

    virtual void Simulate(float deltaTime) = 0;
    void Display(const Renderer& renderer) const;

    void SetMesh(RenderMesh* mesh);
    inline Transform2D& GetTransform() { return m_Transform; }
    inline glm::vec2 GetPosition() const { return m_Transform.GetPosition(); }
    inline glm::mat4 GetTransformMatrix() const { return m_Transform.GetMatrix(); }
    inline void SetSpriteCoodrdinate(int x, int y) { m_SpriteColumn = x; m_SpriteRow = y; }
};

#endif //GAME_ELEMENT_H
