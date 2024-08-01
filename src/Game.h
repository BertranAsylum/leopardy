#pragma once

#include "GameSession.h"
#include "interfaces/GameStarter.h"
#include "interfaces/GameController.h"
#include "network/Channel.h"
#include "ui/MainForm.h"

#include <memory>
#include <vector>

class Widget;

class Game : public GameStarter, public GameController {
public:
    explicit Game(Widget *window);

    GameOptions lastOptions() override;
    bool createGame(const GameOptions &opts) override;
    bool joinGameAsPlayer(const GameOptions &opts) override;
    bool joinGameAsObserver(const GameOptions &opts) override;
    bool quitToMenu() override;

    const GameSession *gameSession() const override;
    void onEvent(const EventCallback &callback) override;
    void pushEvent(const std::shared_ptr<GameEvent> &event) override;
    void raiseError(const std::wstring &message) override;

private:
    bool initNetworkChannel(const std::wstring &address);
    void onNetworkChannelMessage(const Network::Channel::Message &msg);
    void onGameEvent(const std::shared_ptr<GameEvent> &event);

private:
    MainForm m_mainForm;
    GameSession m_gameSession;
    std::shared_ptr<Participant> m_thisParticipant;
    std::vector<EventCallback> m_eventCallbacks;
    Network::Channel m_networkChannel;
};

