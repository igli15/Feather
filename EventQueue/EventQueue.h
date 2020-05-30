//
// Created by Igli milaqi on 13/03/2020.
//

#ifndef CROW_EVENTQUEUE_H
#define CROW_EVENTQUEUE_H


#include "MemberFunctionHandler.h"
#include <list>
#include <map>
#include <typeindex>

typedef std::list<MemberFunctionBase*> HandlerList;

///EventQueue class allows the user to publish and subscribe to events.
class EventQueue {

public:

    ///singelton instance for the event queue.
    static EventQueue& Instance();

    ///Publishes an event of a certain type "EventType".
    ///@param event the event which will be published.
    template <typename EventType>
    void Publish(EventType* event)
    {
        HandlerList * handlers = m_subscribers[typeid(EventType)];

        if (handlers == nullptr)
        {
            return;
        }

        for (auto & handler : *handlers)
        {
            if (handler != nullptr) {
                handler->Execute(event);
            }
        }

        delete event;
    }


    ///Subscribes to an event by providing the method callback that will be thrown.
    ///e.g if class "Foo" is listening for a event "TestEvent" and wants to have a callback "Foo::Callback()".
    ///The callback has to have the event type as a parameter so it should be "Foo::Callback(TestEvent* event)".
    ///Then subscribing is EventQueue.Subscribe(FooInstance,Foo::Callback);
    template<class T, class EventType>
    void Subscribe(T * instance, void (T::*memberFunction)(EventType *))
    {
        HandlerList * handlers = m_subscribers[typeid(EventType)];


        if (handlers == nullptr)
        {
            handlers = new HandlerList();
            m_subscribers[typeid(EventType)] = handlers;
        }

        handlers->push_back(new MemberFunctionHandler<T, EventType>(instance, memberFunction));
    }

private:
    static EventQueue* m_instance;
    std::map<std::type_index,HandlerList*> m_subscribers;
};


#endif //CROW_EVENTQUEUE_H
