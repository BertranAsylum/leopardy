#include "CategoryCard.h"

#include "FrameLayout.h"
#include "GridLayout.h"
#include "TextButton.h"
#include "TextLabel.h"

CategoryCard::CategoryCard(const std::wstring &name, const GameSet::Category &category)
{
    auto *widget = new Widget;
    widget->setId(L"Widget");

    auto *categoryNameLabel = new TextLabel(name);
    categoryNameLabel->setId(L"CategoryNameLabel");
    categoryNameLabel->setShadowed(true);

    auto *gridLayout = new GridLayout(category.cards.size() + 2, 1);
    gridLayout->setId(L"GridLayout");
    gridLayout->setParent(widget);
    gridLayout->setMargins(5.0f);
    gridLayout->adjustWidgetSize(true);
    gridLayout->addWidget(0, 0, categoryNameLabel);

    int num = 0;
    for (auto &card : category.cards) {
        auto *priceButton = new TextButton(std::to_wstring(card.price));
        priceButton->setId(L"PriceButton" + std::to_wstring(num));
        priceButton->setVisible(!card.used);
        gridLayout->addWidget(num + 2, 0, priceButton);
        m_priceButtons[card.price] = priceButton;
        ++num;
    }

    auto *frameLayout = new FrameLayout(widget);
    frameLayout->setId(L"FrameLayout");
    frameLayout->setMargins(10.0f);
    frameLayout->adjustWidgetSize(true);
    frameLayout->setParent(this);
}

Button *CategoryCard::priceButton(int price)
{
    auto buttonIt = m_priceButtons.find(price);
    if (buttonIt != m_priceButtons.end()) {
        return buttonIt->second;
    }
    return nullptr;
}
