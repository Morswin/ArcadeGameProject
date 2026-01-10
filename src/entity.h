#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>
#include "game_element.h"
#include <vector>

class Entity : virtual public GameElement
{
protected:
    // glm::vec2 m_predkosc;
    // std::vector<glm::vec2> m_sily;
    // bool m_kolizjaKolo;
    // bool m_kolizjaKwadrat;
    // double m_kolizjaKoloŚrenica;
    // double m_kolizjaKwadratBok;
public:
    // void kolizja(Entity& innyEntity);
};

#endif //ENTITY_H
