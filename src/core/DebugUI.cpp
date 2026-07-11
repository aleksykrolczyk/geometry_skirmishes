#include "DebugUI.hpp"

#include <imgui.h>

void DebugUI::draw(const Game& game) {
    const auto& entities = game.entityManager().getEntities();

    ImGui::Begin("Debug");

    ImGui::Text("Score: %d", game.score());
    ImGui::Text("Total entities: %zu", entities.size());

    ImGui::Separator();

    if (ImGui::TreeNode("Entity List")) {
        for (const auto& entity : entities) {
            ImGui::PushID(entity.get());

            const auto& poly = entity->getComponent<CPolygon>();
            const auto& transform = entity->getComponent<CTransform>();

            ImGui::Text(
                "#%03zu %-12s Pos(%.1f, %.1f) Vertices:%d",
                entity->getId(),
                EntityTagToString(entity->getTag()).data(),
                transform.exists ? transform.position.x : 0.0f,
                transform.exists ? transform.position.y : 0.0f,
                poly.exists ? poly.vertexCount : 0
            );

            ImGui::PopID();
        }

        ImGui::TreePop();
    }

    ImGui::End();
}