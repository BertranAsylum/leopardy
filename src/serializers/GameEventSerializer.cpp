#include "GameEvent.h"

#include "serializers/PrimitiveSerializer.h"
#include "serializers/StdWStringSerializer.h"

#include <cassert>

std::ostream &operator<<(std::ostream &s, const GameEvent *ep)
{
    assert(ep);

    if (auto *cep = ep->as<GameSessionSync>()) {
        s << bytes(1) << cep->session;
    }
    else if (auto *cep = ep->as<PlayerJoinRequest>()) {
        s << bytes(2) << cep->player;
    }
    else if (auto *cep = ep->as<PlayerJoinRejected>()) {
        s << bytes(3) << cep->player;
    }
    else if (auto *cep = ep->as<PlayerJoined>()) {
        s << bytes(4) << cep->player;
    }
    else if (auto *cep = ep->as<ObserverJoinRequest>()) {
        s << bytes(5) << cep->observer;
    }
    else if (auto *cep = ep->as<ObserverJoined>()) {
        s << bytes(6) << cep->observer;
    }
    else if (auto *cep = ep->as<GameStarted>()) {
        s << bytes(7);
    }
    else if (auto *cep = ep->as<PlayerChoosing>()) {
        s << bytes(8) << bytes(cep->playerNum);
    }
    else if (auto *cep = ep->as<QuestionChosen>()) {
        s << bytes(9) << bytes(cep->roundNum) << bytes(cep->categoryNum) << bytes(cep->priceNum);
    }
    else if (auto *cep = ep->as<PlayerAnswerRequest>()) {
        s << bytes(10) << bytes(cep->playerNum);
    }
    else if (auto *cep = ep->as<PlayerAnswering>()) {
        s << bytes(11) << bytes(cep->playerNum);
    }
    else if (auto *cep = ep->as<PlayerTypingAnswer>()) {
        s << bytes(12) << cep->answer;
    }
    else if (auto *cep = ep->as<PlayerIsRight>()) {
        s << bytes(13) << bytes(cep->scoreIncrease);
    }
    else if (auto *cep = ep->as<PlayerIsWrong>()) {
        s << bytes(14) << bytes(cep->scoreDecrease);
    }
    else if (auto *cep = ep->as<NextRound>()) {
        s << bytes(15);
    }
    else if (auto *cep = ep->as<PlayerWin>()) {
        s << bytes(16) << bytes(cep->playerNum);
    }
    else {
        assert("Unsupported game event serialization" && false);
    }
    return s;
}

std::istream &operator>>(std::istream &s, GameEvent *&ep)
{
    int type = 0;
    s >> bytes(type);

    switch (type) {
        case 1: {
            auto *cep = new GameSessionSync;
            s >> cep->session;
            ep = cep;
            break;
        }
        case 2: {
            auto *cep = new PlayerJoinRequest;
            s >> cep->player;
            ep = cep;
            break;
        }
        case 3: {
            auto *cep = new PlayerJoinRejected;
            s >> cep->player;
            ep = cep;
            break;
        }
        case 4: {
            auto *cep = new PlayerJoined;
            s >> cep->player;
            ep = cep;
            break;
        }
        case 5: {
            auto *cep = new ObserverJoinRequest;
            s >> cep->observer;
            ep = cep;
            break;
        }
        case 6: {
            auto *cep = new ObserverJoined;
            s >> cep->observer;
            ep = cep;
            break;
        }
        case 7: {
            ep = new GameStarted;
            break;
        }
        case 8: {
            auto *cep = new PlayerChoosing;
            s >> bytes(cep->playerNum);
            ep = cep;
            break;
        }
        case 9: {
            auto *cep = new QuestionChosen;
            s >> bytes(cep->roundNum) >> bytes(cep->categoryNum) >> bytes(cep->priceNum);
            ep = cep;
            break;
        }
        case 10: {
            auto *cep = new PlayerAnswerRequest;
            s >> bytes(cep->playerNum);
            ep = cep;
            break;
        }
        case 11: {
            auto *cep = new PlayerAnswering;
            s >> bytes(cep->playerNum);
            ep = cep;
            break;
        }
        case 12: {
            auto *cep = new PlayerTypingAnswer;
            s >> cep->answer;
            ep = cep;
            break;
        }
        case 13: {
            auto *cep = new PlayerIsRight;
            s >> bytes(cep->scoreIncrease);
            ep = cep;
            break;
        }
        case 14: {
            auto *cep = new PlayerIsWrong;
            s >> bytes(cep->scoreDecrease);
            ep = cep;
            break;
        }
        case 15: {
            ep = new NextRound;
            break;
        }
        case 16: {
            auto *cep = new PlayerWin;
            s >> bytes(cep->playerNum);
            ep = cep;
            break;
        }
        default: {
            break;
        }
    }
    return s;
}
