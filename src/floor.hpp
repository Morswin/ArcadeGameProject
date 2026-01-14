#ifndef FLOOR_H
#define FLOOR_H

#include "environment.hpp"

class Floor : public Environment
{
private:
public:
    Floor(int spriteColumn, int spriteRow);
    Floor(int spriteColumn, int spriteRow, RenderMesh* rendererMesh);
    ~Floor() noexcept;

    void Simulate(float deltaTime);
};

#endif //FLOOR_H
