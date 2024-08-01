#include "Testing.h"
#include "serializers/StdWStringSerializer.h"
#include "serializers/StdMapSerializer.h"

#include <fstream>

void testIntIntMap()
{
    std::ofstream os{
        "StdMap.bin", std::fstream::binary | std::fstream::trunc
    };
    std::map<int, int> mapToWrite = {{100, 1000}, {0, 2000}, {-200, -3000}};
    std::map<int, int> mapToRead;

    os << mapToWrite;
    os.close();

    std::ifstream is{
        "StdMap.bin", std::fstream::binary
    };

    is >> mapToRead;
    is.close();

    TEST_EQ(mapToWrite.size(), mapToRead.size());
    for (const auto &e : mapToWrite) {
        TEST_EQ(e.second, mapToRead.at(e.first));
    }
}

void testWStringIntMap()
{
    std::ofstream os{
        "StdMap.bin", std::fstream::binary | std::fstream::trunc
    };
    std::map<std::wstring, int> mapToWrite = {{L"abc", 1000}, {L"", 2000}, {L"abc qwe", -3000}};
    std::map<std::wstring, int> mapToRead;

    os << mapToWrite;
    os.close();

    std::ifstream is{
        "StdMap.bin", std::fstream::binary
    };

    is >> mapToRead;
    is.close();

    TEST_EQ(mapToWrite.size(), mapToRead.size());
    for (const auto &e : mapToWrite) {
        TEST_EQ(e.second, mapToRead.at(e.first));
    }
}

int main(int, char **)
{
    return TEST_RUN(testIntIntMap, testWStringIntMap);
}
