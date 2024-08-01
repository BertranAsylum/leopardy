#pragma once

#include <exception>
#include <string>

namespace Testing::Private {

class TestException : public std::exception
{
public:
    TestException(const std::string &where, const std::string &what)
        : m_where(where), m_what(what)
    {}

    const char *where() const noexcept { return m_where.c_str(); }

    const char *what() const noexcept override { return m_what.c_str(); }

private:
    std::string m_where;
    std::string m_what;
};

}
