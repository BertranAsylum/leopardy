#pragma once

#include <string>

class Widget;
class TextLabel;
class GameStarter;

class ErrorForm {
public:
    void setup(GameStarter *gameStarter, Widget *parent);
    void setMessage(const std::wstring &message);

private:
    TextLabel *m_messageLabel = nullptr;
};
