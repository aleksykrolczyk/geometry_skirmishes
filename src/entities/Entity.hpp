#pragma once

#include <tuple>

#include "Component.hpp"
#include "EntityTag.hpp"


using ComponentTuple = std::tuple<
    CTransform,
    CLifeSpan,
    CPolygon,
    CInput
>;

class Entity {
private:
    friend class EntityManager;

    const EntityTag mTag;
    const std::size_t mId;
    bool mIsAlive = true;

    ComponentTuple mComponents;

    Entity(const EntityTag tag, const std::size_t id): mTag(tag), mId(id) {}

public:
    bool isAlive() const {
        return mIsAlive;
    }

    EntityTag getTag() const {
        return mTag;
    }

    std::size_t getId() const {
        return mId;
    }

    void destroy() {
        mIsAlive = false;
    }

    template<typename T, typename... TArgs>
    T& addComponent(TArgs&&... args) {
        auto& component = std::get<T>(mComponents);
        component = T(std::forward<TArgs>(args)...);
        component.exists = true;
        return component;
    }

    template <typename T>
    T& getComponent() {
        return std::get<T>(mComponents);
    }

    template <typename T>
    const T& getComponent() const {
        return std::get<T>(mComponents);
    }

    template <typename T>
    bool hasComponent() const {
        return std::get<T>(mComponents).exists;
    }

    template <typename T>
    void removeComponent() {
        std::get<T>(mComponents) = T();
    }
};
