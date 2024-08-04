#pragma once

#include <chrono>

using namespace std::chrono_literals;

class ElapsedTimer {
public:
    ~ElapsedTimer();
    ElapsedTimer();

    void reset();
    std::chrono::duration<double, std::milli> elapsed() const;

private:
    std::chrono::time_point<std::chrono::system_clock> m_start;
};

