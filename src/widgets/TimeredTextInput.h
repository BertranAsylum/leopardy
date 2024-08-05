#pragma once

#include "TextInput.h"
#include "utils/Timer.h"

class TimeredTextInput : public TextInput {
public:
    explicit TimeredTextInput();
    void arm(const std::chrono::duration<double, std::milli> &msec);

protected:
    void onPaint(Canvas *canvas) override;

private:
    Timer m_timer;
    ShapeStyle m_progressStyle;
};
