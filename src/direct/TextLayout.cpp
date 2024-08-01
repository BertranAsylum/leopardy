#include "TextLayout.h"

TextLayout &TextLayout::setBounding(float left, float top, float right, float bottom)
{
    m_rect = D2D1::RectF(left, top, right, bottom);
    return *this;
}

TextLayout &TextLayout::setBounding(const D2D1_POINT_2F &center, float width, float height)
{
    m_rect = D2D1::RectF(center.x - width / 2, center.y - height / 2, center.x + width / 2, center.y + height / 2);
    return *this;
}

TextLayout &TextLayout::setBounding(const D2D1_RECT_F &rect)
{
    m_rect = rect;
    return *this;
}

TextLayout &TextLayout::setAlignment(HAlignment horizontal)
{
    m_hAlignment = DWRITE_TEXT_ALIGNMENT(horizontal);
    return *this;
}

TextLayout &TextLayout::setAlignment(VAlignment vertical)
{
    m_vAlignment = DWRITE_PARAGRAPH_ALIGNMENT(vertical);
    return *this;
}

TextLayout & TextLayout::setMargins(float margins)
{
    m_margins = margins;
    return *this;
}

D2D1_RECT_F TextLayout::rect() const
{
    D2D1_RECT_F r(m_rect);
    r.left += m_margins;
    r.top += m_margins;
    r.right -= m_margins;
    r.bottom -= m_margins;
    return r;
}

DWRITE_TEXT_ALIGNMENT TextLayout::hAlignment() const
{
    return m_hAlignment;
}

DWRITE_PARAGRAPH_ALIGNMENT TextLayout::vAlignment() const
{
    return m_vAlignment;
}
