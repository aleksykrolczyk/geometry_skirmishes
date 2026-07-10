#include "DebugUI.hpp"

#include <imgui.h>

void DebugUI::draw(const Game& game) {
    const auto& entities = game.entityManager().getEntities();

    ImGui::Begin("Entities");

    ImGui::Text("Entities [%zu]", entities.size());
    for (const auto& entity: entities) {
        ImGui::PushID(entity.get());
        const auto poly = entity->getComponent<CPolygon>();
        const auto sides = poly.exists ? poly.vertexCount : 0;
        ImGui::Text(
            "Entity %03zu | %-8s | vertices: %d",
            entity->getId(),
            EntityTagToString(entity->getTag()).data(),
            sides
        );
        ImGui::PopID();
    }

    ImGui::End();
}
