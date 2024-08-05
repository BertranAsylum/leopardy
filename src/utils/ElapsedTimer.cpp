#include "ElapsedTimer.h"

ElapsedTimer::~ElapsedTimer() = default;

ElapsedTimer::ElapsedTimer()
{
    reset();
}

void ElapsedTimer::reset()
{
    m_start = std::chrono::system_clock::now();
}

std::chrono::duration<double, std::milli> ElapsedTimer::elapsed() const
{
    const auto now = std::chrono::system_clock::now();
    return now - m_start;
}
