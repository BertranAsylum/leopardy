#include "Socket.h"

#include "utils/NetworkAddress.h"

#include <cassert>
#include <ws2tcpip.h>

using namespace Network;

std::wstring sockLastError()
{
    wchar_t *errorMessage = nullptr;
    FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                   nullptr, WSAGetLastError(),
                   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                   reinterpret_cast<LPWSTR>(&errorMessage), 0, nullptr);

    if (errorMessage) {
        return errorMessage;
    }
    return L"Internal socket error";
}

Socket::~Socket()
{
    if (m_socket != INVALID_SOCKET) {
        closesocket(m_socket);
    }
    WSACleanup();
}

Socket::Socket()
{
    WSADATA wsaData;
    std::ignore = WSAStartup(MAKEWORD(2, 2), &wsaData);
}

bool Socket::connect(const std::wstring &address)
{
    m_error.clear();
    const NetworkAddress addr(address);
    if (!addr.valid()) {
        m_error = L"Invalid address " + address + L", expect [host]:[port]";
        return false;
    }

    addrinfo *addrinfoRes = nullptr;
    addrinfo addrinfoHints = {};
    addrinfoHints.ai_family = AF_UNSPEC;
    addrinfoHints.ai_socktype = SOCK_STREAM;
    addrinfoHints.ai_protocol = IPPROTO_TCP;

    const auto getaddrRes = ::getaddrinfo(addr.host(), addr.port(), &addrinfoHints, &addrinfoRes);
    if (getaddrRes != 0) {
        m_error = L"Can't resolve host name from " + address;
        return false;
    }

    for (auto *a = addrinfoRes; a != nullptr; a = a->ai_next) {
        m_error.clear();
        m_socket = socket(a->ai_family, a->ai_socktype, a->ai_protocol);
        if (m_socket == INVALID_SOCKET) {
            m_error = sockLastError();
            break;
        }

        const auto connectRes = ::connect(m_socket, a->ai_addr, static_cast<int>(a->ai_addrlen));
        if (connectRes == SOCKET_ERROR) {
            m_error = sockLastError();
            closesocket(m_socket);
            m_socket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    ::freeaddrinfo(addrinfoRes);
    return (m_socket != INVALID_SOCKET);
}

int Socket::poll(int msec)
{
    assert(m_socket != INVALID_SOCKET);
    m_error.clear();
    WSAPOLLFD pollfd{
        .fd = m_socket,
        .events = POLLRDNORM,
        .revents = 0
    };

    const auto res = WSAPoll(&pollfd, 1, msec);
    if (res < 0) {
        m_error = sockLastError();
    }
    return res;
}

int Socket::send(const char *data, int size)
{
    assert(m_socket != INVALID_SOCKET);
    m_error.clear();
    const auto res = ::send(m_socket, data, size, 0);
    if (res == SOCKET_ERROR) {
        m_error = sockLastError();
    }
    return res;
}

int Socket::recv(char *buffer, int size)
{
    m_error.clear();
    int received = 0;
    while (received < size) {
        auto pollRes = 0;
        if ((pollRes = poll(1000)) > 0) {
            auto recvRes = 0;
            if ((recvRes = ::recv(m_socket, buffer + received, size - received, 0)) > 0) {
                received += recvRes;
            }
            else if (recvRes < 0) {
                m_error = sockLastError();
                return recvRes;
            }
        }
        else {
            return pollRes;
        }
    }
    return received;
}

std::wstring Socket::error() const
{
    return m_error;
}
