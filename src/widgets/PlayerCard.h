#pragma once

#include "TimeredCard.h"
#include "Participant.h"

class TextLabel;

class PlayerCard : public TimeredCard {
public:
    explicit PlayerCard(const Player &player);
    void setActive(bool active);
    void setScore(int score);

private:
    std::wstring m_nickname;
    TextLabel *m_nicknameLabel = nullptr;
    TextLabel *m_scoreLabel = nullptr;
};
