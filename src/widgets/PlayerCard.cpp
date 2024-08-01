#include "PlayerCard.h"
#include "GridLayout.h"
#include "TextLabel.h"

PlayerCard::PlayerCard(const Player &player)
{
    auto *nicknameLabel = new TextLabel(player.nickname);
    nicknameLabel->setId(L"NicknameLabel");

    m_scoreLabel = new TextLabel();
    m_scoreLabel->setId(L"ScoreLabel");
    setScore(player.score);

    auto *gridLayout = new GridLayout(5, 1);
    gridLayout->setId(L"PlayerGridLayout");
    gridLayout->adjustWidgetSize(true);
    gridLayout->setParent(this);

    gridLayout->addWidget(0, 0, nicknameLabel);
    gridLayout->addWidget(4, 0, m_scoreLabel);
}

void PlayerCard::setScore(int score)
{
    m_scoreLabel->setText(std::to_wstring(score));
}
