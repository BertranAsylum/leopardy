#pragma once

#include <winsock2.h>
#include <string>
#include <chrono>

using namespace std::chrono_literals;

namespace Network {
class Socket {
public:
    ~Socket();
    Socket();

    bool connect(const std::wstring &address);
    int poll(int msec);
    int send(const char *data, int size);
    int recv(char *buffer, int size);
    std::wstring error() const;

private:
    SOCKET m_socket = INVALID_SOCKET;
    std::wstring m_error;
};
}
