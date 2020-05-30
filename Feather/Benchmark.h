//
// Created by Igli milaqi on 28/05/2020.
//

#ifndef CROW_BENCHMARK_H
#define CROW_BENCHMARK_H

#include <cstdio>
#include <ctime>
#include <chrono>

class Timer
{

public:
    void Begin()
    {
        m_startTimerPoint = std::chrono::high_resolution_clock::now();
    };

    double End()
    {
        auto endTimerPoint = std::chrono::high_resolution_clock::now();
        long long startTime = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimerPoint).time_since_epoch().count();
        long long endTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimerPoint).time_since_epoch().count();
        microSeconds = endTime - startTime;
        milliSeconds = microSeconds * 0.001;
        return milliSeconds;
    }

    long long microSeconds = 0;
    double milliSeconds = 0;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimerPoint;
};


#endif //CROW_BENCHMARK_H
