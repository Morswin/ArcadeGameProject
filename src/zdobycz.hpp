#ifndef ARCADEGAMEPROJECT_ZDOBYCZ_H
#define ARCADEGAMEPROJECT_ZDOBYCZ_H

#include "byt.hpp"

class Zdobycz : public Byt
{
private:
    double m_opoznienie;
public:
    void zdobadzSie();
    void losujOpoznienie();
};

#endif //ARCADEGAMEPROJECT_ZDOBYCZ_H
