#include "GameOptionsLoader.h"
#include "serializers/StdWStringSerializer.h"

#include <fstream>

GameOptionsLoader::GameOptionsLoader() :
    m_path("leopardy.cfg") {}

GameOptionsLoader::GameOptionsLoader(const std::string &path) :
    m_path(path) {}

void GameOptionsLoader::save(const GameOptions &opts) const
{
    std::ofstream stream(m_path, std::fstream::binary | std::fstream::trunc);
    stream << opts.nickname << opts.serverAddress;
}

GameOptions GameOptionsLoader::load() const
{
    GameOptions opts;
    std::ifstream stream(m_path, std::fstream::binary);
    stream >> opts.nickname >> opts.serverAddress;
    return opts;
}
