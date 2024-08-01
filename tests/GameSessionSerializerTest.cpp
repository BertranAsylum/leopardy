#include "Testing.h"
#include "GameSession.h"

#include <fstream>

static GameSession gameSessionTestObject()
{
    GameSet gameSet;
    for (int k = 0; k < 2; ++k) {
        GameSet::Round round;
        for (int j = 1; j < 7; ++j) {
            GameSet::Category category;
            category.name = L"Cat " + std::to_wstring(j + 10 * k);
            for (int i = 1; i < 6; ++i) {
                GameSet::Card c;
                c.used = (j * i) % 2;
                c.price = (k + 1) * i * 100;
                c.question = L"Question from " + category.name + L" question " + std::to_wstring(c.price) + L"?";
                category.cards.push_back(c);
            }
            round.categories.push_back(category);
        }
        gameSet.rounds.push_back(round);
    }

    Leader l;
    l.nickname = L"Dima";

    Player p1, p2, p3;
    p1.nickname = L"Vovan";
    p1.score = 0;
    p2.nickname = L"Mikola";
    p2.score = 600;
    p3.nickname = L"Dmitro";
    p3.score = 1800;

    Observer o1, o2, o3;
    o1.nickname = L"Rulon";
    o2.nickname = L"Saray";
    o3.nickname = L"Slon";

    GameSession session;

    session.init(gameSet, l);

    session.addPlayer(p1);
    session.addPlayer(p2);
    session.addPlayer(p3);

    session.addObserver(o1);
    session.addObserver(o2);
    session.addObserver(o3);

    session.setThisPlayerNum(1);

    session.start();
    session.choosingQuestion(2);
    session.viewingQuestion(2, 3);

    return session;
}

void testFullGameSession()
{
    std::ofstream os{
        "GameSession.bin", std::fstream::binary | std::fstream::trunc
    };
    GameSession sessionToWrite = gameSessionTestObject();
    GameSession sessionToRead;

    os << sessionToWrite;
    os.close();

    std::ifstream is{
        "GameSession.bin", std::fstream::binary
    };

    is >> sessionToRead;
    is.close();

    const auto &gameSetToWrite = sessionToWrite.gameSet();
    const auto &gameSetToRead = sessionToRead.gameSet();

    TEST_EQ(gameSetToWrite.rounds.size(), gameSetToRead.rounds.size());
    for (int i = 0; i < gameSetToWrite.rounds.size(); ++i) {
        TEST_EQ(gameSetToWrite.rounds[i].categories.size(), gameSetToRead.rounds[i].categories.size());
        for (int j = 0; j < gameSetToWrite.rounds[i].categories.size(); ++j) {
            TEST_EQ(gameSetToWrite.rounds[i].categories[j].name,
                    gameSetToRead.rounds[i].categories[j].name);
            TEST_EQ(gameSetToWrite.rounds[i].categories[j].cards.size(),
                    gameSetToRead.rounds[i].categories[j].cards.size());
            for (int k = 0; k < gameSetToWrite.rounds[i].categories[j].cards.size(); ++k) {
                TEST_EQ(gameSetToWrite.rounds[i].categories[j].cards[k].used,
                        gameSetToRead.rounds[i].categories[j].cards[k].used);
                TEST_EQ(gameSetToWrite.rounds[i].categories[j].cards[k].price,
                        gameSetToRead.rounds[i].categories[j].cards[k].price);
                TEST_EQ(gameSetToWrite.rounds[i].categories[j].cards[k].question,
                        gameSetToRead.rounds[i].categories[j].cards[k].question);
                TEST_EQ(gameSetToWrite.rounds[i].categories[j].cards[k].answer,
                        gameSetToRead.rounds[i].categories[j].cards[k].answer);
            }
        }
    }

    TEST_EQ(sessionToWrite.leader().nickname, sessionToRead.leader().nickname);

    const auto &playersToWrite = sessionToWrite.players();
    const auto &playersToRead = sessionToRead.players();

    TEST_EQ(playersToWrite.size(), playersToRead.size());
    for (int i = 0; i < playersToWrite.size(); ++i) {
        TEST_EQ(playersToWrite.at(i).nickname, playersToRead.at(i).nickname);
        TEST_EQ(playersToWrite.at(i).score, playersToRead.at(i).score);
    }

    const auto &observersToWrite = sessionToWrite.observers();
    const auto &observersToRead = sessionToRead.observers();

    TEST_EQ(observersToWrite.size(), observersToRead.size());
    for (int i = 0; i < observersToWrite.size(); ++i) {
        TEST_EQ(observersToWrite.at(i).nickname, observersToRead.at(i).nickname);
    }

    const auto &stateToWrite = sessionToWrite.state();
    const auto &stateToRead = sessionToRead.state();

    TEST_EQ(stateToWrite.currentStage, stateToRead.currentStage);
    TEST_EQ(stateToWrite.currentRound, stateToRead.currentRound);
    TEST_EQ(stateToWrite.questionCategoryNum, stateToRead.questionCategoryNum);
    TEST_EQ(stateToWrite.questionPriceNum, stateToRead.questionPriceNum);
    TEST_EQ(stateToWrite.playerNum, stateToRead.playerNum);
}


int main(int, char **)
{
    return TEST_RUN(testFullGameSession);
}
