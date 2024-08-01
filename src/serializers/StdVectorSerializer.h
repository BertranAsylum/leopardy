#pragma once

#include "serializers/PrimitiveSerializer.h"

#include <vector>
#include <iostream>

template <typename T>
std::ostream &operator<<(std::ostream &s, const std::vector<T> &v)
{
    s << bytes(static_cast<size_t>(v.size()));
    for (const auto &e : v) {
        if (std::is_fundamental_v<T>)
            s << bytes(e);
        else
            s << e;
    }
    return s;
}

template <typename T>
std::istream &operator>>(std::istream &s, std::vector<T> &v)
{
    size_t size = 0;
    s >> bytes(size);
    v.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        T value;

        if (std::is_fundamental_v<T>)
            s >> bytes(value);
        else
            s >> value;

        v.push_back(value);
    }
    return s;
}
