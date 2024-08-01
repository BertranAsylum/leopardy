#include "Button.h"

void Button::setCheckable(bool value)
{
    m_checkable = value;
}

bool Button::checkable() const
{
    return m_checkable;
}

bool Button::checked() const
{
    return m_checked;
}

void Button::onMousePress(int x, int y)
{
    Widget::onMousePress(x, y);
}

void Button::onMouseRelease(int x, int y)
{
    m_checked = !m_checked;
    Widget::onMouseRelease(x, y);
}
