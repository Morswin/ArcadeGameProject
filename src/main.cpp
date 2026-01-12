#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glad/glad.h>
#include <string>
#include <iostream>
#include "glm/glm.hpp"
#include "renderer/renderer_utils.hpp"
#include "renderer/renderer.hpp"
#include "renderer/render_mesh.hpp"
#include "sdl_error.hpp"
#include "game.hpp"
#include "transform2d.hpp"
#include "player.hpp"

struct MovementInput {
    bool right, left, up, down;
    glm::vec2 movement;

    MovementInput() : right(false), left(false), up(false), down(false), movement(glm::vec2{0.0f, 0.0f}) {}

    void UpdateMovement() {
        float x = 0.0f;
        float y = 0.0f;

        if (right && !left) {
            x = 1.0f;
        }
        else if (!right && left) {
            x = -1.0f;
        }

        if (up && !down) {
            y = 1.0f;
        }
        else if (!up && down) {
            y = -1.0f;
        }

        // I believe that this if statement should fix the issue with accidentally making a vec2 of Nan values. Mostlikely it was a way not to divide by zero, but I am not sure. After all, there is no need for notmalizing a vector of 0.0f length, right?
        if (!(x == 0.0f && y ==0.0f)) {
            movement = glm::normalize(glm::vec2{x, y});
        }
        else {
            movement = glm::vec2{x, y};
        }
    }
};

// TODO - This needs to get moved/abstracted into a separate thing. Maybe game.h would do? Or something else.
static Game* game = nullptr;
static Renderer* renderer = nullptr;
static MovementInput movement_input;
static Player* player = nullptr;
static RenderMesh* render_mesh = nullptr;
static unsigned int fps = 0;
static unsigned int lastDeltaTime = 0;
static float deltaTime = 0.0f;


SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    try {
        game = new Game();
    }
    catch (sdl_error e) {
        std::cerr << e.what() << std::endl;
        return SDL_APP_FAILURE;
    }

    GLCall(glViewport(0, 0, 800, 600));

    /* Data for VBO */
    float vertices[] = {
         0.5f,  0.5f, 0.0f, 0.125f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f,   0.875f,
         0.5f, -0.5f, 0.0f, 0.125f, 0.875f,
        -0.5f,  0.5f, 0.0f, 0.0f,   1.0f
    };

    /* Data for EBO */
    unsigned int elements[] = {
        0, 1, 2,
        1, 0, 3
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    render_mesh = new RenderMesh(vertices, 20, elements, 6, "resources/food.png");
    player = new Player();
    player->SetMesh(render_mesh);
    // game_element = new GameElement();
    // game_element->SetMesh(render_mesh);

    // Background color
    GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));

    renderer = new Renderer();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
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
            movement_input.up = true;
            break;
        case SDLK_A:
            movement_input.left = true;
            break;
        case SDLK_S:
            movement_input.down = true;
            break;
        case SDLK_D:
            movement_input.right = true;
            break;
        }
        break;
    case SDL_EVENT_KEY_UP:
        switch (event->key.key) {
        case SDLK_W:
            movement_input.up = false;
            break;
        case SDLK_A:
            movement_input.left = false;
            break;
        case SDLK_S:
            movement_input.down = false;
            break;
        case SDLK_D:
            movement_input.right = false;
            break;
        }
        break;
    }
    // For now I don't see a reason to handle the default.
    // I only want to handle specific events. Not all of them.
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    unsigned int tickStartTime = SDL_GetTicks();

    movement_input.UpdateMovement();
    player->SetMovementInputForce(movement_input.movement);
    player->Simulate(deltaTime);

    renderer->Clear();
    // renderer->Draw(*render_mesh->vao, *render_mesh->ebo, *render_mesh->shader);
    // game_element->Display(*renderer);
    player->Display(*renderer);

    game->SwapWindow();

    fps++;
    deltaTime = (SDL_GetTicks() - tickStartTime) / 1000.0f;
    // std::cout << player->GetVelocity().x << " " << player->GetVelocity().y << std::endl;
    if (tickStartTime > lastDeltaTime + 1000) {
        lastDeltaTime = tickStartTime;
        std::string title = "FPS: " + std::to_string(fps);
        game->SetWindowTitle(title);
        fps = 0;
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    delete render_mesh;
    delete renderer;
    delete game;
}
