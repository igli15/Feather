//
// Created by Igli milaqi on 27/02/2020.
//

#ifndef CROW_ENTITYHANDLE_H
#define CROW_ENTITYHANDLE_H

#include "Types.h"
#include "World.h"

///A small wrapper for the entity.
///It provides a more "GameObject" style of programming which is more intuitive is certain cases.
///Instead of doing world->AddComponent(entity,component) you do entityHandle->AddComponent(component) instead.
struct EntityHandle {

    Entity entity;
    World* world;

    ///Adds a component of a certain type to the entity.
    ///@param component The component which is going to be added.
    template <typename T, typename... Args>
    T* AddComponent(Args&&... args)
    {
        return world->AddComponent<T,Args...>(entity, std::forward<Args>(args)...);
    }

    ///Removes a component of a certain type to the entity.
    template <typename T>
    void RemoveComponent()
    {
        world->RemoveComponent<T>(entity);
    }

    ///Get a component of a certain type from the entity.
    ///@return Returns a "ComponentHandle<T>" which can contain a valid component pointer or a nullptr if no component was found.
    template <typename T>
    T& GetComponent()
    {
        return world->GetComponent<T>(entity);
    }

    template <typename T>
    T* GetComponentPtr()
    {
        return world->GetComponentPtr<T>(entity);
    }

    void Destroy()
    {
        world->DestroyEntity(entity);
    }

    EntityHandle& operator=(const EntityHandle& other)
    {
        entity = other.entity;
        world = other.world;
        return *this;
    }

    bool operator == (const EntityHandle &other) const
    {
        return(this->entity == other.entity);
    }

};


#endif //CROW_ENTITYHANDLE_H
