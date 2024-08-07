#include "QuestionCard.h"
#include "FrameLayout.h"
#include "TextLabel.h"

QuestionCard::QuestionCard(const GameSet::Card &card)
{
    auto *question = new TextLabel(card.question);
    question->setId(L"QuestionLabel");
    question->setMouseTransparent(true);
    question->setShadowed(true);

    auto *frameLayout = new FrameLayout(question);
    frameLayout->setId(L"QuestionFrameLayout");
    frameLayout->adjustWidgetSize(true);
    frameLayout->setMouseTransparent(true);
    frameLayout->setParent(this);
}
