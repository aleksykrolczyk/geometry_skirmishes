#pragma once
#include "core/EntityManager.hpp"
#include "core/InputState.hpp"


class InputSystem {
public:
    void handleInput(const InputState &state, const EntityVec& entities);
};
