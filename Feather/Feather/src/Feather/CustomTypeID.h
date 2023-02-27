//
// Created by Igli milaqi on 04/03/2020.
//

#ifndef CROW_CUSTOMTYPEID_H
#define CROW_CUSTOMTYPEID_H

#include <numeric>


///Create a custom id for every TypeDummy
///For example if you give it one "TypeDummy" every "Type" that gets the index starts from 0 amd goes up.
///Useful for generating type ids without the need of inheritance.
///If you need a new seed of types just provide a new type dummy.
template <typename TypeDummy>
class CustomTypeID {

private:
    inline static std::size_t m_nextIndex = 0;

public:
    template<typename Type>
    inline static const std::size_t index = m_nextIndex++;
};


#endif //CROW_CUSTOMTYPEID_H
