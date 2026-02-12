#include "game.hpp"

#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include "utils/sdl_error.hpp"
#include "utils/rng.hpp"
#include "floor.hpp"
#include "wall.hpp"
#include "settings.hpp"

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

    GLCall(glViewport(0, 0, 800, 600));

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // Background color
    GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));

    m_Renderer = new Renderer();

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
    m_RenderMeshes["projectile"] = new RenderMesh(vertices, 20, elements, 6, "resources/projectile.png", 1, 1);

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

    PopulateMapWithEnemies();

    // Test - setting up ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& imgui_io = ImGui::GetIO();
    imgui_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    imgui_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui_ImplSDL3_InitForOpenGL(m_Window, m_glContext);
    ImGui_ImplOpenGL3_Init();
}

Game::~Game() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    delete m_RenderMeshes["food"];
    delete m_RenderMeshes["characters"];
    delete m_RenderMeshes["dungeon"];
    delete m_RenderMeshes["dungeon_autotile"];
    delete m_Player;
    delete m_Map;
    delete m_Renderer;
    SDL_GL_DestroyContext(m_glContext);
}

void Game::Draw() {
    m_Renderer->Clear();

    // Floors and Walls
    m_Map->DisplayFloorAndWall(*m_Player, *m_Renderer);
    // Loot
    for (const Loot& _loot : m_Loot) {
        _loot.Display(*m_Renderer, m_Player->GetViewMatrix());
    }
    // Enemies
    for (const Enemy& _enemy : m_Enemies) {
        _enemy.Display(*m_Renderer, m_Player->GetViewMatrix());
    }
    // Player
    m_Player->Display(*m_Renderer, m_Player->GetViewMatrix());
    // Projectiles
    for (const Projectile& _projectile : m_Projectiles) {
        _projectile.Display(*m_Renderer, m_Player->GetViewMatrix());
    }

    // Displaying ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Game::Simulate() {
    // Imgui Test
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow();

    if (m_Player->IsAlive() && !m_Enemies.empty()) {
        m_MovementInput.UpdateMovement();
        SetPlayerInput();

        // Enemies
        for (const Enemy& _enemy : m_Enemies) {
            if (!_enemy.IsAlive() && RNG::GetRNG().GetNextInt(0, 10) <= 4) {
                Loot _loot(m_RenderMeshes["food"]);
                _loot.GetTransform().SetPosition(_enemy.GetTransform().GetPosition());
                m_Loot.push_back(_loot);
            }
        }
        std::erase_if(m_Enemies, [](const Enemy& _enemy) {
            return !_enemy.IsAlive();
        });
        for (Enemy& _enemy : m_Enemies) {
            _enemy.Simulate(m_DeltaTime, m_Map->GetMapData(), *m_Player);
            if (_enemy.Overlaps(*m_Player)) {
                m_Player->DamagePlayer(m_DeltaTime, _enemy.GetContactDamagePerSecond());
            }
        }
        // Player
        if (m_Map->ShouldPlayerRelocate()) {
            m_Player->GetTransform().SetPosition(m_Map->GetPlayerStartLocation());
        }
        m_Player->Simulate(m_DeltaTime, m_Map->GetMapData());
        // Loot
        std::erase_if(m_Loot, [&](Loot& _loot) {
            if (_loot.Overlaps(*m_Player)) {
                m_Player->HealByAmount(_loot.GetRestoredHealth());
                return true;
            }
            return false;
        });
        // Here Loot can be simulated if such need would arise.
        // Projectiles
        if (m_Player->IsReadyToFire() && !m_Enemies.empty() && IsEnemyInPlayerRange()) {
            Projectile _projectile(0, 0);
            _projectile.SetMesh(m_RenderMeshes["projectile"]);
            _projectile.GetTransform().SetPosition(m_Player->GetTransform().GetPosition());
            _projectile.GetTransform().SetScale(glm::vec2(0.2f));
            const glm::vec2 projectilePos = _projectile.GetTransform().GetPosition();
            Enemy* closestEnemy = nullptr;
            float closestDistSq = std::numeric_limits<float>::max();
            for (Enemy& enemy : m_Enemies) {
                const glm::vec2 enemyPos = enemy.GetTransform().GetPosition();
                const glm::vec2 diff = enemyPos - projectilePos;
                const float distSq = glm::dot(diff, diff);
                if (distSq < closestDistSq) {
                    closestDistSq = distSq;
                    closestEnemy = &enemy;
                }
            }
            if (closestEnemy) {
                glm::vec2 direction = glm::normalize(closestEnemy->GetTransform().GetPosition() - projectilePos);
                const float projectileSpeed = 3.0f;
                _projectile.SetVelocity(direction * projectileSpeed);
                _projectile.AddForce(direction * (projectileSpeed * 0.1f));
            }
            m_Projectiles.push_back(_projectile);
            m_Player->ResetFireReadiness();
        }
        for (Projectile& _projectile : m_Projectiles) {
            _projectile.Simulate(m_DeltaTime, m_Map->GetMapData());
        }
        for (Projectile& _projectile : m_Projectiles) {
            for (Enemy& _enemy : m_Enemies) {
                if (!_enemy.IsAlive()) continue;
                if (_projectile.Overlaps(_enemy)) {
                    _enemy.TakeDamage(_projectile.GetDamage());
                    _projectile.OnHitEnemy();
                    break;
                }
            }
        }
        std::erase_if(m_Projectiles, [](const Projectile& _projectile) {
            return _projectile.ReadyForDeletion();
        });
    }
    // Here I can distinguish various reasons why the level should be regenerated
    else {
        // This is a good place to show some Game Over UI, once it's'
        // Or something regarding wenturing to the next level if all enemies have been killed
        m_Loot.clear();
        m_Projectiles.clear();
        m_Map->GenerateNewMap();
        m_Player->GetTransform().SetPosition(m_Map->GetPlayerStartLocation());
        PopulateMapWithEnemies();
        m_Player->HealCompletely();
    }
}

SDL_AppResult Game::HandleEvent(SDL_Event* event) {
    // Let ImGui process events
    ImGui_ImplSDL3_ProcessEvent(event);

    // My event handling
    switch (event->type) {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
        break;
    case SDL_EVENT_WINDOW_RESIZED:
        GLCall(glViewport(0, 0, event->window.data1, event->window.data2));
        break;
    case SDL_EVENT_KEY_DOWN:
        switch (event->key.key) {
        case SDLK_W:
            m_MovementInput.up = true;
            break;
        case SDLK_A:
            m_MovementInput.left = true;
            break;
        case SDLK_S:
            m_MovementInput.down = true;
            break;
        case SDLK_D:
            m_MovementInput.right = true;
            break;
        case SDLK_PAGEUP:
            Settings::GetSettings().ZoomOut();
            break;
        case SDLK_PAGEDOWN:
            Settings::GetSettings().ZoomIn();
            break;
        }
        break;
    case SDL_EVENT_KEY_UP:
        switch (event->key.key) {
        case SDLK_W:
            m_MovementInput.up = false;
            break;
        case SDLK_A:
            m_MovementInput.left = false;
            break;
        case SDLK_S:
            m_MovementInput.down = false;
            break;
        case SDLK_D:
            m_MovementInput.right = false;
            break;
        }
        break;
    }
    // For now I don't see a reason to handle the default.
    // I only want to handle specific events. Not all of them.
    return SDL_APP_CONTINUE;
}

void Game::PopulateMapWithEnemies() {
    m_Enemies.clear();
    m_Enemies = m_Map->PopulateMapWithEnemies(0.2, m_RenderMeshes.at("characters"));
    std::erase_if(m_Enemies, [&](const Enemy& _enemy) {
        const float _difference = glm::distance(_enemy.GetTransform().GetPosition(), m_Player->GetTransform().GetPosition());
        const double _erasureRange = _enemy.GetDetectionRange() * 1.5;
        return _difference < _erasureRange;
    });
}

void Game::SwapWindow() const {
    SDL_GL_SwapWindow(m_Window);
}

void Game::FinishFrameTracking() {
    m_FPS++;
    m_DeltaTime = (SDL_GetTicks() - m_DeltaTimeMeasureStart) / 1000.0f;
    if (m_DeltaTimeMeasureStart > m_DeltaTimeMeasurePrevious + 1000) {
        m_DeltaTimeMeasurePrevious = m_DeltaTimeMeasureStart;
        SetWindowTitle();
        m_FPS = 0;
    }
}

void Game::SetWindowTitle() const {
    std::stringstream title;
    title << "FPS: " << m_FPS << " Player health: " << m_Player->GetHealth() << "%";
    SDL_SetWindowTitle(m_Window, title.str().c_str());
}

bool Game::IsEnemyInPlayerRange() {
    const float _rangeSq = std::pow(m_Player->GetRange(), 2);
    for (const Enemy& _enemy : m_Enemies) {
        if (!_enemy.IsAlive()) continue;
        const glm::vec2 _delta = _enemy.GetTransform().GetPosition() - m_Player->GetTransform().GetPosition();
        if (glm::dot(_delta, _delta) <= _rangeSq) {
            return true;
        }
    }
    return false;
}

