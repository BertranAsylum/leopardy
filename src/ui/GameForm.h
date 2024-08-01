#pragma once

#include "ui/TopbarForm.h"
#include "ui/PlaygroundForm.h"
#include "ui/BottombarForm.h"

class GameController;

class GameForm {
public:
    void setup(GameController *gameController, Widget *parent);

    TopbarForm topbar;
    PlaygroundForm playground;
    BottombarForm bottombar;
};
