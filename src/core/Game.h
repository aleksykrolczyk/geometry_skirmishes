#pragma once

#include "EntityManager.hpp"
#include "InputState.hpp"
#include "SDL3/SDL_render.h"
#include "systems/Renderer.hpp"


class Game {
private:
    EntityManager mEntityManager;
    Renderer mRenderer;
    InputState mInputState;

    std::shared_ptr<Entity> mPlayer;
    std::shared_ptr<Entity> mCursor;

    void sInput();
    void sCursor();
    void sMovement(f32 dt);
    void sAnimation(f32 dt);
    void sSpawn();

public:
    explicit Game(SDL_Renderer* render): mRenderer(render) {};

    void init();
    void handleInput(const InputState& state);
    void update(f32 dt);

    void render();
};


