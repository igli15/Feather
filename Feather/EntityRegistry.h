//
// Created by Igli milaqi on 14/02/2020.
//

#ifndef CROW_ENTITYREGISTRY_H
#define CROW_ENTITYREGISTRY_H

#include <queue>
#include <array>
#include "Types.h"

///"EntityRegistry" manages all the entities.
///It is responsible for creating/destroying and storing the signature of the entities.
///EntitySignature is a bitset which represents all the attached components to the entity.
///For example if a entity contains an component with ID 2 the 2nd bit with be marked active.
///Entity is just an std::uint32 and all the entities are stored in a queue.
class EntityRegistry {

public:
    EntityRegistry();

    ///Creates an entity
    ///@return Returns the entity that was just created
    Entity CreateEntity();

    ///Destroy an entity and put it back on the queue
    ///@param e Entity to destroy
    void DestroyEntity(Entity e);

    ///Set the signature of an entity
    ///@param e Entity which signature will be set
    ///@param s The new signature
    void SetSignature(Entity e,EntitySignature s);

    ///Get the entity signature of a specified entity
    ///@param e Entity which signature will be returned
    ///@return The entity's Signature
    EntitySignature GetSignature(Entity e);

    void ReturnAllEntities();

private:
    std::queue<Entity> m_entityQueue{};

    std::array<EntitySignature,MAX_ENTITIES> m_signatures{};

    int m_activeEntities = 0;
};


#endif#endif