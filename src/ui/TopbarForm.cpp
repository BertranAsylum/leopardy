#include "TopbarForm.h"

#include "widgets/Toolbar.h"
#include "widgets/FrameLayout.h"

void TopbarForm::setup(GameController *gameController, Widget *parent)
{
    auto *topbar = new Toolbar(8);
    topbar->setId(L"TopbarWidget");

    auto *frameLayout = new FrameLayout(topbar);
    frameLayout->setId(L"TopbarFrameLayout");
    frameLayout->adjustWidgetSize(true);
    frameLayout->setParent(parent);
}
