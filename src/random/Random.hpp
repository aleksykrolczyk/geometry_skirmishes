#pragma once

#include <climits>
#include <random>

#include "common/Types.hpp"

namespace Random
{
    inline std::mt19937& engine() {
        static std::mt19937 rng(std::random_device{}());
        return rng;
    }

    inline i32 getInt(i32 min, i32 max) {
        std::uniform_int_distribution<i32> dist(min, max);
        return dist(engine());
    }

    inline i32 getInt() {
        return getInt(0, INT_MAX);
    }

    inline f32 getFloat(const f32 min, const f32 max) {
        std::uniform_real_distribution<f32> dist(min, max);
        return dist(engine());
    }

    inline f32 getFloat() {
        return getFloat(0.0f, 1.0f);
    }
}