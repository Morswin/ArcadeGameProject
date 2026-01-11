#ifndef PLAYER_H
#define PLAYER_H

#include "entity.hpp"

class Player : public Entity
{
private:
    // Wektor2D m_pozycjaKamery;
    // poziomPostaci  // Nie wiem czy tego inaczej nie rozwiążę
public:
    Player();
    ~Player();
    // void przyjmiejInputPlayera();  // Tutaj przyjąć z SDL3 inputy gracza albo jakoś tak
    // void zbierzZdobycz();  // Prawdopodobnie wzorzec Obserwator z Zdobyczami, żeby te mogły trafnie reagować na gracza
};

#endif //PLAYER_H
