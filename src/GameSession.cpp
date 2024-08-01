#include "GameSession.h"

#include <cassert>

void GameSession::init(const GameSet &gameSet, const Leader &leader)
{
    m_gameSet = gameSet;
    m_leader = leader;
}

GameSet GameSession::gameSet() const
{
    return m_gameSet;
}

Leader GameSession::leader() const
{
    return m_leader;
}

bool GameSession::addPlayer(const Player &player)
{
    const bool contains = std::find_if(m_players.begin(), m_players.end(), [player](const Player &p)
    {
        return p.nickname == player.nickname;
    }) != m_players.end();

    if (contains) {
        return true;
    }

    if (m_players.size() == 3) {
        return false;
    }

    m_players.push_back(player);
    return true;
}

Player GameSession::player(int playerNum) const
{
    if (playerNum < m_players.size()) {
        return m_players.at(playerNum);
    }
    return {};
}

std::vector<Player> GameSession::players() const
{
    return m_players;
}

void GameSession::addObserver(const Observer &observer)
{
    m_observers.push_back(observer);
}

std::vector<Observer> GameSession::observers() const
{
    return m_observers;
}

void GameSession::setThisPlayerNum(int playerNum)
{
    assert(playerNum < m_players.size());
    m_thisPlayerNum = playerNum;
}

Player GameSession::thisPlayer() const
{
    return m_players.at(m_thisPlayerNum);
}

bool GameSession::amIPlayer() const
{
    return (m_thisPlayerNum >= 0);
}

void GameSession::start()
{
    assert(m_state.currentStage == State::Stage::Lobby);

    m_state.currentStage = State::Stage::SelectingPlayer;
    m_state.currentRound = 0;
    m_state.questionCategoryNum = -1;
    m_state.questionPriceNum = -1;
    m_state.playerNum = -1;
}

void GameSession::choosingQuestion(int playerNum)
{
    assert(m_state.currentStage == State::Stage::SelectingPlayer);

    m_state.currentStage = State::Stage::ChoosingQuestion;
    m_state.questionCategoryNum = -1;
    m_state.questionPriceNum = -1;
    m_state.playerNum = playerNum;
}

void GameSession::viewingQuestion(int categoryNum, int priceNum)
{
    assert(m_state.currentStage == State::Stage::ChoosingQuestion);
    assert(m_state.playerNum >= 0);
    assert(m_state.currentRound < m_gameSet.rounds.size());
    assert(categoryNum < m_gameSet.rounds.at(m_state.currentRound).categories.size());
    assert(priceNum < m_gameSet.rounds.at(m_state.currentRound).categories.at(categoryNum).cards.size());
    assert(m_gameSet.rounds.at(m_state.currentRound).categories.at(categoryNum).cards.at(priceNum).used == false);

    m_state.currentStage = State::Stage::ViewingQestion;
    m_state.questionCategoryNum = categoryNum;
    m_state.questionPriceNum = priceNum;

    m_gameSet.rounds.at(m_state.currentRound).categories.at(categoryNum).cards.at(priceNum).used = true;
}

void GameSession::playerAnswering(int playerNum)
{
    assert(m_state.currentStage == State::Stage::ViewingQestion);
    assert(m_state.questionCategoryNum >= 0);
    assert(m_state.questionPriceNum >= 0);

    m_state.currentStage = State::Stage::PlayerAnswering;
    m_state.playerNum = playerNum;
}

void GameSession::increasePlayerScore(int playerNum, int value)
{
    assert(m_state.currentStage == State::Stage::PlayerAnswering);
    assert(playerNum < m_players.size());
    assert(m_state.currentRound < m_gameSet.rounds.size());

    if (gameSet().rounds.at(m_state.currentRound).hasUnusedCards()) {
        m_state.currentStage = State::Stage::SelectingPlayer;
    }
    else {
        m_state.currentStage = State::Stage::RoundFinished;
    }

    m_state.questionCategoryNum = -1;
    m_state.questionPriceNum = -1;
    m_state.playerNum = -1;

    m_players.at(playerNum).score += value;
}

void GameSession::decreasePlayerScore(int playerNum, int value)
{
    assert(m_state.currentStage == State::Stage::PlayerAnswering);
    assert(playerNum < m_players.size());
    assert(m_state.currentRound < m_gameSet.rounds.size());

    if (gameSet().rounds.at(m_state.currentRound).hasUnusedCards()) {
        m_state.currentStage = State::Stage::SelectingPlayer;
    }
    else {
        m_state.currentStage = State::Stage::RoundFinished;
    }

    m_state.questionCategoryNum = -1;
    m_state.questionPriceNum = -1;
    m_state.playerNum = -1;

    m_players.at(playerNum).score -= value;
}

void GameSession::nextRound()
{
    assert(m_state.currentStage == State::Stage::RoundFinished);
    assert(m_state.currentRound < m_gameSet.rounds.size() - 1);

    m_state.currentStage = State::Stage::SelectingPlayer;
    m_state.currentRound++;
    m_state.questionCategoryNum = -1;
    m_state.questionPriceNum = -1;
    m_state.playerNum = -1;
}

void GameSession::playerWin(int playerNum)
{
    assert(m_state.currentStage == State::Stage::RoundFinished);
    assert(m_state.currentRound == m_gameSet.rounds.size() - 1);

    m_state.currentStage = State::Stage::GameFinished;
    m_state.questionCategoryNum = -1;
    m_state.questionPriceNum = -1;
    m_state.playerNum = playerNum;
}

GameSession::State GameSession::state() const
{
    return m_state;
}

Player GameSession::winner() const
{
    assert(m_state.currentStage == State::Stage::GameFinished);
    return m_players.at(m_state.playerNum);
}

// TODO: Resolve players with same score
int GameSession::deduceWinner() const
{
    int maxScore = 0;
    int winnerNum = 0;
    int playerNum = 0;
    for (const auto &p : m_players) {
        if (p.score > maxScore) {
            maxScore = p.score;
            winnerNum = playerNum;
        }
        ++playerNum;
    }
    return winnerNum;
}
