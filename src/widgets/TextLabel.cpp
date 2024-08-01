#include "TextLabel.h"
#include "Style.h"
#include "direct/Canvas.h"
#include "direct/TextLayout.h"

TextLabel::TextLabel(const std::wstring &text) :
    m_text(text)
{
    m_font = Style::font();
}

void TextLabel::setText(const std::wstring &text)
{
    m_text = text;
}

void TextLabel::onPaint(Canvas *canvas)
{
    D2D1_RECT_F bounding = D2D1::RectF(
        float(geometry().x),
        float(geometry().y),
        float(geometry().x + geometry().width),
        float(geometry().y + geometry().height));

    TextLayout layout;
    layout.setBounding(bounding);
    layout.setAlignment(TextLayout::HAlignment::Center);
    layout.setAlignment(TextLayout::VAlignment::Center);

    canvas->drawText(m_text, m_font, layout, Style::color(Style::ColorTag::Foreground));

    Widget::onPaint(canvas);
}
