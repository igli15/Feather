//
// Created by Igli milaqi on 14/02/2020.
//

#ifndef CROW_TYPES_H
#define CROW_TYPES_H

#include <bitset>
#include "CustomTypeID.h"

///Entity is just an std::uint32
using Entity = std::uint32_t;

///Entity 0 is invalid the entities start from 1.
const Entity InvalidEntity = 0;

///Type dummy used as a seed to generate all component ids
struct ComponentTypeDummy
{

};

///Type dummy used as a seed to generate all component ids
struct SystemTypeDummy
{

};

using ComponentType = std::uint32_t;

///custom type id generator for all component types
using ComponentIDGenerator = CustomTypeID<ComponentTypeDummy>;

///custom type id generator for all component types
using SystemIDGenerator = CustomTypeID<SystemTypeDummy>;

///max number of entities allowed in a world
const int MAX_ENTITIES = 50000;

///max number of component allowed to be attached to a single entity
const int MAX_COMPONENTS = 32;

///Entity signature is just a std::bitset<MAX_COMPONENTS>
///when a component of ID 2 is added 2nd bitset is marked active and when removed is marked inactive
using EntitySignature = std::bitset<MAX_COMPONENTS>;


#endif //CROW_TYPES_H
