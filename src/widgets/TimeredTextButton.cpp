#include "TimeredTextButton.h"
#include "Style.h"
#include "direct/Canvas.h"

static const float barHeight = 5.0f;

TimeredTextButton::TimeredTextButton(const std::wstring &text)
    : TextButton(text)
{
    m_progressStyle.setFillColor({0.8f, 0.8f, 0.8f});
}

void TimeredTextButton::arm(const std::chrono::duration<double, std::milli> &msec)
{
    disable();
    m_timer.start(msec);
}

void TimeredTextButton::onPaint(Canvas *canvas)
{
    TextButton::onPaint(canvas);

    if (m_timer.finished()) {
        enable();
    }
    else {
        D2D1_RECT_F bounding = D2D1::RectF(
            float(geometry().x + geometry().width * m_timer.progress() / 2),
            float(geometry().y + geometry().height - barHeight - Style::borderWidth()),
            float(geometry().x + geometry().width - geometry().width * m_timer.progress() / 2),
            float(geometry().y + geometry().height - Style::borderWidth()));
        canvas->drawRect(bounding,
                         m_progressStyle);
    }
}
