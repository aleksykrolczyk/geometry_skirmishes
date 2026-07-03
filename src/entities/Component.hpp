#pragma once
#include "../common/Color.hpp"
#include "math/Vector.hpp"

struct Component {
    bool exists = false;
    Component& enable() {
        exists = true;
        return *this;
    }
    Component& disable() {
        exists = false;
        return *this;
    }
};


struct  CLifeSpan : Component {
    i32 totalLifespan = 0;
    i32 remainingLifespan = 0;

    CLifeSpan() = default;
    CLifeSpan(const i32 totalLifespan, const i32 remainingLifespan): totalLifespan(totalLifespan), remainingLifespan(remainingLifespan) {
        exists = true;
    }
};

struct CPolygon : Component {
    i32 vertexCount = 0;
    i32 radius = 0;
    Color color = {};

    CPolygon() = default;
    CPolygon(const i32 vertexCount, const i32 radius, const Color& color) : vertexCount(vertexCount), radius(radius), color(color) {
        exists = true;
    }
};

struct  CTransform : Component {
    Vec2f position = {0.0f, 0.0f};
    f32 rotation = {0.0f};
    Vec2f scale = {1.0f, 1.0f};

    CTransform() = default;
    CTransform(const Vec2f& position, const f32 rotation, const Vec2f& scale):
        position(position), rotation(rotation), scale(scale)
    {
        exists = true;
    }
};

struct CInput : Component {
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;

    CInput() = default;
};

struct CCollision : Component {
    i32 radius = 0;
};