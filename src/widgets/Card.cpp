#include "Card.h"
#include "direct/Canvas.h"

Card::Card()
{
    m_style.setStrokeWidth(1.0f);
    m_style.setStrokeColor({0.1f, 0.1f, 0.1f});
    m_style.setFillColor({0.3f, 0.3f, 0.3f});
}

void Card::onPaint(Canvas *canvas)
{
    D2D1_RECT_F bounding = D2D1::RectF(
        float(geometry().x),
        float(geometry().y),
        float(geometry().x + geometry().width),
        float(geometry().y + geometry().height));

    canvas->drawRoundedRect(D2D1::RoundedRect(
        bounding,
        8.0f, 8.0f),
        m_style);

    Widget::onPaint(canvas);
}
