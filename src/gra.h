#ifndef ARCADEGAMEPROJECT_GRA_H
#define ARCADEGAMEPROJECT_GRA_H

#include <vector>
#include "mapa.h"
#include "byt.h"
#include "gracz.h"
#include "ustawienia.h"

class Gra
{
private:
    Mapa m_mapa;
    std::vector<Byt> m_byty;
    Gracz m_gracz;
    Ustawienia& m_ustawienia;
public:
    void symulujWszystkieByty();
    void wyswietlWszystkieByty();
    void wyswietlMape();
    void obslozInputGracza();  // Nie wiem czy to właściwy sposób na podpięcie tego do SDL3
};

#endif //ARCADEGAMEPROJECT_GRA_H
