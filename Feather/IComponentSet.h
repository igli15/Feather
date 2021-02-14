//
// Created by Igli milaqi on 25/05/2020.
//

#ifndef CROW_ICOMPONENTSET_H
#define CROW_ICOMPONENTSET_H

///This is the base class of all ComponentSets.
///It is here so that the ComponentRegistry stores a reference to all ComponentArrays and some abstract method implementations.
class IComponentSet {

public:
    virtual ~IComponentSet() = default;

    ///Called when an entity is destroyed from the world.
    ///@param entity The entity which is about to be destroyed.
    virtual void OnEntityDestroyed(Entity entity) = 0;

    ///Returns a std::vector of all entities that the components in the array are attached to.
    virtual std::vector<Entity> GetEntities() = 0;

    virtual void Clear() = 0;

    ///The active component count.
    size_t validSize = 0;
};

#endif //CROW_ICOMPONENTSET_H
