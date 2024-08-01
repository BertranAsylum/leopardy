#pragma once

#include <string>

class NetworkAddress {
public:
    NetworkAddress(const std::wstring &address);

    bool valid() const;
    const char *host() const;
    const char *port() const;

private:
    std::string m_host;
    std::string m_port;
};
