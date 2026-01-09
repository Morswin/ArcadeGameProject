#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glad/glad.h>
#include <string>
#include <iostream>
#include "renderer/renderer_utils.h"
#include "renderer/renderer.h"
#include "renderer/vertex_buffer.h"
#include "renderer/element_buffer.h"
#include "renderer/vertex_array.h"
#include "renderer/shader.h"
#include "renderer/texture.h"
#include "sdl_error.h"
#include "game.h"
#include "glm/glm.hpp"

struct MovementInput {
    bool right = false;
    bool left = false;
    bool up = false;
    bool down = false;
    glm::vec2 movement{0.0f, 0.0f};

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

        movement = glm::normalize(glm::vec2{x, y});
    }
};

// TODO - This needs to get moved/abstracted into a separate thing. Maybe game.h would do? Or something else.
static Game* game = nullptr;
static VertexBuffer* vb = nullptr;
static ElementBuffer* eb = nullptr;
static VertexArray* va = nullptr;
static Shader* shader = nullptr;
static Renderer* renderer = nullptr;
static Texture* texture = nullptr;
static MovementInput movement_input;
static unsigned int fps = 0;
static unsigned int lastDeltaTime = 0;


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
         0.5f,  0.5f, 0.0f, 0.125f, 0.125f,
        -0.5f, -0.5f, 0.0f, 0.0f,   0.0f,
         0.5f, -0.5f, 0.0f, 0.125f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.0f,   0.125f
    };

    /* Data for EBO */
    unsigned int elements[] = {
        0, 1, 2,
        1, 0, 3
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    va = new VertexArray();
    vb = new VertexBuffer(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    va->AddBuffer(*vb, layout);
    eb = new ElementBuffer(elements, 6);

    shader = new Shader("shaders/basic.glsl");
    shader->Bind();

    std::string basePath = SDL_GetBasePath();
    std::string texPath = basePath + "resources/food.png";
    texture = new Texture(texPath);
    // texture = new Texture("resources/food.png");
    texture->Bind();
    shader->SetUniform1i("u_Texture", 0);

    va->Unbind();
    vb->Unbind();
    eb->Unbind();
    shader->Unbind();

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
    // SDL_Log("Movement: (%.2f, %.2f)", movement_input.movement.x, movement_input.movement.y);
    // IT WORKS :)

    renderer->Clear();
    renderer->Draw(*va, *eb, *shader);

    game->SwapWindow();

    fps++;
    unsigned int deltaTime = SDL_GetTicks() - tickStartTime;
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
    delete eb;
    delete vb;
    delete va;
    delete shader;
    delete renderer;
    delete texture;
    delete game;
}
