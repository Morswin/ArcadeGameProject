#include <string>
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "utils/sdl_error.hpp"
#include "game.hpp"

static Game* game = nullptr;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    try {
        game = new Game();
    }
    catch (sdl_error e) {
        std::cerr << e.what() << std::endl;
        return SDL_APP_FAILURE;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    return game->HandleEvent(event);
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    game->StartFrameTracking();
    game->Simulate();
    game->Draw();
    game->SwapWindow();
    game->FinishFrameTracking();
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    delete game;
}
