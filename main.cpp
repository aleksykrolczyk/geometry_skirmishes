#define SDL_MAIN_USE_CALLBACKS 1
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "core/DebugUI.hpp"
#include "core/Game.h"


struct AppState {
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    std::unique_ptr<Game> game;
    DebugUI debugUI;
    Uint64 last_time{};
    InputState input;
} ;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    auto *state = new AppState();

    if (!SDL_CreateWindowAndRenderer("Hello World", 1600, 900, SDL_WINDOW_RESIZABLE, &state->window, &state->renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->game = std::make_unique<Game>(state->window, state->renderer);
    state->last_time = SDL_GetPerformanceCounter();
    *appstate = state;

    state->game->init();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(state->window, state->renderer);

    ImGui_ImplSDLRenderer3_Init(state->renderer);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    auto *state = static_cast<AppState *>(appstate);

    ImGui_ImplSDL3_ProcessEvent(event);

    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    if (event->type == SDL_EVENT_KEY_DOWN || event->type == SDL_EVENT_KEY_UP) {
        const bool pressed = (event->type == SDL_EVENT_KEY_DOWN);

        switch (event->key.key) {
            case SDLK_W: state->input.up.current = pressed; break;
            case SDLK_S: state->input.down.current = pressed; break;
            case SDLK_A: state->input.left.current = pressed; break;
            case SDLK_D: state->input.right.current = pressed; break;
            default: ;
        }
    }

    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN || event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
        const bool pressed = (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN);
        switch (event->button.button) {
            case SDL_BUTTON_LEFT: state->input.mouse.left.current = pressed; break;
            case SDL_BUTTON_RIGHT: state->input.mouse.right.current = pressed; break;
            default: ;
        }
    }

    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppIterate(void *appstate) {
    const auto state = static_cast<AppState *>(appstate);

    const Uint64 now = SDL_GetPerformanceCounter();
    const Uint64 freq = SDL_GetPerformanceFrequency();
    auto dt = static_cast<float>(now - state->last_time) / static_cast<float>(freq);

    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();


    SDL_GetMouseState(&state->input.mouse.x, &state->input.mouse.y);

    SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255);
    SDL_RenderClear(state->renderer);

    state->game->handleInput(state->input);
    state->game->update(dt);
    state->game->render();

    state->debugUI.draw(*state->game);
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), state->renderer);

    SDL_RenderPresent(state->renderer);


    state->input.endFrame();
    state->last_time = now;

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    const auto state = static_cast<AppState *>(appstate);

    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();


    delete state;
}