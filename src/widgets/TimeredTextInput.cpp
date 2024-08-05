#include "TimeredTextInput.h"
#include "Style.h"
#include "direct/Canvas.h"

static const float barHeight = 5.0f;

TimeredTextInput::TimeredTextInput()
{
    m_progressStyle.setFillColor({0.2f, 0.2f, 0.2f});
}

void TimeredTextInput::arm(const std::chrono::duration<double, std::milli> &msec)
{
    enable();
    m_timer.start(msec);
}

void TimeredTextInput::onPaint(Canvas *canvas)
{
    TextInput::onPaint(canvas);

    if (m_timer.finished()) {
        disable();
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
