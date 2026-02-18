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
#include "loot.hpp"
#include "ui/ui_manager.hpp"

struct MovementInput
{
    bool right, left, up, down;
    glm::vec2 movement;

    MovementInput() : right(false), left(false), up(false), down(false), movement(glm::vec2{0.0f, 0.0f}) {}

    void UpdateMovement()
    {
        float x = 0.0f;
        float y = 0.0f;

        if (right && !left)
        {
            x = 1.0f;
        }
        else if (!right && left)
        {
            x = -1.0f;
        }

        if (up && !down)
        {
            y = 1.0f;
        }
        else if (!up && down)
        {
            y = -1.0f;
        }

        // I believe that this if statement should fix the issue with accidentally making a vec2 of Nan values. Mostlikely it was a way not to divide by zero, but I am not sure. After all, there is no need for notmalizing a vector of 0.0f length, right?
        if (!(x == 0.0f && y ==0.0f))
        {
            movement = glm::normalize(glm::vec2{x, y});
        }
        else
        {
            movement = glm::vec2{x, y};
        }
    }
};

class Game
{
private:
    SDL_Window* m_Window = nullptr;
    SDL_GLContext m_glContext;
    Renderer* m_Renderer = nullptr;
    Player* m_Player = nullptr;
    std::map<std::string, RenderMesh*> m_RenderMeshes;
    Map* m_Map = nullptr;
    std::vector<Enemy> m_Enemies{};
    std::vector<Projectile> m_Projectiles{};
    std::vector<Loot> m_Loot{};
    MovementInput m_MovementInput;
    unsigned int m_DeltaTimeMeasureStart{0};
    unsigned int m_DeltaTimeMeasurePrevious{0};
    unsigned int m_FPS{0};
    float m_DeltaTime{0.0f};
    UIManager m_UIManager;
public:
    Game();
    ~Game();

    void Draw();
    void Simulate();
    SDL_AppResult HandleEvent(SDL_Event* event);
    void FinishFrameTracking();

    inline void SetPlayerInput() { m_Player->SetMovementInputForce(m_MovementInput.movement); }
    inline void StartFrameTracking() { m_DeltaTimeMeasureStart = SDL_GetTicks(); }
private:
    void PopulateMapWithEnemies();
    bool IsEnemyInPlayerRange();
};

#endif //GAME_H
