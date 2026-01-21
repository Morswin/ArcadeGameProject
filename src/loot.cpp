#include "loot.hpp"

#include <glm/glm.hpp>
#include "utils/rng.hpp"

Loot::Loot(RenderMesh* render_mesh)
    : Loot(render_mesh, RNG::GetRNG().GetNextInt(0, 7), RNG::GetRNG().GetNextInt(0, 7))
{}

Loot::Loot(RenderMesh* render_mesh, int spriteColumn, int spriteRow)
    : GameElement(spriteColumn, spriteRow), Entity(spriteColumn, spriteRow)
{
    SetMesh(render_mesh);
    GetTransform().SetScale(glm::vec2(0.5f));
}

Loot::~Loot() noexcept {
}

