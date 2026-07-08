#pragma once
#include <cmath>

template <typename T>
struct Vec2 {

    T x = 0, y = 0;

    Vec2() = default;
    Vec2(T x, T y) : x(x), y(y) {}
    explicit Vec2(T both) : x(both), y(both) {}

    Vec2 operator + (const Vec2& rhs) const {
        return Vec2(x + rhs.x, y + rhs.y);
    }

    Vec2 operator - (const Vec2& rhs) const {
        return Vec2(x - rhs.x, y - rhs.y);
    }

    Vec2 operator * (const float rhs) const {
        return Vec2(x * rhs, y * rhs);
    }

    Vec2 operator / (const float rhs) const {
        return Vec2(x / rhs, y / rhs);
    }

    Vec2& operator+=(const Vec2& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vec2& operator-=(const Vec2& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vec2& operator*=(T rhs) {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    Vec2& operator/=(T rhs) {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    bool operator == (const Vec2& rhs) {
        return x == rhs.x && y == rhs.y;
    }

    T length() {
        return sqrtf(x * x + y * y);
    }

    float distance(const Vec2& rhs) {
        return (rhs - *this).length();
    }

    Vec2 normalized() {
        auto len = length();
        if (len < 1e-6f) {
            return Vec2(0, 0);
        }
        return {x / len, y / len};
    }

    Vec2 rotated(const float angle) const {
        const float c = std::cos(angle);
        const float s = std::sin(angle);

        return Vec2(
            x * c - y * s,
            x * s + y * c
        );
    }

    Vec2 translated(const Vec2& offset) const {
        return *this + offset;
    }

    Vec2 scaled(const T scale) const {
        return *this * scale;
    }

    Vec2 scaled(const Vec2& scale) const {
        auto c = *this;
        c.x *= scale.x;
        c.y *= scale.y;
        return c;
    }

    T toAngle() const {
        return std::atan2(y, x);
    }


};

typedef Vec2<f32> Vec2f;
