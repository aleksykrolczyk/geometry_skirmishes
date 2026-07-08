#pragma once
#include "entities/Entity.hpp"

namespace Physics {
    inline bool isCollision(const Entity &a, const Entity &b) {
        const auto& ta = a.getComponent<CTransform>();
        const auto& ca = a.getComponent<CCollision>();

        const auto& tb = b.getComponent<CTransform>();
        const auto& cb = b.getComponent<CCollision>();
        if (!ta.exists || !ca.exists || !tb.exists || !cb.exists) {
            return false;
        }
        const Vec2f dv = ta.position - tb.position;
        const f32 dr = ca.radius + cb.radius;
        return (dv.x * dv.x + dv.y * dv.y) < (dr * dr);
    }
}
