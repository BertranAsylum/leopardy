#include "Game.h"

#include "Window.h"
#include "GameEvent.h"
#include "GameSetLoader.h"
#include "GameOptionsLoader.h"

static const std::wstring networkConnectionErrorMessage =
    L"Network error\n\n"
    L"Can't connect to server";
static const std::wstring networkLostErrorMessage =
    L"Network error\n\n"
    L"Connection with server lost";
static const std::wstring networkProtocolErrorMessage =
    L"Network error\n\n"
    L"Fatal protocol violation";
static const std::wstring lobbyIsFullMessage =
    L"Player join rejected\n\n"
    L"Lobby is full";

Game::Game(Widget *window)
{
    m_eventCallbacks.emplace_back([this](const std::shared_ptr<GameEvent> &event) { onGameEvent(event); });
    m_mainForm.setup(this, window);
}

GameOptions Game::lastOptions()
{
    return GameOptionsLoader().load();
}

bool Game::createGame(const GameOptions &opts)
{
    GameOptionsLoader().save(opts);

    if (!initNetworkChannel(opts.serverAddress)) {
        return false;
    }

    Leader leader;
    leader.nickname = opts.nickname;

    m_thisParticipant = std::make_shared<Leader>(leader);
    m_gameSession.init(GameSetLoader::load(), leader);
    m_mainForm.showGame();

    pushEvent(std::make_shared<UiReset>());
    return true;
}

bool Game::joinGameAsPlayer(const GameOptions &opts)
{
    GameOptionsLoader().save(opts);

    if (!initNetworkChannel(opts.serverAddress)) {
        return false;
    }

    auto joinRequest = std::make_shared<PlayerJoinRequest>();
    joinRequest->player.nickname = opts.nickname;
    m_thisParticipant = std::make_shared<Player>(joinRequest->player);

    pushEvent(joinRequest);
    return true;
}

bool Game::joinGameAsObserver(const GameOptions &opts)
{
    GameOptionsLoader().save(opts);
    return false;
}

bool Game::quitToMenu()
{
    m_mainForm.showMenu();
    return true;
}

const Participant *Game::thisParticipant()
{
    return m_thisParticipant.get();
}

const GameSession *Game::gameSession() const
{
    return &m_gameSession;
}

void Game::onEvent(const EventCallback &callback)
{
    m_eventCallbacks.push_back(callback);
}

void Game::pushEvent(const std::shared_ptr<GameEvent> &event)
{
    if (!event->local()) {
        if (!m_networkChannel.sendMessage(Network::Channel::Message(event.get()))) {
            raiseError(networkLostErrorMessage + L": " + m_networkChannel.error());
            return;
        }
    }
    auto callbacks = m_eventCallbacks;
    for (auto &c : callbacks) {
        c(event);
    }
}

void Game::raiseError(const std::wstring &message)
{
    m_mainForm.showError(message);
}

bool Game::initNetworkChannel(const std::wstring &address)
{
    if (!m_networkChannel.connect(address)) {
        raiseError(networkConnectionErrorMessage + L": " + m_networkChannel.error());
        return false;
    }
    m_networkChannel.onMessage([this](const Network::Channel::Message &msg)
    {
        Application::push([this, msg]() { onNetworkChannelMessage(msg); });
    });
    m_networkChannel.onError([this](const std::wstring &message)
    {
        Application::push([this, message]() { raiseError(networkConnectionErrorMessage + L": " + message); });
    });
    return true;
}

void Game::onNetworkChannelMessage(const Network::Channel::Message &msg)
{
    GameEvent *event = nullptr;
    msg.deserialize(event);
    if (!event) {
        raiseError(networkProtocolErrorMessage + L": Unsupported message received");
        return;
    }
    if (event->local()) {
        raiseError(networkProtocolErrorMessage + L": Unexpected local event received");
        return;
    }

    const std::shared_ptr<GameEvent> eventShared(event);
    auto callbacks = m_eventCallbacks;
    for (auto &c : callbacks) {
        c(eventShared);
    }
}

void Game::onGameEvent(const std::shared_ptr<GameEvent> &event)
{
    if (auto *e = event->as<GameSessionSync>()) {
        if (!m_gameSession.initialized()) {
            m_gameSession = e->session;
            m_mainForm.showGame();
        }
    }
    else if (auto *e = event->as<PlayerJoinRequest>()) {
        if (m_thisParticipant->role() == Participant::Role::Leader) {
            if (m_gameSession.players().size() < 3 || m_gameSession.hasPlayer(e->player)) {
                auto sync = std::make_shared<GameSessionSync>();
                sync->session = m_gameSession;
                pushEvent(sync);

                auto joined = std::make_shared<PlayerJoined>();
                joined->player = e->player;
                pushEvent(joined);
            }
            else {
                auto rejected = std::make_shared<PlayerJoinRejected>();
                rejected->player = e->player;
                pushEvent(rejected);
            }
        }
    }
    else if (auto *e = event->as<PlayerJoinRejected>()) {
        if (m_thisParticipant->role() == Participant::Role::Player
            && m_thisParticipant->nickname == e->player.nickname) {
            raiseError(lobbyIsFullMessage);
        }
    }
    else if (auto *e = event->as<PlayerJoined>()) {
        const auto playerNum = m_gameSession.addPlayer(e->player);
        if (m_thisParticipant->role() == Participant::Role::Player
            && m_thisParticipant->nickname == e->player.nickname) {
            m_gameSession.setThisPlayerNum(playerNum);
            pushEvent(std::make_shared<UiReset>());
        }
    }
    else if (auto *e = event->as<ObserverJoined>()) {
        m_gameSession.addObserver(e->observer);
    }
    else if (auto *e = event->as<GameStarted>()) {
        m_gameSession.start();
    }
    else if (auto *e = event->as<PlayerChoosing>()) {
        m_gameSession.choosingQuestion(e->playerNum);
    }
    else if (auto *e = event->as<QuestionChosen>()) {
        m_gameSession.viewingQuestion(e->categoryNum, e->priceNum);
    }
    else if (auto *e = event->as<PlayerAnswerRequest>()) {
        if (m_thisParticipant->role() == Participant::Role::Leader) {
            if (m_gameSession.state().currentStage != GameSession::State::Stage::PlayerAnswering) {
                auto playerAnswering = std::make_shared<PlayerAnswering>();
                playerAnswering->playerNum = e->playerNum;
                pushEvent(playerAnswering);
            }
        }
    }
    else if (auto *e = event->as<PlayerAnswering>()) {
        m_gameSession.playerAnswering(e->playerNum);
    }
    else if (auto *e = event->as<PlayerIsRight>()) {
        m_gameSession.increasePlayerScore(e->scoreIncrease);
    }
    else if (auto *e = event->as<PlayerIsWrong>()) {
        m_gameSession.decreasePlayerScore(e->scoreDecrease);
    }
    else if (auto *e = event->as<NextRound>()) {
        m_gameSession.nextRound();
    }
    else if (auto *e = event->as<PlayerWin>()) {
        m_gameSession.nextRound();
    }
}
