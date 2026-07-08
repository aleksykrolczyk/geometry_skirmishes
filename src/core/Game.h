#pragma once

#include "EntityManager.hpp"
#include "InputState.hpp"
#include "SDL3/SDL_render.h"
#include "systems/Renderer.hpp"


class Game {
private:
    f32 mPlayerSpeed = 250;

    EntityManager mEntityManager;
    Renderer mRenderer;
    InputState mInputState;

    std::shared_ptr<Entity> mPlayer;
    std::shared_ptr<Entity> mCursor;

    void sControl() const;
    void sPhysics(f32 dt);
    void sAnimation(f32 dt);

    void spawnBullet();

public:
    explicit Game(SDL_Renderer* render): mRenderer(render) {};

    void init();
    void handleInput(const InputState& state);
    void update(f32 dt);

    void render();
};


