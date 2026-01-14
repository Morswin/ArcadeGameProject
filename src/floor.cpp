#include "floor.hpp"

Floor::Floor(int spriteColumn, int spriteRow)
    : GameElement(spriteColumn, spriteRow), Environment(spriteColumn, spriteRow)
{}

Floor::Floor(int spriteColumn, int spriteRow, RenderMesh* rendererMesh)
    : GameElement(spriteColumn, spriteRow), Environment(spriteColumn, spriteRow, rendererMesh)
{}

Floor::~Floor() noexcept {
}

void Floor::Simulate(float deltaTime) {
}
