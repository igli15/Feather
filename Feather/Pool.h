//
// Created by Igli milaqi on 28/05/2020.
//

#ifndef CROW_POOL_H
#define CROW_POOL_H

#include <cstdlib>
#include "Types.h"
#include "../Debug/Debug.h"

//Work in progress pool class
//It stores a max nr of elements and pools them. It holds a reference to the holes of the packed array and fills them when it can.
//It will iterate at complexity O(activeCount + holes) and the get complexity is O(1).

//just an interface
class IPool
{

};

//TODO this works but, maybe find a better wey then allocating 3 arrays
template<typename T>
class Pool
{

public:
    void Allocate(size_t maxSize)
    {
        m_dataArray = (T*)(calloc(maxSize, sizeof(T)));
        m_activeFlags = (bool*)(calloc(maxSize,sizeof(bool)));
        m_nextValidIndexes = (int*)(calloc(maxSize, sizeof(int)));
    }

    size_t count = 0;

    T& GetNewData()
    {
         size_t currentCount = count;

         count++;

         if(m_validIndexesCount > 0)
         {
             if(m_emptyHoles>0) m_emptyHoles--;

             int index = m_nextValidIndexes[m_validIndexesCount - 1 ];
             m_validIndexesCount--;
             m_activeFlags[index] = true;
             return m_dataArray[index];

         } else
         {
             m_activeFlags[currentCount] = true;
             return m_dataArray[currentCount];
         }

    }

    void ReturnData(const T& data)
    {
        size_t index = GetIndexOfData(data);

        if(index <0 || index >= (count + m_emptyHoles))
        {
            ENGINE_LOG_CRITICAL("Bad Pool Access!");
            throw;
        }

        if(index != count + m_emptyHoles -1)
        {
            m_emptyHoles++;

            int vi = m_validIndexesCount;
            m_validIndexesCount++;
            m_nextValidIndexes[vi] = index;
        }

        m_activeFlags[index] = false;

        count--;
    }

    void ForEach(typename std::common_type<std::function<void(T&)>>::type func)
    {
        ENGINE_LOG(m_emptyHoles);
        for (int i = 0; i < (count + m_emptyHoles); ++i)
        {
            if(m_activeFlags[i])
            {
                func(m_dataArray[i]);
            }
        }
    }

    size_t GetIndexOfData(const T& data)
    {
        return (&data - &m_dataArray[0]);
    }

private:


    unsigned int m_emptyHoles = 0;
    T* m_dataArray = nullptr;
    int* m_nextValidIndexes = nullptr;
    size_t m_validIndexesCount = 0;
    bool* m_activeFlags = nullptr;
};

#endif //CROW_POOL_H
