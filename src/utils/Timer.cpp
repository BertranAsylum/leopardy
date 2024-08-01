#include "Timer.h"

Timer::~Timer()
{}

Timer::Timer()
{
    reset();
}

void Timer::reset()
{
    m_start = std::chrono::system_clock::now();
}

std::chrono::duration<double, std::milli> Timer::elapsed() const
{
    const auto now = std::chrono::system_clock::now();
    return now - m_start;
}
