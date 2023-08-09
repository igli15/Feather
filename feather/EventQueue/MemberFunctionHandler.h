//
// Created by Igli milaqi on 13/03/2020.
//

#ifndef CROW_MEMBERFUNCTIONHANDLER_H
#define CROW_MEMBERFUNCTIONHANDLER_H


#include "Event.h"

///Base class for MemberFunctionHandler.
class MemberFunctionBase
{
public:
    ///Executes the callback function
    void Execute(Event* event)
    {
        Call(event);
    }

private:
    virtual void Call(Event* event) = 0;
};


///Wrapper around the callback functions registered for events.
template <class T, class EventType>
class MemberFunctionHandler : public MemberFunctionBase {

public:
    typedef void (T::*MemberFunction)(EventType*);

    MemberFunctionHandler(T * instance, MemberFunction memberFunction) : m_instance{ instance }, m_memberFunction{ memberFunction } {};

    void Call(Event * event) override
    {
        (m_instance->*m_memberFunction)(static_cast<EventType*>(event));
    }

private:
    T * m_instance;
    MemberFunction m_memberFunction;
};


#endif //CROW_MEMBERFUNCTIONHANDLER_H
