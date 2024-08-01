#include "MonitorInfo.h"

MonitorInfo::~MonitorInfo()
{
    ReleaseDC(nullptr, m_handle);
}

MonitorInfo::MonitorInfo()
{
    m_handle = GetDC(nullptr);
}

int MonitorInfo::width() const
{
    return GetDeviceCaps(m_handle, HORZRES);
}

int MonitorInfo::height() const
{
    return GetDeviceCaps(m_handle, VERTRES);
}
