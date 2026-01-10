#ifndef ARCADEGAMEPROJECT_GRACZ_H
#define ARCADEGAMEPROJECT_GRACZ_H

#include "byt.h"

class Gracz : public Byt
{
private:
    Wektor2D m_pozycjaKamery;
    // poziomPostaci  // Nie wiem czy tego inaczej nie rozwiążę
public:
    Gracz();
    ~Gracz();
    void przyjmiejInputGracza();  // Tutaj przyjąć z SDL3 inputy gracza albo jakoś tak
    void zbierzZdobycz();  // Prawdopodobnie wzorzec Obserwator z Zdobyczami, żeby te mogły trafnie reagować na gracza
};

#endif //ARCADEGAMEPROJECT_GRACZ_H
