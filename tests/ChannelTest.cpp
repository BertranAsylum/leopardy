#include "Testing.h"
#include "network/Channel.h"
#include "serializers/PrimitiveSerializer.h"
#include "serializers/StdWStringSerializer.h"

#include <semaphore>

struct TestMessage {
    int intField = 0;
    bool boolField = false;
    std::wstring wstrField;
    double doubleField = 0.0;
};

std::ostream &operator<<(std::ostream &s, const TestMessage &m)
{
    s << bytes(m.intField) << bytes(m.boolField) << m.wstrField << bytes(m.doubleField);
    return s;
}

std::istream &operator>>(std::istream &s, TestMessage &m)
{
    s >> bytes(m.intField) >> bytes(m.boolField) >> m.wstrField >> bytes(m.doubleField);
    return s;
}

void testMessage(const TestMessage &actual, const TestMessage &expected)
{
    TEST_EQ(actual.intField, expected.intField);
    TEST_EQ(actual.boolField, expected.boolField);
    TEST_EQ(actual.wstrField, expected.wstrField);
    TEST_EQ(actual.doubleField, expected.doubleField);
}

void testMessageSerialization()
{
    TestMessage tmsgActual;
    TestMessage tmsgExpect = {
        .intField = 99666,
        .boolField = true,
        .wstrField = L"Hello World",
        .doubleField = 456.789456
    };

    const auto data = Network::Channel::Message(tmsgExpect).data();
    TEST_GT(data.size(), 0);
    Network::Channel::Message(data).deserialize(tmsgActual);
    testMessage(tmsgActual, tmsgExpect);
}

void testSingleSend()
{
    Network::Channel channelFrom, channelTo;
    TEST_EQ(channelFrom.connect(L"127.0.0.1:50000"), true);
    TEST_EQ(channelTo.connect(L"127.0.0.1:50000"), true);
    std::this_thread::sleep_for(500ms);

    TestMessage msgExpect = {
        .intField = 99666,
        .boolField = true,
        .wstrField = L"Hello World",
        .doubleField = 456.789456
    };

    std::binary_semaphore sem{0};
    channelTo.onMessage([&sem, &msgExpect](const Network::Channel::Message &msg)
    {
        TestMessage msgActual;
        msg.deserialize(msgActual);
        testMessage(msgActual, msgExpect);
        sem.release();
    });

    TEST_EQ(channelFrom.sendMessage(Network::Channel::Message(msgExpect)), true);
    const auto done = sem.try_acquire_for(1s);
    TEST_EQ(done, true);
}

void testMultiSend()
{
    Network::Channel channelFrom, channelTo;
    TEST_EQ(channelFrom.connect(L"127.0.0.1:50000"), true);
    TEST_EQ(channelTo.connect(L"127.0.0.1:50000"), true);
    std::this_thread::sleep_for(500ms);

    int sent = 10;
    int received = 0;
    TestMessage msgExpect = {
        .intField = 99666,
        .boolField = true,
        .wstrField = L"Hello World",
        .doubleField = 456.789456
    };

    std::binary_semaphore sem{0};
    channelTo.onMessage([&sem, sent, &received, &msgExpect](const Network::Channel::Message &msg)
    {
        TestMessage msgActual;
        msg.deserialize(msgActual);
        testMessage(msgActual, msgExpect);

        ++received;
        if (received == sent) {
            sem.release();
        }
    });

    for (int i = 0; i < sent; ++i) {
        TEST_EQ(channelFrom.sendMessage(Network::Channel::Message(msgExpect)), true);
    }

    const auto done = sem.try_acquire_for(1s);
    TEST_EQ(done, true);
}

int main(int, char **)
{
    return TEST_RUN(
        testMessageSerialization,
        testSingleSend,
        testMultiSend);
}
