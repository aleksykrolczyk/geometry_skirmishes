#include "EntityManager.hpp"

#include <ranges>

void EntityManager::update() {
    std::erase_if(mEntities,[](const std::shared_ptr<Entity>& e){ return !e->isAlive(); });
    for (auto& eVec: mEntitiesMap | std::views::values) {
        std::erase_if(eVec,[](const std::shared_ptr<Entity>& e){ return !e->isAlive(); });
    }

    for (const auto& e : mToAdd) {
        mEntities.push_back(e);
        mEntitiesMap[e->getTag()].push_back(e);
    }

    mToAdd.clear();

}

EntityVec & EntityManager::getEntities() {
    return mEntities;
}

EntityVec &EntityManager::getEntities(const EntityTag &tag) {
    return mEntitiesMap[tag];
}

std::shared_ptr<Entity> EntityManager::addEntity(const EntityTag tag) {
    auto e = std::shared_ptr<Entity>(new Entity(tag, mTotalEntities++));
    mToAdd.push_back(e);
    return e;
}
