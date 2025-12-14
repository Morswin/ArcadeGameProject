#ifndef ARCADEGAMEPROJECT_BYT_H
#define ARCADEGAMEPROJECT_BYT_H

#include "element_gry.h"
#include "wektor_2d.h"
#include <vector>

class Byt : virtual public ElementGry
{
protected:
    Wektor2D m_predkosc;
    std::vector<Wektor2D> m_sily;
    bool m_kolizjaKolo;
    bool m_kolizjaKwadrat;
    double m_kolizjaKoloŚrenica;
    double m_kolizjaKwadratBok;
public:
    void kolizja(Byt& innyByt);
};

#endif //ARCADEGAMEPROJECT_BYT_H