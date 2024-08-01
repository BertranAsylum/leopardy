#include "Testing.h"
#include "serializers/StdVectorSerializer.h"

#include <fstream>

void testIntVector()
{
    std::ofstream os{
        "StdVector.bin", std::fstream::binary | std::fstream::trunc
    };
    std::vector<int> vecToWrite = {0, 100, 333, 10000, -4000, -80000000};
    std::vector<int> vecToRead;

    os << vecToWrite;
    os.close();

    std::ifstream is{
        "StdVector.bin", std::fstream::binary
    };

    is >> vecToRead;
    is.close();


    TEST_EQ(vecToWrite.size(), vecToRead.size());
    for (int i = 0; i < vecToWrite.size(); ++i) {
        TEST_EQ(vecToWrite[i], vecToRead[i]);
    }
}

int main(int, char **)
{
    return TEST_RUN(testIntVector);
}
