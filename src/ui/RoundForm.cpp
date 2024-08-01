#include "RoundForm.h"

#include "GameSession.h"
#include "widgets/Pager.h"
#include "widgets/Button.h"
#include "widgets/TextLabel.h"
#include "widgets/GridLayout.h"
#include "widgets/FrameLayout.h"
#include "widgets/QuestionCard.h"
#include "widgets/CategoryCard.h"
#include "interfaces/GameController.h"

#include <cassert>

void RoundForm::setup(GameController *gameController, Widget *parent)
{
    m_gameController = gameController;
    m_gameController->onEvent([this](const std::shared_ptr<GameEvent> &event)
    {
        if (auto *e = event->as<GameSessionReset>()) {
            reset();
        }
        else if (auto *e = event->as<QuestionChosen>()) {
            const auto round = m_gameController->gameSession()->state().currentRound;
            const auto card = m_gameController->gameSession()->gameSet().rounds[round].categories[e->categoryNum].cards
                [e->priceNum];

            auto *questionCard = new QuestionCard(card);
            questionCard->setId(L"QuestionCard");
            questionCard->onMouseRelease([this](int, int)
            {
                auto playerIsRight = std::make_shared<PlayerIsRight>();
                m_gameController->pushEvent(playerIsRight);
            });
            m_questionPage->clearChildren();
            m_questionPage->addWidget(1, 2, 4, 5, questionCard);

            const auto questionPageNum = m_roundPager->pageCount() - 2;
            m_roundPager->switchTo(questionPageNum);
        }
        else if (auto *e = event->as<PlayerIsRight>()) {
            m_roundPager->switchTo(m_gameController->gameSession()->state().currentRound);
        }
    });

    m_roundPager = new Pager;
    m_roundPager->setId(L"RoundPager");

    auto *frame = new FrameLayout(m_roundPager);
    frame->setId(L"RoundFrameLayout");
    frame->adjustWidgetSize(true);
    frame->setParent(parent);
}

void RoundForm::reset()
{
    m_roundPager->clearChildren();

    const auto *session = m_gameController->gameSession();

    m_questionPage = new GridLayout(6, 8);
    m_questionPage->setId(L"QuestionPage");
    m_questionPage->adjustWidgetSize(true);

    m_winnerLabel = new TextLabel;
    m_winnerLabel->setId(L"WinnerLabel");

    auto *winnerPage = new FrameLayout(m_winnerLabel);
    winnerPage->setId(L"WinnerPage");

    int roundNum = 1;
    const auto &rounds = session->gameSet().rounds;

    for (auto round : rounds) {
        // TODO: Gentle handle categories
        assert("Game don't support more than 6 categories" && round.categories.size() <= 6);

        auto *roundPage = new GridLayout(2, 3);
        roundPage->setId(L"RoundPage" + std::to_wstring(roundNum++));
        roundPage->setMargins(10.0f);
        roundPage->adjustWidgetSize(true);

        auto categoryNum = 0;
        for (int row = 0; row < roundPage->rowCount(); ++row) {
            for (int col = 0; col < roundPage->colCount(); ++col) {
                if (categoryNum >= round.categories.size()) {
                    break;
                }

                const auto &category = round.categories[categoryNum];
                auto *cardWidget = new CategoryCard(category.name, category);
                cardWidget->setId(L"CategoryCard" + std::to_wstring(row) + std::to_wstring(col));
                roundPage->addWidget(row, col, cardWidget);

                auto priceNum = 0;
                for (auto &card : category.cards) {
                    auto *priceButton = cardWidget->priceButton(card.price);
                    priceButton->onMouseRelease([this, categoryNum, priceNum](int, int)
                    {
                        auto questionChoosen = std::make_shared<QuestionChosen>();
                        questionChoosen->categoryNum = categoryNum;
                        questionChoosen->priceNum = priceNum;
                        m_gameController->pushEvent(questionChoosen);
                    });
                    ++priceNum;
                }
                ++categoryNum;
            }
        }
        m_roundPager->addPage(roundPage);
    }
    m_roundPager->addPage(m_questionPage);
    m_roundPager->addPage(winnerPage);

    if (session->state().currentStage == GameSession::State::Stage::GameFinished) {
        setWinner(session->winner());
        const auto winnerPageNum = m_roundPager->pageCount() - 1;
        m_roundPager->switchTo(winnerPageNum);
    }
    else {
        m_roundPager->switchTo(session->state().currentRound);
    }
}

void RoundForm::setWinner(const Player &player)
{
    m_winnerLabel->setText(player.nickname + L" win!");
}

