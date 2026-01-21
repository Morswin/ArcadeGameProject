#ifndef GAME_H
#define GAME_H

#include <string>
#include <map>
#include <vector>
#include <SDL3/SDL.h>
#include "renderer/renderer.hpp"
#include "renderer/render_mesh.hpp"
#include "player.hpp"
#include "map.hpp"
#include "enemy.hpp"
#include "projectile.hpp"

class Game
{
private:
    SDL_Window* m_Window = nullptr;
    SDL_GLContext m_glContext;
    Player* m_Player = nullptr;
    std::map<std::string, RenderMesh*> m_RenderMeshes;
    Map* m_Map = nullptr;
    std::vector<Enemy> m_Enemies{};
    std::vector<Projectile> m_Projectiles{};
public:
    Game();
    ~Game();

    void Draw(Renderer* renderer);
    void Simulate(float deltaTime);
    void SwapWindow() const;
    void SetWindowTitle(std::string& name) const;
    void PopulateMapWithEnemies();

    inline void SetPlayerInput(glm::vec2 input) { m_Player->SetMovementInputForce(input); }
private:
    bool IsEnemyInPlayerRange();
};

#endif //GAME_H
