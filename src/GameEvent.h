#pragma once

#include "Participant.h"
#include "GameSession.h"

struct GameEvent {
    virtual ~GameEvent() = default;

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

struct GameSessionReset : GameEvent {};

struct GameSessionUpdated : GameEvent {
    GameSession session;
};

struct PlayerJoinRequest : GameEvent {
    Player player;
};

struct PlayerJoined : GameEvent {
    Player player;
    GameSession session;
};

struct ObserverJoinRequest : GameEvent {
    Observer observer;
};

struct ObserverJoined : GameEvent {
    Observer observer;
};

struct PlayerChoosing : GameEvent {
    int playerNum = -1;
};

struct QuestionChosen : GameEvent {
    int categoryNum = -1;
    int priceNum = -1;
};

struct PlayerAnswerRequest : GameEvent {
    int playerNum = -1;
};

struct PlayerAnswering : GameEvent {
    int playerNum = -1;
};

struct PlayerTypingAnswer : GameEvent {
    std::wstring answer;
};

struct PlayerIsRight : GameEvent {
    int scoreIncrease = 0;
};

struct PlayerIsWrong : GameEvent {
    int scoreDecrease = 0;
};

struct NextRound : GameEvent {};

struct PlayerWin : GameEvent {
    int playerNum = -1;
};
