#include "Game.h"

#include <algorithm>

#include "Physics.hpp"
#include "math/Vector.hpp"
#include "../common/Random.hpp"


void Game::init() {
    mPlayer = mEntityManager.addEntity(EntityTag::Player);
    mPlayer->addComponent<CPolygon>(8, mConfig.playerRadius, Color::GREEN);
    mPlayer->addComponent<CCollision>(mConfig.playerRadius);
    mPlayer->addComponent<CVelocity>(Vec2f{0, 0});
    mPlayer->addComponent<CTransform>(mWorld.size / 2, 0, Vec2f{1});
    mPlayer->addComponent<CInput>();
    mPlayer->addComponent<CBoundary>(CBoundary::BoundaryMode::Clamp);

    mCursor = mEntityManager.addEntity(EntityTag::Cursor);
    mCursor->addComponent<CPolygon>(20, 5, Color::WHITE);
    mCursor->addComponent<CTransform>(Vec2f{-1, -1}, 0, Vec2f{1});
}

void Game::handleInput(const InputState &state) const {
    auto &input = mPlayer->getComponent<CInput>();
    input.up = state.up.down();
    input.down = state.down.down();
    input.left = state.left.down();
    input.right = state.right.down();

    input.shoot = state.mouse.left.pressed();
    input.mousePosition = mRenderer.screenToWorld({state.mouse.x, state.mouse.y});

    auto& transform = mCursor->getComponent<CTransform>();
    auto& polygon = mCursor->getComponent<CPolygon>();
    transform.position = input.mousePosition;
    polygon.color = state.mouse.left.down() ? Color::BLUE : Color::WHITE;
}

void Game::update(const f32 dt) {
    mEntityManager.update();
    sControl();
    sMovement(dt);
    sPlayerActions();
    sEnemySpawn(dt);
    sBoundary();
    sAnimation(dt);
}

void Game::sControl() const {
    const auto& input = mPlayer->getComponent<CInput>();
    auto& velocity = mPlayer->getComponent<CVelocity>();
    Vec2f direction{0,0};

    if (input.left) direction.x -= 1;
    if (input.right) direction.x += 1;
    if (input.up) direction.y -= 1;
    if (input.down) direction.y += 1;

    velocity.velocity = direction.isZero() ? Vec2f{0, 0} : direction.normalized() * mConfig.playerSpeed;
}

void Game::sMovement(const f32 dt) {
    for (const auto& entity : mEntityManager.getEntities()) {
        auto& transform = entity->getComponent<CTransform>();
        auto& velocity = entity->getComponent<CVelocity>();

        if (!transform.exists || !velocity.exists) continue;

        const Vec2f delta = velocity.velocity * dt;
        transform.position += delta;
        for (const auto& other : mEntityManager.getEntities()) {
            if (entity == other) continue;

            if (Physics::isCollision(*entity, *other)) {
                switch (entity->getTag()) {
                    case EntityTag::Player:
                        transform.position -= delta;
                        velocity.velocity = {0,0};
                        break;
                    case EntityTag::Bullet:
                        entity->destroy();
                    default: ;
                }
            }
        }
    }
}

void Game::sPlayerActions() {
    const auto& input = mPlayer->getComponent<CInput>();
    if (input.shoot) {
        spawnBullet(mPlayer->getComponent<CTransform>().position, input.mousePosition);
    }
}

void Game::sEnemySpawn(const f32 dt) {
    mEnemyTimer += dt;
    if (mEnemyTimer < mConfig.enemySpawnDelay) {
        return;
    }

    const i32 verticesCount = Random::getInt(3, mConfig.enemyMaxVertices);
    const f32 radius = Random::getFloat(mConfig.enemyRadiusLimits.first, mConfig.enemyRadiusLimits.second);

    Vec2f pos;
    const auto posOffset = 2 * radius;

    switch (Random::getInt(0, 3)) {
        case 0: // top
            pos = {Random::getFloat(0, mWorld.size.x), -posOffset};
            break;
        case 1: // left
            pos = {-posOffset, Random::getFloat(0, mWorld.size.y)};
            break;
        case 2: // bottom
            pos = {Random::getFloat(0, mWorld.size.x), mWorld.size.y + posOffset};
            break;
        case 3: //right
            pos = {mWorld.size.x + posOffset, Random::getFloat(0, mWorld.size.y)};
            break;
        default: break;
    }

    const auto speed = Random::getFloat(mConfig.enemySpeedLimits.first, mConfig.enemySpeedLimits.second);
    const Vec2f target{Random::getFloat(0, mWorld.size.x), Random::getFloat(0, mWorld.size.y)};
    const Vec2f velocity = (target - pos).normalized() * speed;

    spawnEnemy(pos, verticesCount, radius, velocity);
    mEnemyTimer -= mConfig.enemySpawnDelay;
}

void Game::sBoundary() {
    for (const auto& entity : mEntityManager.getEntities()) {
        auto& boundary = entity->getComponent<CBoundary>();
        auto& transform = entity->getComponent<CTransform>();
        if (!boundary.exists || !transform.exists) continue;

        const auto& p = transform.position;
        const bool outside =
            p.x < -boundary.margin ||
            p.x > +boundary.margin + mWorld.size.x ||
            p.y < -boundary.margin ||
            p.y > +boundary.margin + mWorld.size.y;

        if (!outside) continue;
        switch (boundary.mode) {
            case CBoundary::BoundaryMode::Clamp:
                transform.position.x = std::ranges::clamp(transform.position.x, 0.0f, mWorld.size.x);
                transform.position.y = std::ranges::clamp(transform.position.y, 0.0f, mWorld.size.y);
                break;
            case CBoundary::BoundaryMode::Destroy:
                entity->destroy();
        }
    }
}

void Game::sAnimation(const f32 dt) {
    for (const auto& entity : mEntityManager.getEntities()) {
        auto& transform = entity->getComponent<CTransform>();
        if (!transform.exists) continue;
        transform.rotation += std::numbers::pi / 2 * dt;
        if (transform.rotation > 2 * std::numbers::pi) {
            transform.rotation -= 2 * std::numbers::pi;
        }
    }
}


void Game::spawnBullet(const Vec2f& from, const Vec2f& to) {
    const auto bullet = mEntityManager.addEntity(EntityTag::Bullet);
    const auto playerRadius = mPlayer->getComponent<CPolygon>().radius;
    const auto direction = (to - from).normalized();

    const auto spawnPosition = from + direction * ((playerRadius + mConfig.bulletRadius) * 1.05);
    bullet->addComponent<CPolygon>(10, mConfig.bulletRadius, Color::WHITE);
    bullet->addComponent<CCollision>(mConfig.bulletRadius);
    bullet->addComponent<CTransform>(spawnPosition, 0, Vec2f{1});
    bullet->addComponent<CVelocity>(direction * mConfig.bulletSpeed);
    bullet->addComponent<CBoundary>(CBoundary::BoundaryMode::Destroy, 2 * mConfig.bulletRadius);
}

void Game::spawnEnemy(const Vec2f &at, i32 vertices, f32 radius, Vec2f velocity) {
    const auto enemy = mEntityManager.addEntity(EntityTag::Enemy);
    enemy->addComponent<CPolygon>(vertices, radius, Color::RED);
    enemy->addComponent<CCollision>(radius);
    enemy->addComponent<CTransform>(at, 0, Vec2f{1});
    enemy->addComponent<CVelocity>(velocity);
    enemy->addComponent<CBoundary>(CBoundary::BoundaryMode::Destroy, 2 * radius);

}

void Game::render() {
    mRenderer.drawEntities(mEntityManager.getEntities());
}

const EntityManager& Game::entityManager() const {
    return mEntityManager;
}
