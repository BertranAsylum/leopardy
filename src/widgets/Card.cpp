#include "Card.h"
#include "direct/Canvas.h"

Card::Card()
{
    m_normalStyle.setStrokeWidth(1.0f);
    m_normalStyle.setStrokeColor({0.1f, 0.1f, 0.1f});
    m_normalStyle.setFillColor({0.3f, 0.3f, 0.3f});

    m_hoveredStyle.setStrokeWidth(1.0f);
    m_hoveredStyle.setStrokeColor({0.6f, 0.6f, 0.6f});
    m_hoveredStyle.setFillColor({0.3f, 0.3f, 0.3f});
}

void Card::onPaint(Canvas *canvas)
{
    D2D1_RECT_F bounding = D2D1::RectF(
        float(geometry().x),
        float(geometry().y),
        float(geometry().x + geometry().width),
        float(geometry().y + geometry().height));

    auto &style = hovered()
                      ? m_hoveredStyle
                      : m_normalStyle;

    canvas->drawRoundedRect(D2D1::RoundedRect(
                                bounding,
                                8.0f, 8.0f),
                            style);

    Widget::onPaint(canvas);
}
