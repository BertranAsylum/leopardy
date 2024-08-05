#include "Timer.h"

Timer::~Timer() = default;
Timer::Timer() = default;

void Timer::start(const std::chrono::duration<double, std::milli> &msec)
{
    m_start = std::chrono::system_clock::now();
    m_durationMsec = msec;
}

std::chrono::duration<double, std::milli> Timer::remained() const
{
    const auto elapsed = std::chrono::system_clock::now() - m_start;
    if (elapsed < m_durationMsec) {
        return m_durationMsec - elapsed;
    }
    return 0ms;
}

double Timer::progress() const
{
    return ((m_durationMsec - remained()).count() / m_durationMsec.count());
}

bool Timer::finished() const
{
    return (remained() == 0ms);
}
