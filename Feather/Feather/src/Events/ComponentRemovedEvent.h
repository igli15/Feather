//
// Created by Igli milaqi on 10/04/2020.
//

#ifndef CROW_COMPONENTREMOVEDEVENT_H
#define CROW_COMPONENTREMOVEDEVENT_H


#include "../EventQueue/Event.h"
#include "../Feather/Types.h"

template <typename T>
class ComponentRemovedEvent : public Event {

public:
    Entity entity;
    T component;

    ComponentRemovedEvent(Entity pEntity,T pComponent) : entity(pEntity),component(pComponent)
    {

    }

};


#endif //CROW_COMPONENTREMOVEDEVENT_H
