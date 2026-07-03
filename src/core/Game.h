#pragma once

#include "EntityManager.hpp"
#include "InputState.hpp"
#include "SDL3/SDL_render.h"
#include "systems/InputSystem.hpp"
#include "systems/Renderer.hpp"


class Game {
private:
    EntityManager mEntityManager;
    Renderer mRenderer;
    InputSystem mInputSystem;
public:
    explicit Game(SDL_Renderer* render): mRenderer(render) {};

    void init();
    void handleInput(const InputState& state);
    void update(f32 dt);
    void render();
};


