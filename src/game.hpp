#ifndef ARCADEGAMEPROJECT_GRA_H
#define ARCADEGAMEPROJECT_GRA_H

// #include <vector>
#include <string>
#include <SDL3/SDL.h>
// #include "mapa.h"
// #include "ustawienia.h"
#include "renderer/renderer.hpp"
#include "renderer/render_mesh.hpp"
#include "player.hpp"

class Game
{
private:
    // Mapa m_mapa;
    // std::vector<Byt> m_byty;
    // Gracz m_gracz;
    // Ustawienia& m_ustawienia;
    SDL_Window* m_Window = nullptr;
    SDL_GLContext m_glContext;
    RenderMesh* m_PlayerMesh = nullptr;
    Player* m_Player = nullptr;
public:
    Game();
    ~Game();

    void Draw(Renderer* renderer);
    void Simulate(float deltaTime);
    void SwapWindow() const;
    void SetWindowTitle(std::string& name) const;

    inline void SetPlayerInput(glm::vec2 input) { m_Player->SetMovementInputForce(input); }
};

#endif //ARCADEGAMEPROJECT_GRA_H
