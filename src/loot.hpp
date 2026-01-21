#ifndef LOOT_H
#define LOOT_H

#include "renderer/render_mesh.hpp"
#include "entity.hpp"

class Loot : public Entity
{
private:
    double m_RestoresHealth{10.0};
public:
    Loot(RenderMesh* render_mesh);
    ~Loot() noexcept;

    inline double GetRestoredHealth() const { return m_RestoresHealth; }
private:
    Loot(RenderMesh* render_mesh, int spriteColumn, int spriteRow);
};

#endif //LOOT_H
