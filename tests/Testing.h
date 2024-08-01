#pragma once

#include "TestException.h"
#include "TestFailString.h"

#include <array>
#include <functional>
#include <iostream>

namespace Testing {
using TestFuncProto = std::function<void()>;

template <typename... Tests>
int run(Tests... tests)
{
    int passed = 0;
    std::array<TestFuncProto, sizeof...(tests)> funcs = {tests...};
    for (const auto &f : funcs) {
        try {
            f();
        }
        catch (const Private::TestException &e) {
            std::cout << "    Failed: " << e.where() << ":" << std::endl;
            std::cout << "        " << e.what() << std::endl;
            continue;
        }
        ++passed;
    }
    std::cout << "    Result: " << passed << "/" << sizeof...(tests) << " subtests passed"
        << std::endl;
    return passed - sizeof...(tests);
}

template <typename T1, typename T2>
void eq(
    const std::string &context,
    const std::string &argName1,
    T1 argVal1,
    const std::string &argName2,
    T2 argVal2)
{
    if (argVal1 != argVal2) {
        throw Private::TestException{
            context, Private::failString(__FUNCTION__, argName1, argVal1, argName2, argVal2)
        };
    }
}

template <typename T1, typename T2>
void ne(
    const std::string &context,
    const std::string &argName1,
    T1 argVal1,
    const std::string &argName2,
    T2 argVal2)
{
    if (argVal1 == argVal2) {
        throw Private::TestException{
            context, Private::failString(__FUNCTION__, argName1, argVal1, argName2, argVal2)
        };
    }
}

template <typename T1, typename T2>
void gt(
    const std::string &context,
    const std::string &argName1,
    T1 argVal1,
    const std::string &argName2,
    T2 argVal2)
{
    if (!(argVal1 > argVal2)) {
        throw Private::TestException{
            context, Private::failString(__FUNCTION__, argName1, argVal1, argName2, argVal2)
        };
    }
}

template <typename T1, typename T2>
void ge(
    const std::string &context,
    const std::string &argName1,
    T1 argVal1,
    const std::string &argName2,
    T2 argVal2)
{
    if (!(argVal1 >= argVal2)) {
        throw Private::TestException{
            context, Private::failString(__FUNCTION__, argName1, argVal1, argName2, argVal2)
        };
    }
}

template <typename T1, typename T2>
void lt(
    const std::string &context,
    const std::string &argName1,
    T1 argVal1,
    const std::string &argName2,
    T2 argVal2)
{
    if (!(argVal1 < argVal2)) {
        throw Private::TestException{
            context, Private::failString(__FUNCTION__, argName1, argVal1, argName2, argVal2)
        };
    }
}

template <typename T1, typename T2>
void le(
    const std::string &context,
    const std::string &argName1,
    T1 argVal1,
    const std::string &argName2,
    T2 argVal2)
{
    if (!(argVal1 <= argVal2)) {
        throw Private::TestException{
            context, Private::failString(__FUNCTION__, argName1, argVal1, argName2, argVal2)
        };
    }
}

template <typename Func>
void thrw(const std::string &context, const std::string &callStr, Func func)
{
    try {
        func();
    }
    catch (...) {
        return;
    }
    throw Private::TestException{context, Private::failString(__FUNCTION__, callStr)};
}
}

#define TEST_RUN(...) Testing::run(__VA_ARGS__)
#define TEST_CTX std::string(__FUNCTION__) + " at " + std::to_string(__LINE__)

#define TEST_EQ(a1, a2) Testing::eq(TEST_CTX, #a1, a1, #a2, a2)
#define TEST_NE(a1, a2) Testing::ne(TEST_CTX, #a1, a1, #a2, a2)
#define TEST_GT(a1, a2) Testing::gt(TEST_CTX, #a1, a1, #a2, a2)
#define TEST_GE(a1, a2) Testing::ge(TEST_CTX, #a1, a1, #a2, a2)
#define TEST_LT(a1, a2) Testing::lt(TEST_CTX, #a1, a1, #a2, a2)
#define TEST_LE(a1, a2) Testing::le(TEST_CTX, #a1, a1, #a2, a2)
#define TEST_THROW(c) Testing::thrw(TEST_CTX, #c, [=]() { c })
