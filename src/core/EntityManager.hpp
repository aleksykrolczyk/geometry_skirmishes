#pragma once

#include <map>
#include <memory>
#include <vector>

#include "entities/Entity.hpp"

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<EntityTag, EntityVec> EntityMap;

class EntityManager {
    size_t mTotalEntities = 0;

    EntityVec mEntities;
    EntityMap mEntitiesMap;

    EntityVec mToAdd;

public:
    void update();
    EntityVec& getEntities();
    EntityVec& getEntities(const EntityTag& tag);
    std::shared_ptr<Entity> addEntity(EntityTag tag);
};


