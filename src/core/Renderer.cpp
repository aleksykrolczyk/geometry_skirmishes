#include "Renderer.hpp"

#include <cmath>

#include "core/EntityManager.hpp"

Renderer::Renderer(SDL_Window *window, SDL_Renderer *renderer, const Vec2f worldSize):
    mWindow(window), mRenderer(renderer), mWorldSize(worldSize)
{
    i32 w, h;
    SDL_GetWindowSize(mWindow, &w, &h);
    mScreenSize = {static_cast<float>(w), static_cast<float>(h)};
}

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

    const f32 step = 2.0f * std::numbers::pi_v<f32> / polygon.vertexCount;
    for (u32 i = 0; i < polygon.vertexCount; i++) {
        const f32 angle = i * step;

        const Vec2f local {
            polygon.radius * std::cos(angle),
            polygon.radius * std::sin(angle),
        };

        const auto transformed = local
            .scaled(transform.scale)
            .rotated(transform.rotation)
            .translated(transform.position);

        const auto screen = worldToScreen(transformed);
        vertices.push_back(SDL_FPoint{screen.x, screen.y});
    }
    vertices.push_back(vertices[0]);


    const auto& [r, g, b, a] = polygon.color;
    SDL_SetRenderDrawColor(mRenderer, r, g, b, a);
    SDL_RenderLines(mRenderer, vertices.data(), vertices.size());
}


Vec2f Renderer::screenToWorld(const Vec2f& screen) const {
    const float scale = std::min(
        mScreenSize.x / mWorldSize.x,
        mScreenSize.y / mWorldSize.y
    );

    const float offsetX = (mScreenSize.x - mWorldSize.x * scale) * 0.5f;
    const float offsetY = (mScreenSize.y - mWorldSize.y * scale) * 0.5f;

    return {
        (screen.x - offsetX) / scale,
        (screen.y - offsetY) / scale
    };
}

Vec2f Renderer::worldToScreen(const Vec2f &world) const {
    const f32 scale = std::min(mScreenSize.x / mWorldSize.x, mScreenSize.y / mWorldSize.y);
    const float offsetX = (mScreenSize.x - mWorldSize.x * scale) * 0.5f;
    const float offsetY = (mScreenSize.y - mWorldSize.y * scale) * 0.5f;
    return {
        offsetX + world.x * scale,
        offsetY + world.y * scale
    };
}

