#include "Testing.h"
#include "utils/NetworkAddress.h"

void testValidAddress()
{
    const NetworkAddress address(L"127.0.0.1:50000");
    const std::string host(address.host());
    const std::string port(address.port());

    TEST_EQ(host, std::string("127.0.0.1"));
    TEST_EQ(port, std::string("50000"));
}

int main(int, char **)
{
    return TEST_RUN(testValidAddress);
}
