//
// Created by Igli milaqi on 16/02/2020.
//

#include "World.h"
#include "EntityHandle.h"
#include "../Events/EntityEvents.h"
#include "System.h"

void World::Init(SystemRegistry* systemRegistry,EntityRegistry* entityRegistry,ComponentRegistry* componentRegistry)
{
    m_componentRegistry = componentRegistry;
    m_entityRegistry = entityRegistry;
    m_systemRegistry = systemRegistry;

}

EntityHandle World::CreateEntity()
{
    return {m_entityRegistry->CreateEntity(), this};
}

void World::InternalDestroyEntity(Entity entity)
{
    m_entityRegistry->DestroyEntity(entity);
    m_componentRegistry->OnEntityDestroyed(entity);
    m_systemRegistry->OnEntityDestroyed(entity);
}

void World::InitAllSystems()
{
    for (int i = 0; i < m_allRegisteredSystems.size(); ++i)
    {
        m_allRegisteredSystems[i]->Init();
    }
}

void World::UpdateAllSystems(float dt)
{
    for (int i = 0; i < m_allRegisteredSystems.size(); ++i)
    {
        System* system = m_allRegisteredSystems[i];

        if(system->enabled) system->Update(dt);
    }
}

void World::RenderAllSystems()
{
    for (int i = 0; i < m_allRegisteredSystems.size(); ++i)
    {
        System* system = m_allRegisteredSystems[i];

        if(system->enabled) system->Render();
    }
}

void World::Build()
{

}


void World::DestroyEntity(Entity entity)
{
    m_entityGarbage.push_back(entity);
    EventQueue::Instance().Publish(new OnEntityDestroyedEvent(entity));
}

void World::ClearEntityGarbage()
{
    for (int i = m_entityGarbage.size() - 1; i >= 0; i--)
    {
        InternalDestroyEntity(m_entityGarbage[i]);
    }

    m_entityGarbage.clear();
}

void World::PreRenderAllSystems()
{
    for (int i = 0; i < m_allRegisteredSystems.size(); ++i)
    {
        System* system = m_allRegisteredSystems[i];

        if(system->enabled) system->PreRender();
    }
}

void World::ResetWorld()
{
    m_entityRegistry->ReturnAllEntities();
    m_allRegisteredSystems.clear();
    m_systemRegistry->ResetAllSystems();
    m_componentRegistry->RemoveAllComponents();

    Build();
    InitAllSystems();
}



