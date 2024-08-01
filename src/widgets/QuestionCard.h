#pragma once

#include "Card.h"
#include "GameSet.h"

class QuestionCard : public Card {
public:
    explicit QuestionCard(const GameSet::Card &card);
};
