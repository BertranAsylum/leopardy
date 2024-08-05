#include "BottombarForm.h"

#include "widgets/FrameLayout.h"
#include "widgets/TimeredTextButton.h"
#include "widgets/TimeredTextInput.h"
#include "widgets/Toolbar.h"
#include "widgets/Pager.h"
#include "interfaces/GameController.h"

enum class LeaderPage {
    Blank = 0,
    StartGame,
    NextRound,
    ShowWinner,
    AnswerPage,
    Count
};

enum class PlayerPage {
    Blank = 0,
    TryAnswer,
    TypeAnswer,
    Count
};

void BottombarForm::setup(GameController *gameController, Widget *parent)
{
    m_gameController = gameController;

    m_pager = new Pager;
    m_pager->setId(L"Pager");

    auto *frameLayout = new FrameLayout(m_pager);
    frameLayout->setId(L"FrameLayout");
    frameLayout->adjustWidgetSize(true);
    frameLayout->setParent(parent);

    m_gameController->onEvent([this](const std::shared_ptr<GameEvent> &event)
    {
        if (event->as<UiReset>()) {
            switch (m_gameController->thisParticipant()->role()) {
                case Participant::Role::Leader:
                    setupForLeader();
                    break;
                case Participant::Role::Player:
                    setupForPlayer();
                    break;
                case Participant::Role::Observer:
                    auto *blankBar = new Toolbar(1);
                    blankBar->setId(L"BlankToolbar");
                    auto *blankPage = new FrameLayout(blankBar);
                    blankPage->setId(L"BlankPage");
                    m_pager->addPage(blankPage);
                    break;
            }
        }
    });
}

void BottombarForm::resetForLeader()
{
    auto *blankBar = new Toolbar(1);
    blankBar->setId(L"BlankToolbar");
    auto *blankPage = new FrameLayout(blankBar);
    blankPage->adjustWidgetSize(true);
    blankPage->setId(L"BlankPage");

    auto *startGameButton = new TextButton(L"Start game");
    startGameButton->setId(L"StartGameButton");
    auto *startGameBar = new Toolbar(1);
    startGameBar->setId(L"StartGameToolbar");
    startGameBar->setWidget(0, startGameButton);
    auto *startGamePage = new FrameLayout(startGameBar);
    startGamePage->adjustWidgetSize(true);
    startGamePage->setId(L"StartGamePage");

    auto *nextRoundButton = new TextButton(L"Next Round");
    nextRoundButton->setId(L"NextRoundButton");
    auto *nextRoundBar = new Toolbar(1);
    nextRoundBar->setId(L"NextRoundToolbar");
    nextRoundBar->setWidget(0, nextRoundButton);
    auto *nextRoundPage = new FrameLayout(nextRoundBar);
    nextRoundPage->setId(L"NextRoundPage");

    auto *showWinnerButton = new TextButton(L"Show winner");
    showWinnerButton->setId(L"ShowWinnerButton");
    auto *showWinnerBar = new Toolbar(1);
    showWinnerBar->setId(L"ShowWinnerToolbar");
    showWinnerBar->setWidget(0, showWinnerButton);
    auto *showWinnerPage = new FrameLayout(showWinnerBar);
    showWinnerPage->adjustWidgetSize(true);
    showWinnerPage->setId(L"ShowWinnerPage");

    auto *noButton = new TextButton(L"No");
    noButton->setId(L"NoButton");
    auto *yesButton = new TextButton(L"Yes");
    yesButton->setId(L"YesButton");
    m_answerInput = new TimeredTextInput;
    m_answerInput->setId(L"AnswerText");
    m_answerInput->setPlaceholder(L"Player's answer");
    m_answerInput->disable();

    auto *answerBar = new Toolbar(8);
    answerBar->setId(L"AnswerToolbar");
    answerBar->setWidget(0, noButton);
    answerBar->setWidget(1, 6, m_answerInput);
    answerBar->setWidget(7, yesButton);
    auto *answerPage = new FrameLayout(answerBar);
    answerPage->adjustWidgetSize(true);
    answerPage->setId(L"AnswerPage");


    // NOTE: LeaderPage enum order
    m_pager->clearChildren();
    m_pager->addPage(blankPage);
    m_pager->addPage(startGamePage);
    m_pager->addPage(nextRoundPage);
    m_pager->addPage(showWinnerPage);
    m_pager->addPage(answerPage);

    startGameButton->onMouseRelease([this, startGameButton](int, int)
    {
        m_gameController->pushEvent(std::make_shared<GameStarted>());
        startGameButton->disable();
    });

    nextRoundButton->onMouseRelease([this, nextRoundButton](int, int)
    {
        m_gameController->pushEvent(std::make_shared<NextRound>());
        nextRoundButton->disable();
    });

    showWinnerButton->onMouseRelease([this, showWinnerButton](int, int)
    {
        auto playerWin = std::make_shared<PlayerWin>();
        playerWin->playerNum = m_gameController->gameSession()->deduceWinner();
        m_gameController->pushEvent(playerWin);
        showWinnerButton->disable();
    });

    noButton->onMouseRelease([this, noButton](int, int)
    {
        auto playerIsWrong = std::make_shared<PlayerIsWrong>();
        playerIsWrong->scoreDecrease = m_gameController->gameSession()->card().price;
        m_gameController->pushEvent(playerIsWrong);
        noButton->disable();
    });

    yesButton->onMouseRelease([this, yesButton](int, int)
    {
        auto playerIsRight = std::make_shared<PlayerIsRight>();
        playerIsRight->scoreIncrease = m_gameController->gameSession()->card().price;
        m_gameController->pushEvent(playerIsRight);
        yesButton->disable();
    });
}

void BottombarForm::resetForPlayer()
{
    auto *blankBar = new Toolbar(1);
    blankBar->setId(L"BlankToolbar");
    auto *blankPage = new FrameLayout(blankBar);
    blankPage->adjustWidgetSize(true);
    blankPage->setId(L"BlankPage");

    m_tryAnswerButton = new TimeredTextButton(L"Try to answer");
    m_tryAnswerButton->setId(L"TryAnswerButton");
    auto *tryAnswerBar = new Toolbar(1);
    tryAnswerBar->setId(L"TryAnswerToolbar");
    tryAnswerBar->setWidget(0, m_tryAnswerButton);
    auto *tryAnswerPage = new FrameLayout(tryAnswerBar);
    tryAnswerPage->adjustWidgetSize(true);
    tryAnswerPage->setId(L"TryAnswerPage");

    m_answerInput = new TimeredTextInput;
    m_answerInput->setId(L"TypeAnswerInput");
    m_answerInput->setPlaceholder(L"Type your answer");

    auto *typeAnswerBar = new Toolbar(1);
    typeAnswerBar->setId(L"TypeAnswerToolbar");
    typeAnswerBar->setWidget(0, m_answerInput);
    auto *typeAnswerPage = new FrameLayout(typeAnswerBar);
    typeAnswerPage->adjustWidgetSize(true);
    typeAnswerPage->setId(L"TypeAnswerPage");


    // NOTE: PlayerPage enum order
    m_pager->clearChildren();
    m_pager->addPage(blankPage);
    m_pager->addPage(tryAnswerPage);
    m_pager->addPage(typeAnswerPage);

    switch (m_gameController->gameSession()->state().currentStage) {
        case GameSession::State::ViewingQestion:
            m_pager->switchTo(static_cast<int>(PlayerPage::TryAnswer));
            break;
        case GameSession::State::PlayerAnswering:
            if (m_gameController->gameSession()->state().playerNum
                == m_gameController->gameSession()->thisPlayerNum()) {
                m_pager->switchTo(static_cast<int>(PlayerPage::TypeAnswer));
            }
            break;
        default:
            break;
    }

    m_tryAnswerButton->onMouseRelease([this](int, int)
    {
        auto answerRequest = std::make_shared<PlayerAnswerRequest>();
        answerRequest->playerNum = m_gameController->gameSession()->thisPlayerNum();
        m_gameController->pushEvent(answerRequest);
        m_tryAnswerButton->disable();
    });

    m_answerInput->onTextChanged([this](const std::wstring &text)
    {
        auto answer = std::make_shared<PlayerTypingAnswer>();
        answer->answer = text;
        m_gameController->pushEvent(answer);
    });
}

void BottombarForm::setupForLeader()
{
    m_gameController->onEvent([this](const std::shared_ptr<GameEvent> &event)
    {
        if (event->as<PlayerJoined>()) {
            if (m_gameController->gameSession()->state().currentStage == GameSession::State::Lobby) {
                m_pager->switchTo(static_cast<int>(LeaderPage::StartGame));
            }
        }
        else if (event->as<GameStarted>()
            || event->as<PlayerChoosing>()
            || event->as<QuestionChosen>()
            || event->as<NextRound>()
            || event->as<PlayerWin>()) {
            m_pager->switchTo(static_cast<int>(LeaderPage::Blank));
        }
        else if (event->as<PlayerIsRight>() || event->as<PlayerIsWrong>()) {
            const auto stage = m_gameController->gameSession()->state().currentStage;
            if (stage == GameSession::State::Stage::RoundFinished) {
                m_pager->switchTo(static_cast<int>(LeaderPage::NextRound));
                m_pager->enable();
            }
            else if (stage == GameSession::State::Stage::GameFinished) {
                m_pager->switchTo(static_cast<int>(LeaderPage::ShowWinner));
                m_pager->enable();
            }
            else {
                m_pager->switchTo(static_cast<int>(LeaderPage::Blank));
            }
        }
        else if (event->as<PlayerAnswering>()) {
            m_pager->switchTo(static_cast<int>(LeaderPage::AnswerPage));
            m_pager->enable();
            m_answerInput->disable();
            m_answerInput->clearText();
        }
        else if (const auto *e = event->as<PlayerTypingAnswer>()) {
            updateAnswerPage(e->answer);
        }
    });

    resetForLeader();
}

void BottombarForm::setupForPlayer()
{
    m_gameController->onEvent([this](const std::shared_ptr<GameEvent> &event)
    {
        if (event->as<GameStarted>()
            || event->as<PlayerChoosing>()
            || event->as<PlayerIsRight>()
            || event->as<PlayerIsWrong>()
            || event->as<NextRound>()
            || event->as<PlayerWin>()) {
            m_pager->switchTo(static_cast<int>(PlayerPage::Blank));
        }
        else if (event->as<QuestionChosen>()) {
            m_tryAnswerButton->arm(3s);
            m_pager->switchTo(static_cast<int>(PlayerPage::TryAnswer));
        }
        else if (auto *e = event->as<PlayerAnswering>()) {
            if (e->playerNum == m_gameController->gameSession()->thisPlayerNum()) {
                m_answerInput->clearText();
                m_answerInput->arm(10s);
                m_pager->switchTo(static_cast<int>(PlayerPage::TypeAnswer));
            }
            else {
                m_pager->switchTo(static_cast<int>(PlayerPage::Blank));
            }
        }
    });

    resetForPlayer();
}

void BottombarForm::updateAnswerPage(const std::wstring &answer)
{
    m_answerInput->setText(answer);
}
