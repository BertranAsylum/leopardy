#pragma once

#include "TextButton.h"
#include "utils/Timer.h"

class TimeredTextButton : public TextButton {
public:
    explicit TimeredTextButton(const std::wstring &text);
    void arm(const std::chrono::duration<double, std::milli> &msec);

protected:
    void onPaint(Canvas *canvas) override;

private:
    Timer m_timer;
    ShapeStyle m_progressStyle;
};
