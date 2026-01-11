#ifndef ARCADEGAMEPROJECT_PRZECIWNIK_H
#define ARCADEGAMEPROJECT_PRZECIWNIK_H

#include "byt.hpp"
#include "strategia_przeciwnika.hpp"

class Przeciwnik : public Byt
{
private:
    StrategiaPrzeciwnika strategiaPrzeciwnika;
public:
    void blakajSie();
    void szukajGracza();
    void atakujGracza();
};

#endif //ARCADEGAMEPROJECT_PRZECIWNIK_H
