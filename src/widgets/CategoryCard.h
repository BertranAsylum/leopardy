#pragma once

#include "Card.h"
#include "GameSet.h"

#include <map>

class Button;
class TextButton;

class CategoryCard : public Card {
public:
    CategoryCard(const std::wstring &name, const GameSet::Category &category);
    Button *priceButton(int price);

private:
    std::map<int, TextButton*> m_priceButtons;
};
