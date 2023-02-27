//
// Created by Igli milaqi on 16/02/2020.
//

#ifndef CROW_SYSTEMREGISTRY_H
#define CROW_SYSTEMREGISTRY_H


#include <typeinfo>
#include "System.h"
#include <unordered_map>


///Holds a refence to all the systems.
///Updates system signatures and the entity list for each system when needed.
///Creates and Registers systems.
class SystemRegistry {

public:


    template<typename T>
    T* AllocateSystem()
    {
        std::size_t id = SystemIDGenerator::index<T>;

        if(m_systems.find(id) != m_systems.end())
        {
            //ENGINE_LOG_CRITICAL("System is already allocated");
            throw;
        }

        T* system = new T();
        system->OnCreate();
        m_systems.insert({id,system});
        return system;
    }


    template<typename T>
    T* GetSystem()
    {
        std::size_t id = SystemIDGenerator::index<T>;

        auto iterator = m_systems.find(id);

        if(iterator == m_systems.end())
        {
           // ENGINE_LOG_CRITICAL("System is not allocated");
            throw;
        }

        return static_cast<T*>(iterator->second);
    }

    ///Set the signature of a system
    ///@param signature the new signature.
    template <typename T>
    void SetSignature(EntitySignature signature)
    {
        std::size_t id = SystemIDGenerator::index<T>;

        if(m_systems.find(id) == m_systems.end())
        {
           // ENGINE_LOG_CRITICAL("System is NOT Registered");
            throw;
        }

        m_signatures[id] = signature;
    }

    ///Called when an entity is destroyed from the world.
    ///Erases the entity from the system's set if needed.
    ///@param entity The entity which is about to be destroyed.
    void OnEntityDestroyed(Entity entity)
    {
        for (auto const& pair : m_systems)
        {
            auto const& system = pair.second;

            system->m_entities.erase(entity);
        }
    }

    ///Called when the signature of an entity Has changed.
    ///It checks if the new signature matches the signature of the system and if so it adds it to the set.
    ///@param entity Entity which signature changed
    ///@param signature The new EntitySignature
    void OnEntitySignatureChanged(Entity entity,EntitySignature signature)
    {
        for (auto const& pair : m_systems)
        {
            std::size_t id = pair.first;
            System* system = pair.second;
            EntitySignature systemSignature = m_signatures[id];

            if((signature & systemSignature) == systemSignature)
            {
                system->m_entities.insert(entity);
            }
            else
            {
                system->m_entities.erase(entity);
            }
        }
    }

    void ResetAllSystems()
    {
        for (auto& systemPair : m_systems)
        {
            systemPair.second->m_entities.clear();
        }
    }

private:

    std::unordered_map<std::size_t ,EntitySignature> m_signatures {};
    std::unordered_map<std::size_t,System*> m_systems {};
};


#endif //CROW_SYSTEMREGISTRY_H
