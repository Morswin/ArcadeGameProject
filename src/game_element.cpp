#include "game_element.h"

void GameElement::Display(const Renderer& renderer) const {
    if (!m_Visible || !m_Mesh) return;
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

