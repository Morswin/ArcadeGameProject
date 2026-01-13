#ifndef GAME_H
#define GAME_H

#include <string>
#include <map>
#include <SDL3/SDL.h>
#include "renderer/renderer.hpp"
#include "renderer/render_mesh.hpp"
#include "player.hpp"

class Game
{
private:
    // Mapa m_mapa;
    // Ustawienia& m_ustawienia;
    SDL_Window* m_Window = nullptr;
    SDL_GLContext m_glContext;
    Player* m_Player = nullptr;
    std::map<std::string, RenderMesh*> m_RenderMeshes;
public:
    Game();
    ~Game();

    void Draw(Renderer* renderer);
    void Simulate(float deltaTime);
    void SwapWindow() const;
    void SetWindowTitle(std::string& name) const;

    inline void SetPlayerInput(glm::vec2 input) { m_Player->SetMovementInputForce(input); }
};

#endif //GAME_H
