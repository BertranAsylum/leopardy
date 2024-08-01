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

Game::Game(Widget *window)
{
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
    pushEvent(std::make_shared<GameSessionReset>());
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
    if (!m_networkChannel.sendMessage(Network::Channel::Message(event.get()))) {
        raiseError(networkLostErrorMessage + L": " + m_networkChannel.error());
        return;
    }
    for (const auto &c : m_eventCallbacks) {
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
        std::lock_guard lock(Window::mutex());
        onNetworkChannelMessage(msg);
    });
    m_networkChannel.onError([this](const std::wstring &message)
    {
        std::lock_guard lock(Window::mutex());
        raiseError(networkConnectionErrorMessage + L": " + message);
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

    if (auto *e = event->as<GameSessionReset>()) {
        // NOTE: Ignore external session reset
        return;
    }
    else if (auto *e = event->as<PlayerJoinRequest>()) {
        if (m_thisParticipant->role() == Participant::Role::Leader) {
            if (m_gameSession.addPlayer(e->player)) {
                auto joined = std::make_shared<PlayerJoined>();
                joined->player = e->player;
                joined->session = m_gameSession;
                pushEvent(joined);
            }
        }
    }
    else if (auto *e = event->as<PlayerJoined>()) {
        if (m_thisParticipant->role() == Participant::Role::Player) {
            if (e->player.nickname == m_thisParticipant->nickname) {
                m_gameSession = e->session;
                m_mainForm.showGame();
                pushEvent(std::make_shared<GameSessionReset>());
            }
        }
    }

    const std::shared_ptr<GameEvent> eventShared(event);
    for (const auto &c : m_eventCallbacks) {
        c(eventShared);
    }
}
