#pragma once

#include <chrono>

using namespace std::chrono_literals;

class Timer {
public:
    ~Timer();
    Timer();

    void start(const std::chrono::duration<double, std::milli> &msec);
    void stop();
    std::chrono::duration<double, std::milli> remained() const;
    double progress() const;
    bool finished() const;

private:
    std::chrono::time_point<std::chrono::system_clock> m_start;
    std::chrono::duration<double, std::milli> m_durationMsec;
};

