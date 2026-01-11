#ifndef ARCADEGAMEPROJECT_POCISK_DEKORATOR_H
#define ARCADEGAMEPROJECT_POCISK_DEKORATOR_H

#include "pocisk.hpp"

class PociskDekorator : public Pocisk
{
private:
    Pocisk& m_pocisk;
public:
    void podazajTrajektoria();
};

#endif //ARCADEGAMEPROJECT_POCISK_DEKORATOR_H
