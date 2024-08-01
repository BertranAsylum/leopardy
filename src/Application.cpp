#include "Application.h"

#include <cassert>

static Application *instance = nullptr;

Application::Application()
{
    assert(instance == nullptr);
    instance = this;
}

int Application::exec()
{
    instance->m_running = true;
    while (instance->m_running) {
        instance->loop();
        for (; !instance->m_events.empty(); instance->m_events.pop()) {
            (instance->m_events.front())();
        }
    }
    return 0;
}

void Application::terminate()
{
    instance->m_running = false;
}

void Application::push(const std::function<void()> &event)
{
    std::lock_guard lock(instance->m_mutex);
    instance->m_events.push(event);
}
