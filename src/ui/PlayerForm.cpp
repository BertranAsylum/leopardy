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
        if (auto *e = event->as<UiReset>()) {
            reset();
        }
        else if (auto *e = event->as<PlayerJoined>()) {
            updatePlayerGrid();
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
    updatePlayerGrid();
}

void PlayerForm::updatePlayerGrid()
{
    // TODO: Gentle handle players
    const auto &players = m_gameController->gameSession()->players();
    assert("Game don't support more than 3 players" && players.size() <= 3);

    for (int i = m_playerGrid->childrenCount(); i < players.size(); ++i) {
        auto *playerCard = new PlayerCard(players[i]);
        playerCard->setId(L"PlayerCard" + players[i].nickname);
        m_playerGrid->addWidget(0, i, playerCard);
    }
}
