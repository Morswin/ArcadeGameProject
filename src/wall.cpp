#include "wall.hpp"

Wall::Wall(int spriteColumn, int spriteRow)
    : GameElement(spriteColumn, spriteRow), Entity(spriteColumn, spriteRow), Environment(spriteColumn, spriteRow)
{}

Wall::Wall(int spriteColumn, int spriteRow, RenderMesh* rendererMesh)
    : GameElement(spriteColumn, spriteRow), Entity(spriteColumn, spriteRow), Environment(spriteColumn, spriteRow, rendererMesh)
{}

Wall::~Wall() noexcept {
}

void Wall::Simulate(float deltaTime) {
}

