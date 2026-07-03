#include "Game.h"

#include "../entities/Component.hpp"
#include "math/Vector.hpp"


void Game::init() {
    const auto s1 = mEntityManager.addEntity(EntityTag::Neutral);
    s1->addComponent<CPolygon>(4, 30, Color::RED);
    s1->addComponent<CTransform>(Vec2f{100, 100}, 0, Vec2f{1});

    mPlayer = mEntityManager.addEntity(EntityTag::Player);
    mPlayer->addComponent<CPolygon>(8, 30, Color::GREEN);
    mPlayer->addComponent<CTransform>(Vec2f{300, 500}, 0, Vec2f{1});
    mPlayer->addComponent<CInput>();

    mCursor = mEntityManager.addEntity(EntityTag::Cursor);
    mCursor->addComponent<CPolygon>(20, 5, Color::WHITE);
    mCursor->addComponent<CTransform>(Vec2f{-1, -1}, 0, Vec2f{1});
}

void Game::handleInput(const InputState &state) {
    mInputState = state;
}

void Game::update(const f32 dt) {
    mEntityManager.update();

    sCursor();
    sInput();
    sAnimation(dt);
    sMovement(dt);
    sSpawn();
}

void Game::sInput() {
    for (const auto& entity : mEntityManager.getEntities()) {
        auto& input = entity->getComponent<CInput>();
        if (!input.exists) continue;

        input.up = mInputState.up;
        input.down = mInputState.down;
        input.left = mInputState.left;
        input.right = mInputState.right;
    }
}

void Game::sCursor() {
    auto& transform = mCursor->getComponent<CTransform>();
    auto& polygon = mCursor->getComponent<CPolygon>();
    transform.position.x = mInputState.mouse.x;
    transform.position.y = mInputState.mouse.y;
    polygon.color = mInputState.mouse.lDown ? Color::BLUE : Color::WHITE;
}

void Game::sMovement(const f32 dt) {
    const auto& input = mPlayer->getComponent<CInput>();
    auto& transform = mPlayer->getComponent<CTransform>();

    auto dx = 0.0f, dy = 0.0f;

    if (input.left)  dx -= 1;
    if (input.right) dx += 1;
    if (input.down)  dy += 1;
    if (input.up)    dy -= 1;

    transform.position += Vec2f{dx, dy} * dt * 250.0f;

}

void Game::sAnimation(f32 dt) {
    for (const auto& entity : mEntityManager.getEntities()) {
        auto& transform = entity->getComponent<CTransform>();
        if (!transform.exists) continue;
        transform.rotation += std::numbers::pi / 2 * dt;
        if (transform.rotation > 2 * std::numbers::pi) {
            transform.rotation -= 2 * std::numbers::pi;
        }
    }
}

void Game::sSpawn() {
    // TODO
}

void Game::render() {
    mRenderer.drawEntities(mEntityManager.getEntities());
    mRenderer.commit();
}
