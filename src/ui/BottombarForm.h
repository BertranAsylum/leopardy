#pragma once

#include <string>

class Widget;
class Pager;
class Toolbar;
class TextButton;
class TextInput;
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

    TextInput *m_answerInput = nullptr;
};
