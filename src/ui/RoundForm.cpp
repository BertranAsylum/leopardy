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
        if (auto *e = event->as<UiReset>()) {
            reset();
        }
        else if (event->as<PlayerChoosing>()) {
            updateRoundPages();
        }
        else if (auto *e = event->as<QuestionChosen>()) {
            const auto price = m_gameController->gameSession()->gameSet().rounds[e->roundNum].categories[e->categoryNum]
                .cards[e->priceNum].price;
            m_roundCategoryWidgets[e->roundNum][e->categoryNum]->priceButton(price)->hide();

            updateQuestionPage();
            const auto questionPageNum = m_roundPager->pageCount() - 2;
            m_roundPager->switchTo(questionPageNum);
        }
        else if (event->as<PlayerIsRight>() || event->as<PlayerIsWrong>() || event->as<NextRound>()) {
            updateRoundPages();
            m_roundPager->switchTo(m_gameController->gameSession()->state().currentRound);
        }
        else if (auto *e = event->as<PlayerWin>()) {
            updateWinnerPage();
            const auto winnerPageNum = m_roundPager->pageCount() - 1;
            m_roundPager->switchTo(winnerPageNum);
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
    m_roundPager->clearPages();
    m_roundCategoryWidgets.clear();

    const auto *session = m_gameController->gameSession();

    m_questionPage = new GridLayout(6, 8);
    m_questionPage->setId(L"QuestionPage");
    m_questionPage->adjustWidgetSize(true);

    m_winnerLabel = new TextLabel;
    m_winnerLabel->setId(L"WinnerLabel");
    m_winnerLabel->setFontSize(Style::FontSize::Large);
    m_winnerLabel->setShadowed(true);

    auto *winnerPage = new FrameLayout(m_winnerLabel);
    winnerPage->setId(L"WinnerPage");
    winnerPage->adjustWidgetSize(true);

    int roundNum = 0;
    const auto &rounds = session->gameSet().rounds;

    for (auto round : rounds) {
        // TODO: Gentle handle categories
        assert("Game don't support more than 6 categories" && round.categories.size() <= 6);

        auto *roundPage = new GridLayout(2, 3);
        roundPage->setId(L"RoundPage" + std::to_wstring(roundNum));
        roundPage->setMargins(10.0f);
        roundPage->adjustWidgetSize(true);

        std::vector<CategoryCard*> categoryCards;

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
                categoryCards.push_back(cardWidget);

                auto priceNum = 0;
                for (auto &card : category.cards) {
                    auto *priceButton = cardWidget->priceButton(card.price);
                    priceButton->onMouseRelease([this, roundNum, categoryNum, priceNum](int, int)
                    {
                        auto questionChoosen = std::make_shared<QuestionChosen>();
                        questionChoosen->roundNum = roundNum;
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
        m_roundCategoryWidgets.push_back(categoryCards);
        ++roundNum;
    }
    m_roundPager->addPage(m_questionPage);
    m_roundPager->addPage(winnerPage);
    updateRoundPages();

    if (session->state().currentStage == GameSession::State::Stage::ViewingQestion) {
        updateQuestionPage();
        const auto questionPageNum = m_roundPager->pageCount() - 2;
        m_roundPager->switchTo(questionPageNum);
    }
    else if (session->state().currentStage == GameSession::State::Stage::GameFinished) {
        updateWinnerPage();
        const auto winnerPageNum = m_roundPager->pageCount() - 1;
        m_roundPager->switchTo(winnerPageNum);
    }
    else {
        m_roundPager->switchTo(session->state().currentRound);
    }
}

void RoundForm::updateRoundPages()
{
    bool enable =
        m_gameController->gameSession()->state().currentStage == GameSession::State::Stage::ChoosingQuestion
        && m_gameController->thisParticipant()->role() == Participant::Role::Player
        && m_gameController->gameSession()->state().playerNum == m_gameController->gameSession()->thisPlayerNum();

    const auto &rounds = m_roundPager->children();
    for (int i = 0; i < rounds.size() - 2; ++i) {
        for (const auto &c : rounds[i]->children()) {
            c->setEnabled(enable);
        }
    }
}

void RoundForm::updateQuestionPage()
{
    const auto round = m_gameController->gameSession()->state().currentRound;
    const auto categoryNum = m_gameController->gameSession()->state().questionCategoryNum;
    const auto priceNum = m_gameController->gameSession()->state().questionPriceNum;

    const auto card =
        m_gameController->gameSession()->gameSet().rounds[round].categories[categoryNum].cards[priceNum];

    auto *questionCard = new QuestionCard(card);
    questionCard->setId(L"QuestionCard");
    questionCard->disable();

    m_questionPage->clearChildren();
    m_questionPage->addWidget(1, 2, 4, 5, questionCard);
}

void RoundForm::updateWinnerPage()
{
    m_winnerLabel->setText(m_gameController->gameSession()->winner().nickname + L" win!");
}
