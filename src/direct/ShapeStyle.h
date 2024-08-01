#pragma once

#include <d2d1.h>

class ShapeStyle {
public:
    ShapeStyle();

    ShapeStyle &setStrokeColor(const D2D1::ColorF &color);
    ShapeStyle &setStrokeWidth(float value);
    ShapeStyle &setFillColor(const D2D1::ColorF &color);

    D2D1::ColorF strokeColor() const;
    float strokeWidth() const;
    D2D1::ColorF fillColor() const;
    bool fill() const;
    bool stroke() const;

private:
    D2D1::ColorF m_strokeColor;
    float m_strokeWidth = 1.0f;
    D2D1::ColorF m_fillColor;
    bool m_stroke = false;
    bool m_fill = false;
};

