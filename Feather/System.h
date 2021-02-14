//
// Created by Igli milaqi on 16/02/2020.
//

#ifndef CROW_SYSTEM_H
#define CROW_SYSTEM_H

#include <set>
#include "Types.h"


class World;

///The base class for all the systems
///Provides virtual functions such as OnCreate,Init,Update,Render and PreRender.
///It contains a set of entities which are the entities this sytems will run on (if any EntitySignature was provided to the system, if not set will be empty).
class System {

public:
    std::set<Entity> m_entities;
    World* world;
    bool enabled = true;

    //Called on system creation. be aware
    virtual void OnCreate()
    {

    }
    virtual void Init()
    {

    }

    virtual void Update(float dt)
    {

    }

    virtual void Render()
    {

    }

    virtual void PreRender()
    {

    }

    virtual void OnEnable()
    {

    }

    virtual void OnDisable()
    {

    }

};


#endif //CROW_SYSTEM_H
