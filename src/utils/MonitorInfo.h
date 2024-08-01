#pragma once

#include <Windows.h>

class MonitorInfo {
public:
    ~MonitorInfo();
    MonitorInfo();

    int width() const;
    int height() const;

private:
    HDC m_handle;
};

