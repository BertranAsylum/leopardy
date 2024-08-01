#pragma once

#include "Widget.h"
#include "direct/ShapeStyle.h"

class Card : public Widget {
public:
    explicit Card();

protected:
    void onPaint(Canvas *canvas) override;

private:
    ShapeStyle m_normalStyle;
    ShapeStyle m_hoveredStyle;
};
