#pragma once

#include "Participant.h"
#include "GameSession.h"

struct GameEvent {
    virtual ~GameEvent() = default;
    virtual bool local() const = 0;
    virtual bool internal() const = 0;

    template <typename E>
    const E *as() const
    {
        return dynamic_cast<const E*>(this);
    }

    template <typename E>
    E *as()
    {
        return dynamic_cast<E*>(this);
    }

    friend std::ostream &operator<<(std::ostream &s, const GameEvent *ep);
    friend std::istream &operator>>(std::istream &s, GameEvent *&ep);
};

struct UiReset : GameEvent {
    bool local() const override { return true; }
    bool internal() const override { return false; }
};

struct GameReset : GameEvent {
    bool local() const override { return true; }
    bool internal() const override { return true; }
};

struct GameSessionSync : GameEvent {
    GameSession session;
    bool local() const override { return false; }
    bool internal() const override { return true; }
};

struct PlayerJoinRequest : GameEvent {
    Player player;
    bool local() const override { return false; }
    bool internal() const override { return true; }
};

struct PlayerJoinRejected : GameEvent {
    Player player;
    bool local() const override { return false; }
    bool internal() const override { return true; }
};

struct PlayerJoined : GameEvent {
    Player player;
    bool local() const override { return false; }
    bool internal() const override { return false; }
};

struct ObserverJoinRequest : GameEvent {
    Observer observer;
    bool local() const override { return false; }
    bool internal() const override { return true; }
};

struct ObserverJoined : GameEvent {
    Observer observer;
    bool local() const override { return false; }
    bool internal() const override { return false; }
};

struct GameStarted : GameEvent {
    bool local() const override { return false; }
    bool internal() const override { return false; }
};

struct PlayerChoosing : GameEvent {
    int playerNum = -1;
    bool local() const override { return false; }
    bool internal() const override { return false; }
};

struct QuestionChosen : GameEvent {
    int roundNum = -1;
    int categoryNum = -1;
    int priceNum = -1;
    bool local() const override { return false; }
    bool internal() const override { return false; }
};

struct PlayerAnswerRequest : GameEvent {
    int playerNum = -1;
    bool local() const override { return false; }
    bool internal() const override { return true; }
};

struct PlayerAnswering : GameEvent {
    int playerNum = -1;
    bool local() const override { return false; }
    bool internal() const override { return false; }
};

struct PlayerTypingAnswer : GameEvent {
    std::wstring answer;
    bool local() const override { return false; }
    bool internal() const override { return false; }
};

struct PlayerIsRight : GameEvent {
    int scoreIncrease = 0;
    bool local() const override { return false; }
    bool internal() const override { return false; }
};

struct PlayerIsWrong : GameEvent {
    int scoreDecrease = 0;
    bool local() const override { return false; }
    bool internal() const override { return false; }
};

struct NextRound : GameEvent {
    bool local() const override { return false; }
    bool internal() const override { return false; }
};

struct PlayerWin : GameEvent {
    int playerNum = -1;
    bool local() const override { return false; }
    bool internal() const override { return false; }
};
