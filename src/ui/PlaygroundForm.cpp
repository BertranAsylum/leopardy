#include "PlaygroundForm.h"

#include "widgets/GridLayout.h"
#include "widgets/FrameLayout.h"

void PlaygroundForm::setup(GameController *gameController, Widget *parent)
{
    auto *roundWidget = new Widget;
    roundWidget->setId(L"RoundWidget");
    m_roundForm.setup(gameController, roundWidget);

    auto *playerWidget = new Widget;
    playerWidget->setId(L"PlayerWidget");
    m_playerForm.setup(gameController, playerWidget);

    auto *gridLayout = new GridLayout(4, 1);
    gridLayout->setId(L"PlaygroundGridLayout");
    gridLayout->adjustWidgetSize(true);
    gridLayout->addWidget(0, 0, 2, 0, roundWidget);
    gridLayout->addWidget(3, 0, 3, 0, playerWidget);

    auto *frame = new FrameLayout(gridLayout);
    frame->setId(L"PlaygroundFrameLayout");
    frame->adjustWidgetSize(true);
    frame->setParent(parent);
}
