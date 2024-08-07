#pragma once

#include <chrono>

using namespace std::chrono_literals;

class Constants {
public:
    static std::chrono::duration<double, std::milli> tryAnswerDelay() { return 3s; }
    static std::chrono::duration<double, std::milli> answeringTime() { return 10s; }
};
