#ifndef ARCADEGAMEPROJECT_BYT_H
#define ARCADEGAMEPROJECT_BYT_H

#include <glm/glm.hpp>
#include "element_gry.h"
#include <vector>

class Byt : virtual public ElementGry
{
protected:
    glm::vec2 m_predkosc;
    std::vector<glm::vec2> m_sily;
    bool m_kolizjaKolo;
    bool m_kolizjaKwadrat;
    double m_kolizjaKoloŚrenica;
    double m_kolizjaKwadratBok;
public:
    void kolizja(Byt& innyByt);
};

#endif //ARCADEGAMEPROJECT_BYT_H
