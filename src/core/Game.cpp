#include "Game.h"

#include "../entities/Component.hpp"
#include "math/Vector.hpp"


void Game::init() {
    const auto s1 = mEntityManager.addEntity(EntityTag::Neutral);
    s1->addComponent<CPolygon>(30, 30, Color::RED);
    s1->addComponent<CTransform>(Vec2f{100, 100}, 0, Vec2f{1});

    const auto s2 = mEntityManager.addEntity(EntityTag::Neutral);
    s2->addComponent<CPolygon>(4, 100, Color::RED);
    s2->addComponent<CTransform>(Vec2f{500, 100}, 0, Vec2f{1});

    const auto player = mEntityManager.addEntity(EntityTag::Player);
    player->addComponent<CPolygon>(8, 30, Color::GREEN);
    player->addComponent<CTransform>(Vec2f{300, 500}, 0, Vec2f{1});
    player->addComponent<CInput>();
}

void Game::handleInput(const InputState &state) {
    mInputSystem.handleInput(state, mEntityManager.getEntities());
}

void Game::update(const f32 dt) {
    mEntityManager.update();

    for (const auto& entity : mEntityManager.getEntities()) {
        const auto& input = entity->getComponent<CInput>();
        auto& transform = entity->getComponent<CTransform>();

        if (input.exists && transform.exists) {
            auto dx = 0.0f, dy = 0.0f;
            if (input.left) dx -= 1;
            if (input.right) dx += 1;
            if (input.down) dy += 1;
            if (input.up) dy -= 1;
            transform.position += Vec2f{dx, dy} * dt * 250.0f;
        }
    }
}

void Game::render() {
    mRenderer.drawEntities(mEntityManager.getEntities());
    mRenderer.commit();
}
