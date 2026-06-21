#include "Game.h"

#include "../entities/Component.hpp"
#include "math/Vector.hpp"


void Game::init() {
    const auto s1 = mEntityManager.addEntity(EntityTag::Neutral);
    s1->addComponent<CPolygon>(4, 30);
    s1->addComponent<CTransform>(Vec2f{100, 100}, 0, Vec2f{1});

    const auto s2 = mEntityManager.addEntity(EntityTag::Neutral);
    s2->addComponent<CPolygon>(10, 100);
    s2->addComponent<CTransform>(Vec2f{500, 100}, 0, Vec2f{1});

    const auto s3 = mEntityManager.addEntity(EntityTag::Player);
    s3->addComponent<CPolygon>(3, 30);
    s3->addComponent<CTransform>(Vec2f{300, 500}, 0, Vec2f{2, 1});
    s3->addComponent<CInput>();
}

void Game::handleInput(const InputState &state) {
    mInputSystem.handleInput(state, mEntityManager.getEntities());
}

void Game::update(const float dt) {
    mEntityManager.update();

    for (auto& entity : mEntityManager.getEntities()) {
        auto& input = entity->getComponent<CInput>();
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
