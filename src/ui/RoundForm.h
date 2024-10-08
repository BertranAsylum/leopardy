#pragma once

#include <vector>

class GameController;
class Widget;
class Pager;
class GridLayout;
class TextLabel;
class CategoryCard;

class RoundForm {
public:
    void setup(GameController *gameController, Widget *parent);

private:
    void reset();
    void updateRoundPages();
    void updateQuestionPage();
    void updateWinnerPage();

private:
    GameController *m_gameController = nullptr;
    Pager *m_roundPager = nullptr;
    GridLayout *m_questionPage = nullptr;
    TextLabel *m_winnerLabel = nullptr;
    std::vector<std::vector<CategoryCard*>> m_roundCategoryWidgets;
};
