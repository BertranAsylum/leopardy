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
        else if (event->as<GameStarted>()
            || event->as<NextRound>()) {
            togglePlayerGrid(true);
        }
        else if (event->as<PlayerIsRight>()
            || event->as<PlayerIsWrong>()) {
            togglePlayerGrid(true);
            updatePlayersScore();
        }
        else {
            togglePlayerGrid(false);
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

    const auto stage = m_gameController->gameSession()->state().currentStage;
    togglePlayerGrid(stage == GameSession::State::Stage::SelectingPlayer);
}

void PlayerForm::updatePlayerGrid()
{
    // TODO: Gentle handle players
    const auto &players = m_gameController->gameSession()->players();
    assert("Game don't support more than 3 players" && players.size() <= 3);

    for (int i = m_playerGrid->childrenCount(); i < players.size(); ++i) {
        auto *playerCard = new PlayerCard(players[i]);
        playerCard->setId(L"PlayerCard" + players[i].nickname);
        playerCard->disable();
        playerCard->onMouseRelease([this, i](int, int)
        {
            auto playerChoosing = std::make_shared<PlayerChoosing>();
            playerChoosing->playerNum = i;
            m_gameController->pushEvent(playerChoosing);
        });
        m_playerGrid->addWidget(0, i, playerCard);
    }
}

void PlayerForm::togglePlayerGrid(bool enable)
{
    if (m_gameController->thisParticipant()->role() == Participant::Role::Leader) {
        for (auto *c : m_playerGrid->children()) {
            c->setEnabled(enable);
        }
    }
}

void PlayerForm::updatePlayersScore()
{
    auto playerNum = 0;
    for (auto *c : m_playerGrid->children()) {
        if (auto *playerCard = dynamic_cast<PlayerCard*>(c)) {
            playerCard->setScore(m_gameController->gameSession()->player(playerNum).score);
        }
        playerNum++;
    }
}
