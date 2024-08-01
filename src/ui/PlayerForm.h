#pragma once

class GameController;
class Widget;
class GridLayout;

class PlayerForm {
public:
    void setup(GameController *gameController, Widget *parent);

private:
    void reset();
    void updatePlayerGrid();
    void togglePlayerGrid(bool enable);
    void updatePlayersScore();

private:
    GameController *m_gameController = nullptr;
    GridLayout *m_playerGrid = nullptr;
};
