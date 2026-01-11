#include "game_element.h"

void GameElement::Display(const Renderer& renderer) const {
    if (!m_Visible || !m_Mesh) return;
    m_Mesh->shader->Bind();
    m_Mesh->shader->SetUniform1mat4("u_Model", m_Transform.matrix());
    renderer.Draw(*m_Mesh->vao, *m_Mesh->ebo, *m_Mesh->shader);
}

void GameElement::SetPosition(glm::vec2 position) {
    m_Transform.position = position;
}

void GameElement::SetRotation(float rotation) {
    m_Transform.rotation = rotation;
}

void GameElement::SetScale(glm::vec2 scale) {
    m_Transform.scale = scale;
}

void GameElement::SetMesh(RenderMesh* mesh) {
    m_Mesh = mesh;
}

