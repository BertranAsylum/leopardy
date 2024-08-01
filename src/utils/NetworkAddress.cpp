#include "NetworkAddress.h"

#include <regex>

NetworkAddress::NetworkAddress(const std::wstring &address)
{
    const std::wregex regex(L"(.*):(.*)");
    std::wsmatch match;
    if (std::regex_match(address, match, regex)) {
        if (match.size() == 3) {
            const auto m1 = match[1].str();
            m_host = std::string(m1.begin(), m1.end());

            const auto m2 = match[2].str();
            m_port = std::string(m2.begin(), m2.end());
        }
    }
}

bool NetworkAddress::valid() const
{
    return (!m_host.empty() && !m_port.empty());
}

const char *NetworkAddress::host() const
{
    return m_host.c_str();
}

const char *NetworkAddress::port() const
{
    return m_port.c_str();
}
