#pragma once

#include "Widget.h"
#include "direct/ShapeStyle.h"

class GridLayout;
class Toolbar : public Widget {
public:
    ~Toolbar() override = default;
    Toolbar(int size);

    void setWidget(int index, Widget *widget);
    void setWidget(int indexFrom, int indexTo, Widget *widget);

protected:
    void onPaint(Canvas *canvas) override;

private:
    ShapeStyle m_style;
    GridLayout *m_grid = nullptr;
};
