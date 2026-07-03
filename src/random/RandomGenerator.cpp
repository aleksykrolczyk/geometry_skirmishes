

#include <random>
#include <bits/locale_classes.h>

#include "common/Types.hpp"

class RandomGenerator {
private:
    static std::mt19937& engine() {
        static std::mt19937 rng(std::random_device{}());
        return rng;
    }

public:
    static i32 getInt() {
        return getInt(0, INT_MAX);
    }

    static i32 getInt(const i32 min, const i32 max) {
        std::uniform_int_distribution dist(min, max);
        return dist(engine());
    }

    static f32 getFloat() {
        return getFloat(0.0f, 1.0f);
    }

    static f32 getFloat(const f32 min, const f32 max) {
        std::uniform_real_distribution dist(min, max);
        return dist(engine());
    }
};
