#include "TextButton.h"
#include "Style.h"

#include <direct/Canvas.h>

TextButton::TextButton(const std::wstring &text) :
    m_text(text)
{
    m_normalStyle.setStrokeWidth(Style::borderWidth());
    m_normalStyle.setStrokeColor({0.1f, 0.1f, 0.1f});
    m_normalStyle.setFillColor({0.25f, 0.25f, 0.25f});

    m_hoveredStyle.setStrokeWidth(Style::borderWidth());
    m_hoveredStyle.setStrokeColor({0.1f, 0.1f, 0.1f});
    m_hoveredStyle.setFillColor({0.3f, 0.3f, 0.3f});

    m_pressedStyle.setStrokeWidth(Style::borderWidth());
    m_pressedStyle.setStrokeColor({0.1f, 0.1f, 0.1f});
    m_pressedStyle.setFillColor({0.15f, 0.15f, 0.15f});

    m_font = Style::font();
}

void TextButton::onPaint(Canvas *canvas)
{
    D2D1_RECT_F bounding = D2D1::RectF(
        float(geometry().x),
        float(geometry().y),
        float(geometry().x + geometry().width),
        float(geometry().y + geometry().height));

    auto &style = pressed()
                      ? m_pressedStyle
                      : hovered()
                      ? m_hoveredStyle
                      : m_normalStyle;

    canvas->drawRoundedRect(D2D1::RoundedRect(
                                bounding,
                                8.0f, 8.0f),
                            style);

    TextLayout layout;
    layout.setBounding(bounding);
    layout.setAlignment(TextLayout::HAlignment::Center);
    layout.setAlignment(TextLayout::VAlignment::Center);

    const auto &color = Style::color(Style::ColorTag::Foreground);
    canvas->drawText(m_text, m_font, layout,
                     enabled()
                         ? color
                         : Style::color(color, Style::ColorShift::MuchDarker));

    Button::onPaint(canvas);
}
