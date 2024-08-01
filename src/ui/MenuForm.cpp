#include "MenuForm.h"

#include <GameOptionsLoader.h>
#include <interfaces/GameStarter.h>

#include "widgets/Pager.h"
#include "widgets/GridLayout.h"
#include "widgets/FrameLayout.h"
#include "widgets/TextButton.h"
#include "widgets/TextInput.h"

static constexpr float margins = 20.0f;

void MenuForm::setup(GameStarter *gameStarter, Widget *parent)
{
    auto *createGameButton = new TextButton(L"Create game");
    createGameButton->setId(L"CreateGameButton");
    auto *joinGameButton = new TextButton(L"Join game");
    joinGameButton->setId(L"JoinGameButton");
    auto *quitButton = new TextButton(L"Quit");
    quitButton->setId(L"QuitButton");

    auto *mainPage = new GridLayout(9, 1);
    mainPage->setId(L"MainPage");
    mainPage->adjustWidgetSize(true);
    mainPage->setMargins(margins);

    mainPage->addWidget(3, 0, createGameButton);
    mainPage->addWidget(4, 0, joinGameButton);
    mainPage->addWidget(5, 0, quitButton);

    const auto opts = gameStarter->lastOptions();

    auto *leaderNicknameInput = new TextInput();
    leaderNicknameInput->setId(L"LeaderNicknameTextInput");
    leaderNicknameInput->setPlaceholder(L"Nickname");
    leaderNicknameInput->setMaxLength(50);
    leaderNicknameInput->setText(opts.nickname);

    auto *createdServerAddressInput = new TextInput();
    createdServerAddressInput->setId(L"CreateServerAddressTextInput");
    createdServerAddressInput->setPlaceholder(L"Server address (host:port)");
    createdServerAddressInput->setMaxLength(50);
    createdServerAddressInput->setCharFilter(L"[A-Za-z0-9.:]");
    createdServerAddressInput->setText(opts.serverAddress);

    auto *startCreatedGameButton = new TextButton(L"Start");
    startCreatedGameButton->setId(L"StartCreatedGameButton");
    auto *backFromCreateGameButton = new TextButton(L"Back");
    backFromCreateGameButton->setId(L"BackFromCreatedGameButton");

    auto *createGamePage = new GridLayout(9, 1);
    createGamePage->setId(L"CreateGamePage");
    createGamePage->adjustWidgetSize(true);
    createGamePage->setMargins(margins);

    createGamePage->addWidget(2, 0, leaderNicknameInput);
    createGamePage->addWidget(3, 0, createdServerAddressInput);
    createGamePage->addWidget(4, 0, startCreatedGameButton);
    createGamePage->addWidget(5, 0, backFromCreateGameButton);


    auto *playerNicknameInput = new TextInput();
    playerNicknameInput->setId(L"PlayerNicknameTextInput");
    playerNicknameInput->setPlaceholder(L"Nickname");
    playerNicknameInput->setMaxLength(50);
    playerNicknameInput->setText(opts.nickname);

    auto *joinedServerAddressInput = new TextInput();
    joinedServerAddressInput->setId(L"JoinServerAddressTextInput");
    joinedServerAddressInput->setPlaceholder(L"Server address (host:port)");
    joinedServerAddressInput->setMaxLength(50);
    joinedServerAddressInput->setCharFilter(L"[A-Za-z0-9.:]");
    joinedServerAddressInput->setText(opts.serverAddress);

    auto *startJoinedGameButton = new TextButton(L"Join");
    startJoinedGameButton->setId(L"StartJoinedGameButton");
    auto *backFromJoinGameButton = new TextButton(L"Back");
    backFromJoinGameButton->setId(L"BackFromJoinedGameButton");

    auto *joinGamePage = new GridLayout(9, 1);
    joinGamePage->setId(L"JoinGamePage");
    joinGamePage->adjustWidgetSize(true);
    joinGamePage->setMargins(margins);

    joinGamePage->addWidget(2, 0, playerNicknameInput);
    joinGamePage->addWidget(3, 0, joinedServerAddressInput);
    joinGamePage->addWidget(4, 0, startJoinedGameButton);
    joinGamePage->addWidget(5, 0, backFromJoinGameButton);


    auto *pager = new Pager;
    pager->setId(L"MenuPager");
    pager->addPage(mainPage);
    pager->addPage(createGamePage);
    pager->addPage(joinGamePage);


    auto *frameLayout = new FrameLayout(pager);
    frameLayout->setId(L"MenuFrameLayout");
    frameLayout->adjustWidgetSize(true);
    frameLayout->setParent(parent);


    createGameButton->onMouseRelease([pager](int, int) { pager->switchTo(1); });
    backFromCreateGameButton->onMouseRelease([pager](int, int) { pager->switchTo(0); });
    startCreatedGameButton->onMouseRelease([gameStarter, leaderNicknameInput, createdServerAddressInput](int, int)
    {
        gameStarter->createGame({
            .nickname = leaderNicknameInput->text(),
            .serverAddress = createdServerAddressInput->text()
        });
    });

    joinGameButton->onMouseRelease([pager](int, int) { pager->switchTo(2); });
    backFromJoinGameButton->onMouseRelease([pager](int, int) { pager->switchTo(0); });
    startJoinedGameButton->onMouseRelease([gameStarter, playerNicknameInput, joinedServerAddressInput](int, int)
    {
        gameStarter->joinGameAsPlayer({
            .nickname = playerNicknameInput->text(),
            .serverAddress = joinedServerAddressInput->text()
        });
    });

    quitButton->onMouseRelease([](int, int) { exit(0); });
}
