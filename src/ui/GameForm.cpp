#include "GameForm.h"
#include "widgets/GridLayout.h"

void GameForm::setup(GameController *gameController, Widget *parent)
{
    auto *topbarWidget = new Widget;
    topbarWidget->setId(L"Topbar");
    topbar.setup(gameController, topbarWidget);

    auto *playgroundWidget = new Widget;
    playgroundWidget->setId(L"Playground");
    playground.setup(gameController, playgroundWidget);

    auto *bottombarWidget = new Widget;
    bottombarWidget->setId(L"Bottombar");
    bottombar.setup(gameController, bottombarWidget);

    auto *rootWidget = new GridLayout(14, 1);
    rootWidget->setId(L"MainFormGridLayout");
    rootWidget->adjustWidgetSize(true);
    rootWidget->setMargins(8.0f);

    rootWidget->addWidget(0, 0, topbarWidget);
    rootWidget->addWidget(1, 0, 12, 0, playgroundWidget);
    rootWidget->addWidget(13, 0, bottombarWidget);
    rootWidget->setParent(parent);
}
