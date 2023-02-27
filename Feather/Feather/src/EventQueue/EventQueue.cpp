//
// Created by Igli milaqi on 13/03/2020.
//

#include "EventQueue.h"

EventQueue* EventQueue::m_instance = nullptr;

EventQueue& EventQueue::Instance()
{
    if(m_instance == nullptr)
    {
        m_instance = new EventQueue();
    }

    return *m_instance;
}
