#pragma once

#include "GameOptions.h"

class GameStarter {
public:
    virtual GameOptions lastOptions() = 0;
    virtual bool createGame(const GameOptions &opts) = 0;
    virtual bool joinGameAsPlayer(const GameOptions &opts) = 0;
    virtual bool joinGameAsObserver(const GameOptions &opts) = 0;
    virtual bool quitToMenu() = 0;
};
