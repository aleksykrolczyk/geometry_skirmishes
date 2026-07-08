#pragma once

#include "EntityManager.hpp"
#include "InputState.hpp"
#include "SDL3/SDL_render.h"
#include "systems/Renderer.hpp"


class Game {
private:
    struct GameConfig {
        f32 playerSpeed = 250;
        f32 bulletSpeed = 500;
        f32 bulletRadius = 5;
    };

    GameConfig mConfig;

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
    explicit Game(SDL_Renderer* render): mRenderer(render) {};

    void init();
    void handleInput(const InputState& state) const;

    void update(f32 dt);

    void render();
};


