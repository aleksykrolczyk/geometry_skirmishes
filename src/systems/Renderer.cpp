#include "systems/Renderer.hpp"

#include <cmath>

#include "core/EntityManager.hpp"

void Renderer::drawEntities(const EntityVec &entities) const {
    for (const auto& e : entities) {
        if (e->hasComponent<CPolygon>() && e->hasComponent<CTransform>()) {
            drawPolygon(e->getComponent<CPolygon>(), e->getComponent<CTransform>());
        }
    }
}

void Renderer::drawPolygon(const CPolygon& polygon, const CTransform& transform) const {
    std::vector<SDL_FPoint> vertices;
    vertices.reserve(polygon.vertexCount);

    const float step = 2.0f * std::numbers::pi_v<float> / polygon.vertexCount;
    for (int i = 0; i < polygon.vertexCount; i++) {
        const float angle = i * step;

        const Vec2f local {
            polygon.radius * std::cos(angle),
            polygon.radius * std::sin(angle),
        };

        const auto transformed = local
            .scaled(transform.scale)
            .rotated(transform.rotation)
            .translated(transform.position);

        vertices.push_back(SDL_FPoint{transformed.x, transformed.y});
    }
    vertices.push_back(vertices[0]);


    SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
    SDL_RenderLines(mRenderer, vertices.data(), vertices.size());
}

void Renderer::commit() const {
    SDL_RenderPresent(mRenderer);
}

