#pragma once

#include "Card.h"
#include "Participant.h"

class TextLabel;

class PlayerCard : public Card {
public:
    explicit PlayerCard(const Player &player);
    void setScore(int score);

private:
    TextLabel *m_scoreLabel = nullptr;
};
