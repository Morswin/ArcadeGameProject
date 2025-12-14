#ifndef ARCADEGAMEPROJECT_ELEMENT_GRY_H
#define ARCADEGAMEPROJECT_ELEMENT_GRY_H

#include "wektor_2d.h"

class ElementGry
{
protected:
    Wektor2D m_pozycja;
    Wektor2D m_rozmiar;  // Rozmiar w kontekście wyświetlania na ekranie, nie kontekście kolizji
    // Tekstura  // Do dodania po lepszym opanowaniu openGL
public:
    virtual ~ElementGry();
    virtual void symuluj() = 0;
    virtual void wyswietl() = 0;
};

#endif //ARCADEGAMEPROJECT_ELEMENT_GRY_H