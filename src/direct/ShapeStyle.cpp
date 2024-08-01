#include "ShapeStyle.h"

ShapeStyle::ShapeStyle() :
    m_strokeColor(0.0f, 0.0f, 0.0f),
    m_fillColor(0.0f, 0.0f, 0.0f)
{}

ShapeStyle &ShapeStyle::setStrokeColor(const D2D1::ColorF &color)
{
    m_strokeColor = color;
    m_stroke = true;
    return *this;
}

ShapeStyle &ShapeStyle::setStrokeWidth(float value)
{
    m_strokeWidth = value;
    m_stroke = true;
    return *this;
}

ShapeStyle &ShapeStyle::setFillColor(const D2D1::ColorF &color)
{
    m_fillColor = color;
    m_fill = true;
    return *this;
}

D2D1::ColorF ShapeStyle::strokeColor() const
{
    return m_strokeColor;
}

float ShapeStyle::strokeWidth() const
{
    return m_strokeWidth;
}

D2D1::ColorF ShapeStyle::fillColor() const
{
    return m_fillColor;
}

bool ShapeStyle::fill() const
{
    return m_fill;
}

bool ShapeStyle::stroke() const
{
    return m_stroke;
}
