#include "game.hpp"

#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include "sdl_error.hpp"
#include "floor.hpp"
#include "wall.hpp"

Game::Game() : m_Player(new Player(2, 1)) {
    SDL_SetAppMetadata("ArcadeGameProject", "0.1", "ArcadeGameProject");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::stringstream ss;
        ss << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
        throw sdl_error(ss.str());
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    m_Window = SDL_CreateWindow("Arcade Game Project", 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!m_Window) {
        std::stringstream ss;
        ss << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        throw sdl_error(ss.str());
    }

    m_glContext = SDL_GL_CreateContext(m_Window);
    if (!m_glContext) {
        std::stringstream ss;
        ss << "Failed to create GL context: " << SDL_GetError() << std::endl;
        SDL_Quit();
        throw sdl_error(ss.str());
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        SDL_Quit();
        throw sdl_error("Failed initialize GLAD");
    }

    SDL_GL_SetSwapInterval(1);  // VSync = 1, uncapped = 0, adaprive VSync = -1 (if supported)

    // TODO - move thing below together with meshes to a separate place, prefereably something like hash_map
    /* Data for player VBO */
    float vertices[] = {
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };

    /* Data for player EBO */
    unsigned int elements[] = {
        0, 1, 2,
        1, 0, 3
    };

    // Initializing Render Meshes
    m_RenderMeshes["food"] = new RenderMesh(vertices, 20, elements, 6, "resources/food.png", 8, 8);
    m_RenderMeshes["characters"] = new RenderMesh(vertices, 20, elements, 6, "resources/characters.png", 5, 2);
    m_RenderMeshes["dungeon"] = new RenderMesh(vertices, 20, elements, 6, "resources/dungeon.png", 4, 4);
    m_RenderMeshes["dungeon_autotile"] = new RenderMesh(vertices, 20, elements, 6, "resources/dungeon_autotile.png", 3, 4);

    // Initializing Player
    m_Player->SetMesh(m_RenderMeshes.at("characters"));

    // Initializing Map
    m_Map = new Map();
    m_Map->RegisterNewEnvironment(0, Floor(1, 3, m_RenderMeshes["dungeon"]));
    m_Map->RegisterNewEnvironment(1, Floor(3, 3, m_RenderMeshes["dungeon"]));
    m_Map->RegisterNewEnvironment(10, Wall(0, 3, m_RenderMeshes["dungeon_autotile"]));

    if (m_Map->ShouldPlayerRelocate()) {
        m_Player->GetTransform().SetPosition(m_Map->GetPlayerStartLocation());
    }

    m_Enemies.clear();
    m_Enemies = m_Map->PopulateMapWithEnemies(0.2, m_RenderMeshes.at("characters"));
    std::cout << "Before: " << m_Enemies.size() << std::endl;
    std::erase_if(m_Enemies, [&](const Enemy& _enemy) {
        const float _difference = glm::distance(_enemy.GetTransform().GetPosition(), m_Player->GetTransform().GetPosition());
        const double _erasureRange = _enemy.GetDetectionRange() * 1.5;
        // std::cout << (_difference < _erasureRange) << "\t" << _difference << "\t" << _erasureRange << std::endl;
        return _difference < _erasureRange;
    });
    std::cout << "After: " << m_Enemies.size() << std::endl;
}

Game::~Game() {
    delete m_RenderMeshes["food"];
    delete m_RenderMeshes["characters"];
    delete m_RenderMeshes["dungeon"];
    delete m_RenderMeshes["dungeon_autotile"];
    delete m_Player;
    delete m_Map;
    SDL_GL_DestroyContext(m_glContext);
}

void Game::Draw(Renderer* renderer) {
    // Floors and Walls
    m_Map->DisplayFloorAndWall(*m_Player, *renderer);
    // Loot
    // Enemies
    for (const Enemy& _enemy : m_Enemies) {
        _enemy.Display(*renderer, m_Player->GetViewMatrix());
    }
    // Player
    m_Player->Display(*renderer, m_Player->GetViewMatrix());
    // Decorations
}

void Game::Simulate(float deltaTime) {
    if (m_Map->ShouldPlayerRelocate()) {
        m_Player->GetTransform().SetPosition(m_Map->GetPlayerStartLocation());
    }
    m_Player->Simulate(deltaTime);
}

void Game::SwapWindow() const {
    SDL_GL_SwapWindow(m_Window);
}

void Game::SetWindowTitle(std::string& name) const {
    SDL_SetWindowTitle(m_Window, name.c_str());
}
