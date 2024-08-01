#include "Font.h"

Font &Font::setFamily(const std::wstring &name)
{
    m_family = name;
    return *this;
}

Font &Font::setSize(float value)
{
    m_size = value;
    return *this;
}

Font &Font::setWeight(Weight value)
{
    m_weight = DWRITE_FONT_WEIGHT(value);
    return *this;
}

Font &Font::setStyle(Style value)
{
    m_style = DWRITE_FONT_STYLE(value);
    return *this;
}

std::wstring Font::family() const
{
    return m_family;
}

float Font::size() const
{
    return m_size;
}

DWRITE_FONT_WEIGHT Font::weight() const
{
    return m_weight;
}

DWRITE_FONT_STYLE Font::style() const
{
    return m_style;
}
