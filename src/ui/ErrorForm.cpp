#include "ErrorForm.h"

#include "interfaces/GameStarter.h"
#include "widgets/GridLayout.h"
#include "widgets/TextLabel.h"
#include "widgets/TextButton.h"

static constexpr float margins = 20.0f;

void ErrorForm::setup(GameStarter *gameStarter, Widget *parent)
{
    m_messageLabel = new TextLabel(L"");
    m_messageLabel->setId(L"MessageLabel");

    auto *backToMenuButton = new TextButton(L"Back to menu");
    backToMenuButton->setId(L"BackToMenuButton");

    auto *gridLayout = new GridLayout(9, 1);
    gridLayout->setId(L"GridLayout");
    gridLayout->adjustWidgetSize(true);
    gridLayout->setMargins(margins);
    gridLayout->setParent(parent);

    gridLayout->addWidget(3, 0, 4, 0, m_messageLabel);
    gridLayout->addWidget(5, 0, backToMenuButton);

    backToMenuButton->onMouseRelease([gameStarter](int, int)
    {
        gameStarter->quitToMenu();
    });
}

void ErrorForm::setMessage(const std::wstring &message)
{
    m_messageLabel->setText(message);
}
