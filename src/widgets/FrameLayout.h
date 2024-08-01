#pragma once

#include "widgets/GridLayout.h"

class FrameLayout : public GridLayout {
public:
    FrameLayout(Widget *widget);

private:
    using Widget::addChild;
    using GridLayout::addWidget;
};
