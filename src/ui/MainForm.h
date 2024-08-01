#pragma once

#include "MenuForm.h"
#include "GameForm.h"
#include "ErrorForm.h"

class Widget;
class Pager;
class Game;

class MainForm {
public:
    void setup(Game *game, Widget *parent);

    void showMenu();
    void showGame();
    void showError(const std::wstring &message);

    MenuForm menuForm;
    GameForm gameForm;
    ErrorForm errorForm;

private:
    Pager *m_pager;
};
