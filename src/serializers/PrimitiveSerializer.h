#pragma once

#include <iostream>

template <typename T>
struct bytes_t {
    T t;
};

template <typename T>
bytes_t<T&> bytes(T &t) { return bytes_t<T&>{t}; }

template <typename T>
bytes_t<const T&> bytes(const T &t) { return bytes_t<const T&>{t}; }

template <typename T>
std::ostream &operator<<(std::ostream &s, bytes_t<T> b)
{
    return s.write(reinterpret_cast<const char*>(&b.t), sizeof(T));
}

template <typename T>
std::istream &operator>>(std::istream &s, bytes_t<T&> b)
{
    return s.read(reinterpret_cast<char*>(&b.t), sizeof(T));
}
