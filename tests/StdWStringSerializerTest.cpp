#include "Testing.h"
#include "serializers/StdWStringSerializer.h"

#include <fstream>

void testSingleWString()
{
    std::ofstream os{
        "StdWString.bin", std::fstream::binary | std::fstream::trunc
    };

    std::wstring strToWrite = L"Hello";
    std::wstring strToRead;

    os << strToWrite;
    os.close();

    std::ifstream is{
        "StdWString.bin", std::fstream::binary
    };

    is >> strToRead;
    is.close();

    TEST_EQ(strToWrite, strToRead);
}

void testMultipleWString()
{
    std::ofstream os{
        "StdWString.bin", std::fstream::binary | std::fstream::trunc
    };

    std::wstring strToWrite1 = L"Hello";
    std::wstring strToWrite2 = L"";
    std::wstring strToWrite3 = L"World World";

    std::wstring strToRead1;
    std::wstring strToRead2;
    std::wstring strToRead3;

    os << strToWrite1 << strToWrite2 << strToWrite3;
    os.close();

    std::ifstream is{
        "StdWString.bin", std::fstream::binary
    };

    is >> strToRead1 >> strToRead2 >> strToRead3;
    is.close();

    TEST_EQ(strToWrite1, strToRead1);
    TEST_EQ(strToWrite2, strToRead2);
    TEST_EQ(strToWrite3, strToRead3);
}

int main(int, char **)
{
    return TEST_RUN(testSingleWString, testMultipleWString);
}
