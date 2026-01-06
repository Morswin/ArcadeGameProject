#ifndef ARCADEGAMEPROJECT_GRA_H
#define ARCADEGAMEPROJECT_GRA_H

// #include <vector>
#include <string>
#include <SDL3/SDL.h>
// #include "mapa.h"
// #include "byt.h"
// #include "gracz.h"
// #include "ustawienia.h"

class Game
{
private:
    // Mapa m_mapa;
    // std::vector<Byt> m_byty;
    // Gracz m_gracz;
    // Ustawienia& m_ustawienia;
    SDL_Window* m_Window = nullptr;
    SDL_GLContext m_glContext;
public:
    Game();
    ~Game();

    void SwapWindow();
    void SetWindowTitle(std::string& name);
    // void symulujWszystkieByty();
    // void wyswietlWszystkieByty();
    // void wyswietlMape();
    // void obslozInputGracza();  // Nie wiem czy to właściwy sposób na podpięcie tego do SDL3
};

#endif //ARCADEGAMEPROJECT_GRA_H
