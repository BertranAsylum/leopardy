#include "BottombarForm.h"

#include "widgets/Toolbar.h"
#include "widgets/FrameLayout.h"

void BottombarForm::setup(GameController *gameController, Widget *parent)
{
    auto *topbar = new Toolbar(8);
    topbar->setId(L"BottombarWidget");

    auto *frameLayout = new FrameLayout(topbar);
    frameLayout->setId(L"BottombarFrameLayout");
    frameLayout->adjustWidgetSize(true);
    frameLayout->setParent(parent);
}
