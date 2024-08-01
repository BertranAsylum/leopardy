#pragma once

#include "serializers/PrimitiveSerializer.h"

#include <string>
#include <iostream>

inline std::ostream &operator<<(std::ostream &s, const std::wstring &ws)
{
    const auto size = static_cast<size_t>(ws.size() * (sizeof(wchar_t) / sizeof(char)));
    const auto *data = reinterpret_cast<const char*>(ws.data());

    s << bytes(size);
    s.write(data, static_cast<std::streamsize>(size));
    return s;
}

inline std::istream &operator>>(std::istream &s, std::wstring &ws)
{
    size_t size = 0;
    s >> bytes(size);

    ws.resize(size / (sizeof(wchar_t) / sizeof(char)));
    s.read(reinterpret_cast<char*>(ws.data()), static_cast<std::streamsize>(size));
    return s;
}
