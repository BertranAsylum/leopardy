#include "MainForm.h"

#include "Game.h"
#include "widgets/Pager.h"
#include "widgets/FrameLayout.h"

void MainForm::setup(Game *game, Widget *parent)
{
    auto *menuWidget = new Widget;
    menuWidget->setId(L"MenuPageWidget");
    menuForm.setup(game, menuWidget);
    auto *menuPage = new FrameLayout(menuWidget);
    menuPage->setId(L"MenuPageFrameLayout");
    menuPage->adjustWidgetSize(true);

    auto *gameWidget = new Widget;
    gameWidget->setId(L"GamePageWidget");
    gameForm.setup(game, gameWidget);
    auto *gamePage = new FrameLayout(gameWidget);
    gamePage->setId(L"GamePageFrameLayout");
    gamePage->adjustWidgetSize(true);

    auto *errorWidget = new Widget;
    errorWidget->setId(L"ErrorPageWidget");
    errorForm.setup(game, errorWidget);
    auto *errorPage = new FrameLayout(errorWidget);
    errorPage->setId(L"ErrorPageFrameLayout");
    errorPage->adjustWidgetSize(true);

    m_pager = new Pager;
    m_pager->setId(L"MainFormPager");
    m_pager->addPage(menuPage);
    m_pager->addPage(gamePage);
    m_pager->addPage(errorPage);

    auto *frameLayout = new FrameLayout(m_pager);
    frameLayout->setId(L"MainFrameLayout");
    frameLayout->adjustWidgetSize(true);
    frameLayout->setParent(parent);
}

void MainForm::showMenu()
{
    m_pager->switchTo(0);
}

void MainForm::showGame()
{
    m_pager->switchTo(1);
}

void MainForm::showError(const std::wstring &message)
{
    errorForm.setMessage(message);
    m_pager->switchTo(2);
}
