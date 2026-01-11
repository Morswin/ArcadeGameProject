#ifndef MAP_H
#define MAP_H

#include <map>
#include <glm/glm.hpp>
#include "environment.hpp"
#include "player.hpp"

class Map
{
private:
    std::map<glm::vec2, unsigned int> m_aktualnePolaMapy;
    std::map<unsigned int, Environment> m_spisElementowOtoczenia;
public:
    void wyswietlMape(Player& player);
};

#endif //MAP_H
