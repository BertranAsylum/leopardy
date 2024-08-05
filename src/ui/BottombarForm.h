#pragma once

#include <string>

class Widget;
class Pager;
class Toolbar;
class TimeredTextButton;
class TimeredTextInput;
class GameController;

class BottombarForm {
public:
    void setup(GameController *gameController, Widget *parent);

private:
    void resetForLeader();
    void resetForPlayer();

    void setupForLeader();
    void setupForPlayer();

    void updateAnswerPage(const std::wstring &answer);

private:
    GameController *m_gameController = nullptr;
    Pager *m_pager = nullptr;

    TimeredTextButton *m_tryAnswerButton = nullptr;
    TimeredTextInput *m_answerInput = nullptr;
};
