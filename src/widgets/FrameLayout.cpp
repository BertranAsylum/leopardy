#include "FrameLayout.h"

FrameLayout::FrameLayout(Widget *widget) :
    GridLayout(1, 1)
{
    addWidget(0, 0, widget);
}