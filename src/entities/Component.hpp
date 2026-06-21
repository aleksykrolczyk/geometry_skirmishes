#pragma once
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
    int totalLifespan = 0;
    int remainingLifespan = 0;

    CLifeSpan() = default;
    CLifeSpan(const int totalLifespan, const int remainingLifespan): totalLifespan(totalLifespan), remainingLifespan(remainingLifespan) {
        exists = true;
    }
};

struct CPolygon : Component {
    int vertexCount{};
    int radius{};

    CPolygon() = default;
    CPolygon(const int vertexCount, const int radius) : vertexCount(vertexCount), radius(radius) {
        exists = true;
    }
};

struct  CTransform : Component {
    Vec2f position{0.0f, 0.0f};
    float rotation{0.0f};
    Vec2f scale{1.0f, 1.0f};

    CTransform() = default;
    CTransform(const Vec2f& position, const float rotation, const Vec2f& scale):
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
