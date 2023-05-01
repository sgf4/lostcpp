#pragma once 
#include <chrono>
#include "Integers.hpp"

class Time {
    std::chrono::time_point<std::chrono::steady_clock> m_start;
    
    u32 m_frameCount {};
    float m_nextSecond {1.f};

    
public:
    
    float elapsed {};
    float delta {};
    u32 fps {};

    Time() {
        m_start = std::chrono::steady_clock::now();
    }

    void update() {
        float elapsedSeconds = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now()-m_start).count();
        delta = elapsed-elapsedSeconds;
        elapsed = elapsedSeconds;

        if (elapsedSeconds >= m_nextSecond) {
            fps = m_frameCount;
            m_frameCount = 0;
            m_nextSecond = elapsedSeconds+1.f;
        }
        
        m_frameCount++;
    }
};