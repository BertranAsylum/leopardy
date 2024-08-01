#pragma once

#include "serializers/PrimitiveSerializer.h"

#include <map>
#include <iostream>

template <typename K, typename V>
std::ostream &operator<<(std::ostream &s, const std::map<K, V> &m)
{
    s << bytes(static_cast<size_t>(m.size()));
    for (const auto &e : m) {
        if (std::is_fundamental_v<K>)
            s << bytes(e.first);
        else
            s << e.first;

        if (std::is_fundamental_v<V>)
            s << bytes(e.second);
        else
            s << e.second;
    }
    return s;
}

template <typename K, typename V>
std::istream &operator>>(std::istream &s, std::map<K, V> &m)
{
    size_t size = 0;
    s >> bytes(size);
    for (size_t i = 0; i < size; ++i) {
        K key;
        V value;

        if (std::is_fundamental_v<K>)
            s >> bytes(key);
        else
            s >> key;

        if (std::is_fundamental_v<V>)
            s >> bytes(value);
        else
            s >> value;

        m.insert({key, value});
    }
    return s;
}
