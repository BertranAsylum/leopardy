#pragma once

#include "GameEvent.h"

#include <memory>
#include <functional>

class GameSession;

class GameController {
public:
    using EventCallback = std::function<void(const std::shared_ptr<GameEvent> &event)>;

    virtual const GameSession *gameSession() const = 0;
    virtual void onEvent(const EventCallback &callback) = 0;
    virtual void pushEvent(const std::shared_ptr<GameEvent> &event) = 0;

    virtual void raiseError(const std::wstring &message) = 0;
};
