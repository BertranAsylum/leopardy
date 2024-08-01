#include "TopbarForm.h"

#include <interfaces/GameController.h>

#include "widgets/Toolbar.h"
#include "widgets/TextLabel.h"
#include "widgets/FrameLayout.h"

void TopbarForm::setup(GameController *gameController, Widget *parent)
{
    auto *statusLabel = new TextLabel;
    statusLabel->setId(L"StatusLabel");
    auto *statusFrameLayout = new FrameLayout(statusLabel);
    statusFrameLayout->setId(L"StatusFrameLayout");
    statusFrameLayout->adjustWidgetSize(true);

    auto *topbar = new Toolbar(8);
    topbar->setId(L"TopbarWidget");
    topbar->setWidget(0, 7, statusFrameLayout);

    gameController->onEvent([gameController, statusLabel](const std::shared_ptr<GameEvent> &)
    {
        switch (gameController->gameSession()->state().currentStage) {
            case GameSession::State::Lobby:
                statusLabel->setText(L"Waiting for new players");
                break;
            case GameSession::State::SelectingPlayer:
                statusLabel->setText(L"Leader selecting player");
                break;
            case GameSession::State::ChoosingQuestion: {
                const auto &player = gameController->gameSession()->player(
                    gameController->gameSession()->state().playerNum);
                statusLabel->setText(player.nickname + L" choosing question");
                break;
            }
            case GameSession::State::ViewingQestion:
                statusLabel->setText(L"Waiting for players");
                break;
            case GameSession::State::PlayerAnswering: {
                const auto &player = gameController->gameSession()->player(
                    gameController->gameSession()->state().playerNum);
                statusLabel->setText(player.nickname + L" answering");
                break;
            }
            case GameSession::State::RoundFinished:
                statusLabel->setText(L"Round finished");
                break;
            case GameSession::State::GameFinished:
            case GameSession::State::ShowingWinner:
                statusLabel->setText(L"Game finished");
                break;
        }
    });

    auto *frameLayout = new FrameLayout(topbar);
    frameLayout->setId(L"TopbarFrameLayout");
    frameLayout->adjustWidgetSize(true);
    frameLayout->setParent(parent);
}
