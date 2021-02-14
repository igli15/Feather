//
// Created by Igli milaqi on 30/05/2020.
//
#include "Feather/World.h"
#include "Feather/EntityHandle.h"
#include <iostream>

struct Position
{
    float x = 0.0f;
    float y = 0.0f;
};

struct Gravity
{
    float gravityValue = 9.8f;
};

class GravitySystem : public System
{
    void Update(float dt) override
    {
        world->ForEach<Position, Gravity>([&](Entity e, Position &position, Gravity &gravity) {
            position.y += gravity.gravityValue;
        });

        std::vector<Entity> entities = world->FindEntities<Position>([&](Entity e, Position &position) {
            return (position.y <= 0);
        });

        for (Entity e : entities)
        {
            world->DestroyEntity(e);
        }
    }

};

int main()
{
    ComponentRegistry* componentRegistry = new ComponentRegistry();
    SystemRegistry* systemRegistry = new SystemRegistry();
    EntityRegistry* entityRegistry = new EntityRegistry();

    World* world = new World();
    world->Init(systemRegistry,entityRegistry,componentRegistry);


    componentRegistry->AllocateComponentSet<Position>();
    componentRegistry->AllocateComponentSet<Gravity>();

    systemRegistry->AllocateSystem<GravitySystem>();

    world->RegisterSystem<GravitySystem>();

    world->SetSystemSignature<GravitySystem,Position,Gravity>();

    EntityHandle entity = world->CreateEntity();

    entity.AddComponent<Position>(Position{0.0f,9.0f});
    entity.AddComponent<Gravity>(Gravity{-9.18f});


    world->UpdateAllSystems(0.01f);

    return 0;
}

