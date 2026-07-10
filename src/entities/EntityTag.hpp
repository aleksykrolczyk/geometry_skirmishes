#pragma once

enum class EntityTag {
    Player,
    Cursor,
    Enemy,
    Neutral,
    Bullet,
};


constexpr std::string_view EntityTagToString(const EntityTag entityTag) {
    switch (entityTag) {
        case EntityTag::Player: return "Player";
        case EntityTag::Cursor: return "Cursor";
        case EntityTag::Enemy: return "Enemy";
        case EntityTag::Neutral: return "Neutral";
        case EntityTag::Bullet: return "Bullet";
    }
    return "Unknown";
}
