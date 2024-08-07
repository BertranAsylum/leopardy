#pragma once

#include "Card.h"
#include "utils/Timer.h"

class TimeredCard : public Card {
public:
    explicit TimeredCard();
    void arm(const std::chrono::duration<double, std::milli> &msec);
    void disarm();

protected:
    void onPaint(Canvas *canvas) override;

private:
    Timer m_timer;
    ShapeStyle m_progressStyle;
};
