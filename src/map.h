#ifndef MAP_H
#define MAP_H

#include <map>
#include <glm/glm.hpp>
#include "environment.h"
#include "player.h"

class Map
{
private:
    std::map<glm::vec2, unsigned int> m_aktualnePolaMapy;
    std::map<unsigned int, Environment> m_spisElementowOtoczenia;
public:
    void wyswietlMape(Player& player);
};

#endif //MAP_H
