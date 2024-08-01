#pragma once

#include "Participant.h"
#include "GameSet.h"

#include <vector>

class GameSession {
public:
    struct State {
        enum Stage {
            Lobby,
            SelectingPlayer,
            ChoosingQuestion,
            ViewingQestion,
            PlayerAnswering,
            RoundFinished,
            GameFinished
        };

        Stage currentStage = Stage::Lobby;
        int currentRound = 0;
        int questionCategoryNum = -1;
        int questionPriceNum = -1;
        int playerNum = -1;

        friend std::ostream &operator<<(std::ostream &s, const State &st);
        friend std::istream &operator>>(std::istream &s, State &st);
    };

    GameSession() = default;
    void init(const GameSet &gameSet, const Leader &leader);
    bool initialized() const;

    GameSet gameSet() const;
    Leader leader() const;

    void addPlayer(const Player &player);
    Player player(int playerNum) const;
    std::vector<Player> players() const;
    bool hasPlayer(const Player &player) const;

    void addObserver(const Observer &observer);
    std::vector<Observer> observers() const;

    void setThisPlayerNum(int playerNum);
    Player thisPlayer() const;
    bool amIPlayer() const;

    void start();
    void choosingQuestion(int playerNum);
    void viewingQuestion(int categoryNum, int priceNum);
    void playerAnswering(int playerNum);
    void increasePlayerScore(int value);
    void decreasePlayerScore(int value);
    void nextRound();
    void playerWin(int playerNum);

    State state() const;
    Player winner() const;
    int deduceWinner() const;

    friend std::ostream &operator<<(std::ostream &s, const GameSession &ss);
    friend std::istream &operator>>(std::istream &s, GameSession &ss);

private:
    GameSet m_gameSet;

    Leader m_leader;
    std::vector<Player> m_players;
    std::vector<Observer> m_observers;

    int m_thisPlayerNum = -1;
    State m_state;
};
