//
// Created by Igli milaqi on 29/03/2020.
//

#ifndef CROW_COMPONENTADDEDEVENT_H
#define CROW_COMPONENTADDEDEVENT_H


#include "../Feather/Types.h"
#include "../EventQueue/Event.h"

template <typename T>
class ComponentAddedEvent : public Event{

public:
    Entity entity;
    T* component;

    ComponentAddedEvent(Entity pEntity,T* pComponent) : entity(pEntity),component(pComponent)
    {

    }
};


#endif //CROW_COMPONENTADDEDEVENT_H
