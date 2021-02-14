//
// Created by Igli milaqi on 14/02/2020.
//

#include "EntityRegistry.h"


EntityRegistry::EntityRegistry()
{
    for (Entity e = 1; e < MAX_ENTITIES; ++e)
    {
        m_entityQueue.push(e);
    }

}

Entity EntityRegistry::CreateEntity()
{
    Entity id = m_entityQueue.front();
    m_entityQueue.pop();
    m_activeEntities++;

    return id;
}

void EntityRegistry::DestroyEntity(Entity e)
{
    m_signatures[e].reset(); //reset the bitset
    m_entityQueue.push(e); //put it back at the queue
    m_activeEntities--;
}

void EntityRegistry::SetSignature(Entity e, EntitySignature s)
{
    m_signatures[e]  = s;
}

EntitySignature EntityRegistry::GetSignature(Entity e)
{
    return m_signatures[e];
}

void EntityRegistry::ReturnAllEntities()
{
    for (int i = 1; i < m_activeEntities; ++i)
    {
        m_signatures[i].reset();
        m_entityQueue.push(i);
    }


    m_activeEntities = 0;
}

