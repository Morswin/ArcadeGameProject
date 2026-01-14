#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "game_element.hpp"

class Environment : virtual public GameElement
{
private:
public:
    Environment(int spriteColumn, int spriteRow);
    Environment(int spriteColumn, int spriteRow, RenderMesh* renderMesh);
    ~Environment() noexcept;

    void Simulate(float deltaTime);
};

#endif //ENVIRONMENT_H
