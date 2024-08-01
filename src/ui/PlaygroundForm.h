#pragma once

#include "ui/RoundForm.h"
#include "ui/PlayerForm.h"

class Widget;

class PlaygroundForm {
public:
    void setup(GameController *gameController, Widget *parent);

private:
    RoundForm m_roundForm;
    PlayerForm m_playerForm;
};
