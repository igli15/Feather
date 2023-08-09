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
		//update all entities with a position and gravity component
        world->ForEach<Position, Gravity>([&](Entity e, Position &position, Gravity &gravity) {
            position.y += gravity.gravityValue;
			std::cout <<"Current entity y positon: " << position.y << std::endl;
        });

		//get all entities which are below "0" y value
        std::vector<Entity> entities = world->FindEntities<Position>([&](Entity e, Position &position) {
            return (position.y <= 0);
        });

		//detroy all entities that were returned from above 
        for (Entity e : entities)
        {
			std::cout << "destroying Entity"<< std::endl;
            world->DestroyEntity(e);
        }
    }

};

int main()
{
	//create feather's core registires
    ComponentRegistry* componentRegistry = new ComponentRegistry();
    SystemRegistry* systemRegistry = new SystemRegistry();
    EntityRegistry* entityRegistry = new EntityRegistry();

	//create a new world and initialize it 
    World* world = new World();
    world->Init(systemRegistry,entityRegistry,componentRegistry);

	//Allocate memory for components if left empty it will allocate for MAX_ENTITIES
    componentRegistry->AllocateComponentSet<Position>();

	//We can also allocate for as much as we need 
    componentRegistry->AllocateComponentSet<Gravity>(10);

	//allocate memory for the system
    systemRegistry->AllocateSystem<GravitySystem>();

	//register a system to a world
    world->RegisterSystem<GravitySystem>();

	//We can set a filter so that the system gets the entities with these components automatically (this is optional)
    world->SetSystemSignature<GravitySystem,Position,Gravity>();

	//create a entity
    EntityHandle entity = world->CreateEntity();

	//add our components
    entity.AddComponent<Position>(Position{0.0f,9000});
    entity.AddComponent<Gravity>(Gravity{-9.18f});

	//fake game loop
	while (true)
	{
		world->ClearEntityGarbage();
		world->UpdateAllSystems(0.01f);
	}

    return 0;
}

