#include "game_element.hpp"

void GameElement::Display(const Renderer& renderer) const {
    if (!m_Visible || !m_Mesh) return;
    m_Mesh->GetShader()->Bind();
    m_Mesh->GetShader()->SetUniform1mat4("u_Model", m_Transform.GetMatrix());
    m_Mesh->GetTexture()->Bind();
    renderer.Draw(*m_Mesh->GetVAO(), *m_Mesh->GetEBO(), *m_Mesh->GetShader());
}

void GameElement::SetMesh(RenderMesh* mesh) {
    m_Mesh = mesh;
}

