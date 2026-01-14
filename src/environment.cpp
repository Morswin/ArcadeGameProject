#include "environment.hpp"

Environment::Environment(int spriteColumn, int spriteRow)
    : GameElement(spriteColumn, spriteRow)
{}

Environment::Environment(int spriteColumn, int spriteRow, RenderMesh* renderMesh)
    : GameElement(spriteColumn, spriteRow)
{
    m_Mesh = renderMesh;
}

Environment::~Environment() noexcept {
}

void Environment::Simulate(float deltaTime) {
}

