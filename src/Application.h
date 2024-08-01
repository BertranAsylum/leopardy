#pragma once

#include <queue>
#include <mutex>
#include <functional>

class Application {
public:
    virtual ~Application() = default;
    Application();

    static int exec();
    static void terminate();
    static void push(const std::function<void()> &event);

protected:
    virtual void loop() = 0;

private:
    std::mutex m_mutex;
    std::atomic<bool> m_running = false;
    std::queue<std::function<void()>> m_events;
};
