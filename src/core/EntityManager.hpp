#pragma once

#include <map>
#include <memory>
#include <vector>

#include "common/Types.hpp"
#include "entities/Entity.hpp"

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<EntityTag, EntityVec> EntityMap;

class EntityManager {
    usize mTotalEntities = 0;
    EntityVec mEntities;
    EntityMap mEntitiesMap;
    EntityVec mToAdd;

public:
    void update();
    EntityVec& getEntities();
    EntityVec& getEntities(const EntityTag& tag);

    const EntityVec& getEntities() const;
    const EntityVec& getEntities(const EntityTag& tag) const;

    std::shared_ptr<Entity> getFirst(const EntityTag& tag);
    std::shared_ptr<Entity> addEntity(EntityTag tag);
};


