#pragma once

#include "core/EntityManager.hpp"
#include "SDL3/SDL_render.h"

class Renderer {
public:
    explicit Renderer(SDL_Renderer* renderer) : mRenderer(renderer) {};
    void drawEntities(const EntityVec& entities) const;
    void commit() const;

private:
    SDL_Renderer* mRenderer;
    void drawPolygon(const CPolygon &polygon, const CTransform &transform) const;
};
