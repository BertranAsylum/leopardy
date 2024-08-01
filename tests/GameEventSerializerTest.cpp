#include "Testing.h"
#include "GameEvent.h"

#include <sstream>

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

void testGameSessionReset()
{
    std::stringstream os;
    auto eventToWrite = std::make_shared<GameSessionReset>();
    os << eventToWrite.get();

    GameEvent *eventToRead = nullptr;
    std::stringstream is(os.str());
    is >> eventToRead;

    TEST_EQ(eventToRead == nullptr, false);

    auto *concreteEventToRead = eventToRead->as<GameSessionReset>();
    TEST_EQ(concreteEventToRead == nullptr, false);
}

void testPlayerJoinRequest()
{
    std::stringstream os;
    auto eventToWrite = std::make_shared<PlayerJoinRequest>();
    eventToWrite->player = Player{.score = 200};

    os << eventToWrite.get();

    GameEvent *eventToRead = nullptr;
    std::stringstream is(os.str());
    is >> eventToRead;

    TEST_EQ(eventToRead == nullptr, false);

    auto *concreteEventToRead = eventToRead->as<PlayerJoinRequest>();
    TEST_EQ(concreteEventToRead == nullptr, false);
    TEST_EQ(concreteEventToRead->player.nickname, eventToWrite->player.nickname);
    TEST_EQ(concreteEventToRead->player.score, eventToWrite->player.score);
}

void testPlayerJoined()
{
    std::stringstream os;
    auto eventToWrite = std::make_shared<PlayerJoined>();
    eventToWrite->player = Player{.score = -300};
    eventToWrite->session = gameSessionTestObject();

    os << eventToWrite.get();

    GameEvent *eventToRead = nullptr;
    std::stringstream is(os.str());
    is >> eventToRead;

    TEST_EQ(eventToRead == nullptr, false);

    auto *concreteEventToRead = eventToRead->as<PlayerJoined>();
    TEST_EQ(concreteEventToRead == nullptr, false);
    TEST_EQ(concreteEventToRead->player.nickname, eventToWrite->player.nickname);
    TEST_EQ(concreteEventToRead->player.score, eventToWrite->player.score);
}

int main(int, char **)
{
    return TEST_RUN(
        testGameSessionReset,
        testPlayerJoinRequest,
        testPlayerJoined);
}
