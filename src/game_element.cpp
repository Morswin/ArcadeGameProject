#include "game_element.hpp"

#include "settings.hpp"

GameElement::GameElement(int spriteColumn, int spriteRow)
    : m_SpriteColumn(spriteColumn), m_SpriteRow(spriteRow)
{}

void GameElement::Display(const Renderer& renderer, glm::mat4 u_ViewMatrix) const {
    if (!m_Visible || !m_Mesh) return;
    m_Mesh->GetShader()->Bind();
    m_Mesh->GetShader()->SetUniform1mat4("u_Model", m_Transform.GetMatrix());
    m_Mesh->GetShader()->SetUniform1mat4("u_View", u_ViewMatrix);
    glm::mat4 projection;
    switch(Settings::GetSettings().GetCurrentZoom()) {
    case ZoomLevel::Close:
        projection = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, -1.0f, 1.0f);
        break;
    case ZoomLevel::Neutral:
    default:
        projection = glm::ortho(-6.0f, 6.0f, -4.5f, 4.5f, -1.0f, 1.0f);
        break;
    case ZoomLevel::Far:
        projection = glm::ortho(-10.0f, 10.0f, -7.5f, 7.5f, -1.0f, 1.0f);
        break;
    }
    m_Mesh->GetShader()->SetUniform1mat4("u_Projection", projection);
    m_Mesh->GetTexture()->Bind();
    m_Mesh->SetSpriteCoodrdinate(m_SpriteColumn, m_SpriteRow);
    renderer.Draw(*m_Mesh->GetVAO(), *m_Mesh->GetEBO(), *m_Mesh->GetShader());
}

void GameElement::SetMesh(RenderMesh* mesh) {
    m_Mesh = mesh;
}

