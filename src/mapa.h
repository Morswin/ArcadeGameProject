#ifndef ARCADEGAMEPROJECT_MAPA_H
#define ARCADEGAMEPROJECT_MAPA_H

#include "otoczenie.h"
#include "gracz.h"
#include <map>

class Mapa
{
private:
    std::map<Wektor2D, unsigned int> m_aktualnePolaMapy;
    std::map<unsigned int, Otoczenie> m_spisElementowOtoczenia;
public:
    void wyswietlMape(Gracz& gracz);
};

#endif //ARCADEGAMEPROJECT_MAPA_H
