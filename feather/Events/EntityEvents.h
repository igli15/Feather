//
// Created by Igli milaqi on 29/03/2020.
//

#ifndef CROW_ENTITYEVENTES_H
#define CROW_ENTITYEVENTES_H


#include "EventQueue/Event.h"
#include "Types.h"

class OnEntityDestroyedEvent : public Event {

public:
    Entity entity;

    explicit OnEntityDestroyedEvent(Entity pEntity) : entity(pEntity)
    {

    }

};


#endif //CROW_ENTITYEVENTES_H
