#pragma once

#include "core/EntityManager.hpp"
#include "SDL3/SDL_render.h"

class Renderer {
public:
    explicit Renderer(SDL_Window* window, SDL_Renderer* renderer, Vec2f worldSize);

    void drawEntities(const EntityVec& entities) const;

    [[nodiscard]]
    Vec2f screenToWorld(const Vec2f &screen) const;

    [[nodiscard]]
    Vec2f worldToScreen(const Vec2f &world) const;

private:
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    Vec2f mWorldSize;
    Vec2f mScreenSize;

    void drawPolygon(const CPolygon &polygon, const CTransform &transform) const;
};
