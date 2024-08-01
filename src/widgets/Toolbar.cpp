#include "Toolbar.h"
#include "GridLayout.h"
#include "direct/Canvas.h"

Toolbar::Toolbar(int size)
{
    m_style.setFillColor({0.25f, 0.25f, 0.25f});
    m_grid = new GridLayout(1, size);
    m_grid->setId(id() + L"GridLayout");
    m_grid->adjustWidgetSize(true);
    addChild(m_grid);
}

void Toolbar::setWidget(int index, Widget *widget)
{
    m_grid->addWidget(0, index, widget);
}

void Toolbar::setWidget(int indexFrom, int indexTo, Widget *widget)
{
    m_grid->addWidget(0, indexFrom, 0, indexTo, widget);
}

void Toolbar::onPaint(Canvas *canvas)
{
    D2D1_RECT_F bounding = D2D1::RectF(
        float(geometry().x),
        float(geometry().y),
        float(geometry().x + geometry().width),
        float(geometry().y + geometry().height));

    canvas->drawRoundedRect(D2D1::RoundedRect(
                                bounding,
                                8.0f, 8.0f),
                            m_style);

    Widget::onPaint(canvas);
}
