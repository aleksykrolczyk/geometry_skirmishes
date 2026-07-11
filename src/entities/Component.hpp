#pragma once
#include "../common/Color.hpp"
#include "math/Vector.hpp"

struct Component {
    bool exists = false;
    void enable()  { exists = true; }
    void disable() { exists = false; }
};


struct  CLifeSpan : Component {
    i32 totalLifespan = 0;
    i32 remainingLifespan = 0;

    CLifeSpan() = default;
    CLifeSpan(const i32 totalLifespan, const i32 remainingLifespan):
        totalLifespan(totalLifespan), remainingLifespan(remainingLifespan) {}
};

struct CPolygon : Component {
    i32 vertexCount = 0;
    i32 radius = 0;
    Color color = {};

    CPolygon() = default;
    CPolygon(const i32 vertexCount, const i32 radius, const Color& color):
        vertexCount(vertexCount), radius(radius), color(color) {}
};

struct  CTransform : Component {
    Vec2f position = {0.0f, 0.0f};
    f32 rotation = {0.0f};
    Vec2f scale = {1.0f, 1.0f};

    CTransform() = default;
    CTransform(const Vec2f& position, const f32 rotation, const Vec2f& scale):
        position(position), rotation(rotation), scale(scale) {}
};

struct CInput : Component {
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;

    bool shoot = false;
    Vec2f mousePosition;

    CInput() = default;
};

struct CCollision : Component {
    i32 radius = 0;

    CCollision() = default;
    explicit CCollision(const i32 radius): radius(radius) {}
};

struct CVelocity : Component {
    Vec2f velocity = {0.0f, 0.0f};
    CVelocity() = default;
    explicit CVelocity(const Vec2f velocity): velocity(velocity) {}
};

struct CBoundary : Component {

    enum class BoundaryMode { Clamp, Destroy };

    BoundaryMode mode = BoundaryMode::Clamp;
    f32 margin = 0;

    CBoundary() = default;
    explicit CBoundary(const BoundaryMode mode, const f32 margin = 0): mode(mode), margin(margin) {}
};

struct CScore : Component {
    i32 score = 0;

    CScore() = default;
    explicit CScore(const i32 score): score(score) {}

    void addScore(const i32 s) {
        score += s;
    }
};
