#pragma once

#include "EntityManager.hpp"
#include "InputState.hpp"
#include "SDL3/SDL_render.h"
#include "systems/Renderer.hpp"

struct GameConfig {
    f32 playerSpeed = 500;
    f32 playerRadius = 20;
    f32 bulletSpeed = 750;
    f32 bulletRadius = 5;
};

struct World {
    Vec2f size = {1600, 900};
};

class Game {
private:
    GameConfig mConfig;
    World mWorld;

    EntityManager mEntityManager;
    Renderer mRenderer;

    std::shared_ptr<Entity> mPlayer;
    std::shared_ptr<Entity> mCursor;

    void sControl() const;
    void sMovement(f32 dt);
    void sSpawn();
    void sAnimation(f32 dt);

    void spawnBullet(const Vec2f &from, const Vec2f &to);

public:
    explicit Game(SDL_Window* window, SDL_Renderer* render): mRenderer(window, render, mWorld.size) {};

    void init();
    void handleInput(const InputState& state) const;

    void update(f32 dt);

    void render();
};


