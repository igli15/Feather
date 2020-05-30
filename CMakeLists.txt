cmake_minimum_required(VERSION 3.16)
project(Feather)

set(CMAKE_CXX_STANDARD 14)

include_directories(EventQueue)
include_directories(Events)
include_directories(Feather)

add_executable(Feather
        EventQueue/Event.h
        EventQueue/EventQueue.cpp
        EventQueue/EventQueue.h
        EventQueue/MemberFunctionHandler.cpp
        EventQueue/MemberFunctionHandler.h
        Events/ComponentAddedEvent.cpp
        Events/ComponentAddedEvent.h
        Events/ComponentRemovedEvent.h
        Events/EntityEvents.h
        Feather/Benchmark.h
        Feather/ComponentRegistry.cpp
        Feather/ComponentRegistry.h
        Feather/ComponentSparseSet.cpp
        Feather/ComponentSparseSet.h
        Feather/CustomTypeID.h
        Feather/EntityHandle.cpp
        Feather/EntityHandle.h
        Feather/EntityRegistry.cpp
        Feather/EntityRegistry.h
        Feather/IComponentSet.h
        Feather/Pool.h
        Feather/System.cpp
        Feather/System.h
        Feather/SystemRegistry.cpp
        Feather/SystemRegistry.h
        Feather/Types.h
        Feather/World.cpp
        Feather/World.h
        main.cpp)
