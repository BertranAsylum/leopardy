#include "PlayerForm.h"

#include "GameSession.h"
#include "widgets/GridLayout.h"
#include "widgets/FrameLayout.h"
#include "widgets/PlayerCard.h"
#include "interfaces/GameController.h"

#include <cassert>

void PlayerForm::setup(GameController *gameController, Widget *parent)
{
    m_gameController = gameController;
    m_gameController->onEvent([this](const std::shared_ptr<GameEvent> &event)
    {
        if (auto *e = event->as<PlayerJoined>()) {
            reset();
        }
    });

    m_playerGrid = new GridLayout(1, 3);
    m_playerGrid->setId(L"PlayerGridLayout");
    m_playerGrid->adjustWidgetSize(true);
    m_playerGrid->setMargins(10.0f);

    auto *frame = new FrameLayout(m_playerGrid);
    frame->setId(L"PlayerFrameLayout");
    frame->adjustWidgetSize(true);
    frame->setParent(parent);
}

void PlayerForm::reset()
{
    m_playerGrid->clearChildren();

    const auto &players = m_gameController->gameSession()->players();
    // TODO: Gentle handle players
    assert("Game don't support more than 3 players" && players.size() <= 3);

    int playerNum = 0;
    for (const auto &player : players) {
        auto *playerCard = new PlayerCard(player);
        playerCard->setId(L"PlayerCard" + player.nickname);
        m_playerGrid->addWidget(0, playerNum++, playerCard);
    }
}
