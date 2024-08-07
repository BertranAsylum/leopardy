#include "TimeredCard.h"
#include "Style.h"
#include "direct/Canvas.h"

static const float barHeight = 5.0f;

TimeredCard::TimeredCard()
{
    m_progressStyle.setFillColor({0.8f, 0.8f, 0.8f});
}

void TimeredCard::arm(const std::chrono::duration<double, std::milli> &msec)
{
    m_timer.start(msec);
}

void TimeredCard::disarm()
{
    m_timer.stop();
}

void TimeredCard::onPaint(Canvas *canvas)
{
    Card::onPaint(canvas);

    if (!m_timer.finished()) {
        D2D1_RECT_F bounding = D2D1::RectF(
            float(geometry().x + geometry().width * m_timer.progress() / 2),
            float(geometry().y + geometry().height - barHeight - Style::borderWidth()),
            float(geometry().x + geometry().width - geometry().width * m_timer.progress() / 2),
            float(geometry().y + geometry().height - Style::borderWidth()));
        canvas->drawRect(bounding,
                         m_progressStyle);
    }
}
