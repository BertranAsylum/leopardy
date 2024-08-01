#include "PlayerCard.h"
#include "GridLayout.h"
#include "TextLabel.h"

PlayerCard::PlayerCard(const Player &player)
{
    m_nickname = player.nickname;

    m_nicknameLabel = new TextLabel(m_nickname);
    m_nicknameLabel->setId(L"NicknameLabel");
    m_nicknameLabel->setMouseTransparent(true);
    setActive(false);

    m_scoreLabel = new TextLabel();
    m_scoreLabel->setId(L"ScoreLabel");
    m_scoreLabel->setMouseTransparent(true);
    setScore(player.score);

    auto *gridLayout = new GridLayout(5, 1);
    gridLayout->setId(L"PlayerGridLayout");
    gridLayout->adjustWidgetSize(true);
    gridLayout->setParent(this);
    gridLayout->setMouseTransparent(true);

    gridLayout->addWidget(0, 0, m_nicknameLabel);
    gridLayout->addWidget(4, 0, m_scoreLabel);
}

void PlayerCard::setActive(bool active)
{
    m_nicknameLabel->setText(active
                                 ? L"\u2666 " + m_nickname + L" \u2666"
                                 : m_nickname);
}

void PlayerCard::setScore(int score)
{
    m_scoreLabel->setText(std::to_wstring(score));
}
