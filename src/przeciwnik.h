#ifndef ARCADEGAMEPROJECT_PRZECIWNIK_H
#define ARCADEGAMEPROJECT_PRZECIWNIK_H

#include "byt.h"
#include "strategia_przeciwnika.h"

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