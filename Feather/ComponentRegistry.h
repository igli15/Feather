//
// Created by Igli milaqi on 15/02/2020.
//

#ifndef CROW_COMPONENTREGISTRY_H
#define CROW_COMPONENTREGISTRY_H

#include <unordered_map>
#include "Types.h"
//#include "ComponentArray.h"
#include "ComponentSparseSet.h"



///"ComponentRegistry" Keeps track of all "ComponentArrays" and notifies them if an entity got removed from the world
///All the ComponentArrays pointers are stored in an array and the location of the arrays is their type ID.
class ComponentRegistry
{

public:

    template<typename T>
    void AllocateComponentSet();

    ///Finds an component array of Type "T" and updates it correctly with the new entity and component
    ///@param entity the entity which the component will be added to.
    ///@param component the component that's going to be added.
    ///@return a pointer to the added component
    template<typename T>
    T *AddComponent(Entity entity, T component);

    template<typename T>
    void RemoveComponent(Entity entity);

    ///Finds an component array of Type "T" and get the component
    ///@param entity the entity which the component will be taken from
    template<typename T>
    T &GetComponent(Entity entity);


    ///Finds an component array of Type "T" and get the component pointer
    ///@param entity the entity which the component pointer will be searched for
    template<typename T>
    T *GetComponentPtr(Entity entity);

    ///Notifies all the active component arrays if an Entity got destroyed
    ///and if so update them accordingly
    void OnEntityDestroyed(Entity entity)
    {
        for (auto &pair: m_componentSetsMap) {
            pair.second->OnEntityDestroyed(entity);
        }
    }

    ///Get an component set of a specified type "T"
    template<typename T>
    ComponentSparseSet<T> *GetComponentSet();

private:

    ///All the component set pointers
    std::unordered_map<int, IComponentSet *> m_componentSetsMap;

};
template<typename T>
void ComponentRegistry::AllocateComponentSet()
{
    auto iterator = m_componentSetsMap.find(ComponentIDGenerator::index < T > );

    if (iterator == m_componentSetsMap.end()) {
        ComponentSparseSet<T> *array = new ComponentSparseSet<T>;
        m_componentSetsMap.insert(iterator, std::make_pair(ComponentIDGenerator::index < T > , array));
    } else {
       std::cout<<"Component is already registered.... Skipping"<<std::endl;
    }
}

template<typename T>
ComponentSparseSet<T> *ComponentRegistry::GetComponentSet()
{
    //TODO add assertion here.
    return static_cast<ComponentSparseSet<T> *>(m_componentSetsMap[ComponentIDGenerator::index < T >]);
}

template<typename T>
T *ComponentRegistry::AddComponent(Entity entity, T component)
{
    return GetComponentSet<T>()->AddComponentData(entity, component);
}

template<typename T>
void ComponentRegistry::RemoveComponent(Entity entity)
{
    GetComponentSet<T>()->RemoveComponentData(entity);
}

template<typename T>
T &ComponentRegistry::GetComponent(Entity entity)
{
    return GetComponentSet<T>()->GetComponentData(entity);
}

template<typename T>
T *ComponentRegistry::GetComponentPtr(Entity entity)
{
    ComponentSparseSet<T> *arrayPtr = GetComponentSet<T>();

    if (arrayPtr == nullptr) return nullptr;

    return arrayPtr->GetComponentPtr(entity);
}


#endif //CROW_COMPONENTREGISTRY_H
