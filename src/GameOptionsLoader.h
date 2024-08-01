#pragma once

#include "GameOptions.h"

class GameOptionsLoader {
public:
    explicit GameOptionsLoader();
    explicit GameOptionsLoader(const std::string &path);

    void save(const GameOptions &opts) const;
    GameOptions load() const;

private:
    std::string m_path;
};
