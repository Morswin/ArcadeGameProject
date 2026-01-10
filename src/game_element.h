#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

#include "glm/glm.hpp"

class GameElement
{
protected:
    glm::vec2 position;
    // Tekstura  // Do dodania po lepszym opanowaniu openGL
public:
    virtual ~GameElement();
    virtual void simulate() = 0;
    virtual void display() = 0;
};

#endif //GAME_ELEMENT_H
