#include "game.hpp"

#include <sstream>
#include <glad/glad.h>
#include "sdl_error.hpp"

Game::Game() : m_Player(new Player()) {
    SDL_SetAppMetadata("ArcadeGameProject", "0.1", "ArcadeGameProject");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::stringstream ss;
        ss << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
        // SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        // return SDL_APP_FAILURE;
        throw sdl_error(ss.str());
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    m_Window = SDL_CreateWindow("Arcade Game Project", 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!m_Window) {
        std::stringstream ss;
        ss << "Failed to create window: " << SDL_GetError() << std::endl;
        // SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        throw sdl_error(ss.str());
        // return SDL_APP_FAILURE;
    }

    m_glContext = SDL_GL_CreateContext(m_Window);
    if (!m_glContext) {
        std::stringstream ss;
        ss << "Failed to create GL context: " << SDL_GetError() << std::endl;
        // SDL_Log("Failed to create GL context: %s", SDL_GetError());
        SDL_Quit();
        // return SDL_APP_FAILURE;
        throw sdl_error(ss.str());
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        // SDL_Log("Failed initialize GLAD");
        SDL_Quit();
        // return SDL_APP_FAILURE;
        throw sdl_error("Failed initialize GLAD");
    }

    SDL_GL_SetSwapInterval(1);  // VSync = 1, uncapped = 0, adaprive VSync = -1 (if supported)

    // TODO - move thing below together with meshes to a separate place, prefereably something like hash_map
    /* Data for player VBO */
    float vertices[] = {
        0.5f,  0.5f, 0.0f, 0.125f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f,   0.875f,
        0.5f, -0.5f, 0.0f, 0.125f, 0.875f,
        -0.5f,  0.5f, 0.0f, 0.0f,   1.0f
    };

    /* Data for player EBO */
    unsigned int elements[] = {
        0, 1, 2,
        1, 0, 3
    };

    m_PlayerMesh = new RenderMesh(vertices, 20, elements, 6, "resources/food.png");
    m_Player->SetMesh(m_PlayerMesh);
}

Game::~Game() {
    SDL_GL_DestroyContext(m_glContext);
}

void Game::Draw(Renderer* renderer) {
    // Floor
    // Walls
    // Loot
    // Enemies
    // Player
    m_Player->Display(*renderer);
    // Decorations
}

void Game::Simulate(float deltaTime) {
    m_Player->Simulate(deltaTime);
}

void Game::SwapWindow() const {
    SDL_GL_SwapWindow(m_Window);
}

void Game::SetWindowTitle(std::string& name) const {
    SDL_SetWindowTitle(m_Window, name.c_str());
}
