#include "InputSystem.hpp"


void InputSystem::handleInput(const InputState &state, const EntityVec& entities) {
    for (auto& entity : entities) {
        auto& input = entity->getComponent<CInput>();
        if (!input.exists) continue;

        input.up = state.up;
        input.down = state.down;
        input.left = state.left;
        input.right = state.right;

        if (auto& transform = entity->getComponent<CTransform>(); transform.exists) {
            Vec2f direction;
            if (input.left)  direction.x -= 1.0f;
            if (input.right) direction.x += 1.0f;
            if (input.up)    direction.y -= 1.0f;
            if (input.down)  direction.y += 1.0f;
            if (direction.x != 0.0f || direction.y != 0.0f) {
                transform.rotation = direction.toAngle();
            }
        }
    }
}
