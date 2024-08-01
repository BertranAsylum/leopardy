#pragma once

#include "Socket.h"

#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include <thread>

namespace Network {
class Channel {
public:
    class Message {
    public:
        template <typename T>
        explicit Message(const T &src);

        explicit Message(const std::string &data) :
            m_data(data) {}

        template <typename T>
        void deserialize(T &dest) const;

        std::string data() const { return m_data; }
        std::string &data() { return m_data; }

    private:
        std::string m_data;
    };

    using MessageCallback = std::function<void(const Message &msg)>;
    using ErrorCallback = std::function<void(const std::wstring &msg)>;

    ~Channel();

    bool connect(const std::wstring &address);
    bool sendMessage(const Message &msg);
    void onMessage(const MessageCallback &callback);
    void onError(const ErrorCallback &callback);

    std::wstring error() const;

private:
    bool listen();

private:
    Socket m_socket;
    std::wstring m_error;
    std::atomic<bool> m_listen = false;
    std::thread m_listenThread;
    std::vector<MessageCallback> m_messageCallbacks;
    std::vector<ErrorCallback> m_errorCallbacks;
};

template <typename T>
Channel::Message::Message(const T &src)
{
    std::stringstream stream;
    stream << src;
    m_data = stream.str();
}

template <typename T>
void Channel::Message::deserialize(T &dest) const
{
    std::stringstream stream(m_data);
    stream >> dest;
}
}
