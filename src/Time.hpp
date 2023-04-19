#pragma once 
#include <chrono>

class Time {
    std::chrono::time_point<std::chrono::steady_clock> m_start;
    u32 m_fps {};
    u32 m_frameCount {};

    float m_delta {};
    float m_nextSecond {1.f};
    float m_elapsed {};
    
public:
    Time() {
        m_start = std::chrono::steady_clock::now();
    }
    
    float getElapsed() {
        return m_elapsed;
    }

    float getDelta() const {
        return m_delta;
    }

    void update() {
        float elapsedSeconds = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now()-m_start).count();
        m_delta = m_elapsed-elapsedSeconds;
        m_elapsed = elapsedSeconds;

        if (elapsedSeconds >= m_nextSecond) {
            m_fps = m_frameCount;
            m_frameCount = 0;
            m_nextSecond = elapsedSeconds+1.f;
        }
        
        m_frameCount++;
    }
};