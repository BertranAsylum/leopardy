#include "Channel.h"

using namespace Network;

Channel::~Channel()
{
    m_listen = false;
    if (m_listenThread.joinable()) {
        m_listenThread.join();
    }
}

bool Channel::connect(const std::wstring &address)
{
    m_error.clear();
    if (!m_socket.connect(address)) {
        m_error = m_socket.error();
        return false;
    }

    m_listen = true;
    m_listenThread = std::thread([this]()
    {
        if (!listen()) {
            for (const auto &c : m_errorCallbacks) {
                c(m_error);
            }
        }
    });
    return true;
}

bool Channel::sendMessage(const Message &msg)
{
    m_error.clear();
    const auto &data = msg.data();
    const auto size = static_cast<int>(data.size());

    if (m_socket.send(reinterpret_cast<const char*>(&size), sizeof(size)) > 0) {
        if (m_socket.send(data.c_str(), static_cast<int>(data.size())) > 0) {
            return true;
        }
    }

    m_error = m_socket.error();
    return false;
}

void Channel::onMessage(const MessageCallback &callback)
{
    m_messageCallbacks.push_back(callback);
}

void Channel::onError(const ErrorCallback &callback)
{
    m_errorCallbacks.push_back(callback);
}

std::wstring Channel::error() const
{
    return m_error;
}

bool Channel::listen()
{
    m_error.clear();
    while (m_listen) {
        auto size = 0;
        auto sizeRecvRes = 0;
        if ((sizeRecvRes = m_socket.recv(reinterpret_cast<char*>(&size), sizeof(size))) > 0) {
            std::string buffer(size, 0);
            auto bodyRecvRes = 0;
            if ((bodyRecvRes = m_socket.recv(buffer.data(), size)) > 0) {
                for (const auto &c : m_messageCallbacks) {
                    c(Message(buffer));
                }
            }
            else if (bodyRecvRes < 0) {
                m_error = m_socket.error();
                return false;
            }
            else {
                m_error = L"Connection timeout";
                return false;
            }
        }
        else if (sizeRecvRes < 0) {
            m_error = m_socket.error();
            return false;
        }
    }
    return true;
}
