#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "core/Game.h"

static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;

struct AppState {
    Game *game{};
    Uint64 last_time{};
    InputState input;
} ;


SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    // TODO init in Game::init
    if (!SDL_CreateWindowAndRenderer("Hello World", 800, 600, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    auto *state = new AppState();
    state->game = new Game(renderer);
    state->last_time = SDL_GetPerformanceCounter();
    *appstate = state;

    state->game->init();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    auto *state = static_cast<AppState *>(appstate);

    if (event->type == SDL_EVENT_QUIT) {
        state->input.quit = true;
        return SDL_APP_SUCCESS;
    }

    if (event->type == SDL_EVENT_KEY_DOWN || event->type == SDL_EVENT_KEY_UP) {
        const bool pressed = (event->type == SDL_EVENT_KEY_DOWN);

        switch (event->key.key) {
            case SDLK_W: state->input.up = pressed; break;
            case SDLK_S: state->input.down = pressed; break;
            case SDLK_A: state->input.left = pressed; break;
            case SDLK_D: state->input.right = pressed; break;
            case SDLK_ESCAPE: state->input.quit = pressed; break;
            default: ;
        }
    }

    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN || event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
        const bool pressed = (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN);
        switch (event->button.button) {
            case SDL_BUTTON_LEFT: state->input.mouse.lDown = pressed; break;
            case SDL_BUTTON_RIGHT: state->input.mouse.rDown = pressed; break;
            default: ;
        }
    }

    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppIterate(void *appstate) {
    const auto state = static_cast<AppState *>(appstate);
    const auto game = state->game;

    const Uint64 now = SDL_GetPerformanceCounter();
    const Uint64 freq = SDL_GetPerformanceFrequency();

    auto dt = static_cast<float>(now - state->last_time) / static_cast<float>(freq);

    SDL_GetMouseState(&state->input.mouse.x, &state->input.mouse.y);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    game->handleInput(state->input);
    game->update(dt);
    game->render();

    state->last_time = now;

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    const auto state = static_cast<AppState *>(appstate);

    delete state->game;
    delete state;
}