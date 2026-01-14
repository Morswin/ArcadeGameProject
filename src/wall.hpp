#ifndef WALL_H
#define WALL_H

#include "environment.hpp"
#include "entity.hpp"

class Wall : public Entity, public Environment
{
private:
public:
    Wall(int spriteColumn, int spriteRow);
    Wall(int spriteColumn, int spriteRow, RenderMesh* rendererMesh);
    ~Wall() noexcept;

    void Simulate(float deltaTime);
};

#endif //WALL_H
