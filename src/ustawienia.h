#ifndef ARCADEGAMEPROJECT_USTAWIENIA_H
#define ARCADEGAMEPROJECT_USTAWIENIA_H

#include "wektor_2d.h"

class Ustawienia
{
protected:
    MySingleton();
    ~MySingleton();
public:
    Wektor2D m_rozmiarOkna;  // TODO Ustawić na coś sensownego jak tylko konstruktor będzie kompletny
    bool m_resizeable{false};
    unsigned int m_FPS{60};
    static Ustawienia& pobierzUstawienia();
    MySingleton(const MySingleton&) = delete;
    MySingleton& operator=(const MySingleton&) = delete;
};

#endif //ARCADEGAMEPROJECT_USTAWIENIA_H