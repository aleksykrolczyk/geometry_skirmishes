#include "Game.h"

#include "Physics.hpp"
#include "math/Vector.hpp"
#include "random/Random.hpp"


void Game::init() {
    const auto s1 = mEntityManager.addEntity(EntityTag::Neutral);
    s1->addComponent<CPolygon>(4, 30, Color::RED);
    s1->addComponent<CCollision>(30);
    s1->addComponent<CTransform>(Vec2f{250, 250}, 0, Vec2f{1});

    mPlayer = mEntityManager.addEntity(EntityTag::Player);
    mPlayer->addComponent<CPolygon>(8, mConfig.playerRadius, Color::GREEN);
    mPlayer->addComponent<CCollision>(mConfig.playerRadius);
    mPlayer->addComponent<CVelocity>(Vec2f{0, 0});
    mPlayer->addComponent<CTransform>(mWorld.size / 2, 0, Vec2f{1});
    mPlayer->addComponent<CInput>();

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
    const Vec2f pos = {Random::getFloat(0, mWorld.size.x), Random::getFloat(0, mWorld.size.y)};
    const i32 verticesCount = Random::getInt(3, mConfig.enemyMaxVertices);
    const f32 radius = Random::getFloat(mConfig.enemyRadiusLimits.first, mConfig.enemyRadiusLimits.second);
    const Vec2f v = (Vec2f{Random::getFloat(), Random::getFloat()} - Vec2f{0.5, 0.5}) * 2;
    const auto speed = Random::getFloat(mConfig.enemySpeedLimits.first, mConfig.enemySpeedLimits.second);
    spawnEnemy(pos, verticesCount, radius, v.normalized() * speed);
    mEnemyTimer -= mConfig.enemySpawnDelay;
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
    bullet->addComponent<CPolygon>(10, mConfig.bulletRadius, Color::RED);
    bullet->addComponent<CCollision>(mConfig.bulletRadius);
    bullet->addComponent<CTransform>(spawnPosition, 0, Vec2f{1});
    bullet->addComponent<CVelocity>(direction * mConfig.bulletSpeed);
}

void Game::spawnEnemy(const Vec2f &at, i32 vertices, f32 radius, Vec2f velocity) {
    const auto enemy = mEntityManager.addEntity(EntityTag::Enemy);
    enemy->addComponent<CPolygon>(vertices, radius, Color::RED);
    enemy->addComponent<CCollision>(radius);
    enemy->addComponent<CTransform>(at, 0, Vec2f{1});
    enemy->addComponent<CVelocity>(velocity);
}

void Game::render() {
    mRenderer.drawEntities(mEntityManager.getEntities());
    mRenderer.commit();
}
