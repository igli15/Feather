//
// Created by Igli milaqi on 25/05/2020.
//

#ifndef CROW_COMPONENTSPARSESET_H
#define CROW_COMPONENTSPARSESET_H

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "Types.h"
#include <vector>
#include "../EventQueue/EventQueue.h"
#include "../Events/ComponentRemovedEvent.h"
#include "IComponentSet.h"

template <typename ComponentType>
class ComponentSparseSet : public IComponentSet
{
public:

    ComponentSparseSet()
    {
        m_componentDenseArray =(ComponentType*)(calloc(MAX_ENTITIES,sizeof(ComponentType) ));
        m_entitiesDenseArray = (Entity*)(calloc(MAX_ENTITIES,sizeof(Entity)));
        m_indexesSparseArray = (int*)(calloc(MAX_ENTITIES,sizeof(int)));
    }

    ///Adds a component to the specified entity.
    ///@param entity The entity which the component will be added to.
    ///@param Component The component which will be stored on the array.
    ///@return A pointer to the component which was just added.
    ComponentType* AddComponentData(Entity entity,ComponentType componentData)
    {
        if(GetComponentIndex(entity) != -1)
        {
            std::cout<<"Component Already Added"<<std::endl;
            throw;
        }

        size_t index = validSize;

        m_componentDenseArray[index] = componentData;
        m_entitiesDenseArray[index] = entity;
        m_indexesSparseArray[entity] = index;

        validSize++;

        return &(m_componentDenseArray[index]);
    }

    ///Checks if the entity is an index in the array and if so it removes the component attached to it
    ///@param entity The entity which component will be removed
    void RemoveComponentData(Entity entity)
    {
        if(GetComponentIndex(entity) == -1)
        {
            std::cout<<"Component is not added to this entity"<<std::endl;
            return;
        }

        size_t indexOfElementToRemove = m_indexesSparseArray[entity];
        size_t indexOfLastElement = validSize - 1;

        ComponentType comp = m_componentDenseArray[indexOfElementToRemove];

        m_componentDenseArray[indexOfElementToRemove] = m_componentDenseArray[indexOfLastElement];

        Entity entityOfLastElement = m_entitiesDenseArray[indexOfLastElement];

        m_indexesSparseArray[entityOfLastElement] = indexOfElementToRemove;
        m_entitiesDenseArray[indexOfElementToRemove]  = entityOfLastElement;

        validSize--;
        EventQueue::Instance().Publish(new ComponentRemovedEvent<ComponentType>(entity, comp));

    }

    int GetComponentIndex(Entity entity)
    {
        if(entity > MAX_ENTITIES)
        {
            return -1;
        }

        //make sure we are in the sparse set
        if(m_indexesSparseArray[entity] < validSize && m_entitiesDenseArray[m_indexesSparseArray[entity]] == entity)
        {
            return m_indexesSparseArray[entity];
        }
        else
        {
            return -1;
        }
    }

    ///Finds a component for a specified entity and returns a reference to it.
    ///@param entity the entity which component will be looked for.
    ///@return T& a reference to the component.
    ComponentType& GetComponentData(Entity entity)
    {
        int index = GetComponentIndex(entity);

        if(index == -1)
        {
            std::cout<<"Component is not attached to this entity"<<std::endl;
            throw;
        }
        else
        {
            return m_componentDenseArray[index];
        }
    }

    ///Finds a component for a specified entity and returns a POINTER to it.
    ///@param entity the entity which component will be looked for.
    ///@return T* the pointer to the component.
    ComponentType* GetComponentPtr(Entity entity)
    {
        int index = GetComponentIndex(entity);

        if(index == -1)
        {
            return nullptr;
        }
        else
        {
            return &(m_componentDenseArray[index]);
        }
    }

    void OnEntityDestroyed(Entity entity) override
    {
        if (GetComponentIndex(entity) != -1)
        {
            RemoveComponentData(entity);
        }
    }

    std::vector<Entity> GetEntities() override
    {
        std::vector<Entity> result{};

        for (int i = 0;i< validSize;++i)
        {
            result.push_back(m_entitiesDenseArray[i]);
        }

        return result;
    }

    ///Checks if the set contains an entity as an index to any of the components.
    ///@return Returns true if the entity is used as an index to the array otherwise returns false
    bool ContainsEntity(Entity entity)
    {
        return (GetComponentIndex(entity) != -1);
    }

    void Clear()
    {
        //TODO handle this
    }

private:
    //std::array<ComponentType,MAX_ENTITIES> m_componentDenseArray{};
    //std::array<Entity ,MAX_ENTITIES> m_entitiesDenseArray{} ;
    //std::array<int,MAX_ENTITIES> m_indexesSparseArray{};

    ComponentType* m_componentDenseArray;
    Entity* m_entitiesDenseArray;
    int* m_indexesSparseArray;
};



#endif //CROW_COMPONENTSPARSESET_H
