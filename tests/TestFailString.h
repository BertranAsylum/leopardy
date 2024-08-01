#pragma once

#include <chrono>
#include <codecvt>
#include <locale>
#include <sstream>

namespace Testing::Private {

template <typename T1, typename T2>
std::string failString(
    const std::string &checkName,
    const std::string &argStr1,
    T1 argVal1,
    const std::string &argStr2,
    T2 argVal2)
{
    std::stringstream stream;
    stream << argStr1 << "(" << argVal1 << ") not " << checkName << " " << argStr2 << "("
           << argVal2 << ")" << std::endl;
    return stream.str();
}

template <>
inline std::string failString<>(
    const std::string &checkName,
    const std::string &argStr1,
    std::wstring argVal1,
    const std::string &argStr2,
    std::wstring argVal2)
{
    static std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return failString(
        checkName, argStr1, converter.to_bytes(argVal1), argStr2, converter.to_bytes(argVal2));
}

template <>
inline std::string failString<>(
    const std::string &checkName,
    const std::string &argStr1,
    const wchar_t *argVal1,
    const std::string &argStr2,
    std::wstring argVal2)
{
    static std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return failString(
        checkName, argStr1, converter.to_bytes(argVal1), argStr2, converter.to_bytes(argVal2));
}

template <>
inline std::string failString<>(
    const std::string &checkName,
    const std::string &argStr1,
    std::wstring argVal1,
    const std::string &argStr2,
    const wchar_t *argVal2)
{
    static std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return failString(
        checkName, argStr1, converter.to_bytes(argVal1), argStr2, converter.to_bytes(argVal2));
}

inline std::string failString(const std::string &checkName, const std::string &argStr)
{
    std::stringstream stream;
    stream << argStr << " not " << checkName << std::endl;
    return stream.str();
}

}
