

#include <random>
#include <bits/locale_classes.h>

class RandomGenerator {
private:
    static std::mt19937& engine() {
        static std::mt19937 rng(std::random_device{}());
        return rng;
    }

public:
    static int getInt() {
        return getInt(0, INT_MAX);
    }

    static int getInt(const int min, const int max) {
        std::uniform_int_distribution dist(min, max);
        return dist(engine());
    }

    static float getFloat() {
        return getFloat(0.0f, 1.0f);
    }

    static float getFloat(const float min, const float max) {
        std::uniform_real_distribution dist(min, max);
        return dist(engine());
    }
};
