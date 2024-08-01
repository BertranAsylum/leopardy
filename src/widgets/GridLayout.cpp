#include "GridLayout.h"
#include "Widget.h"

#include <cassert>

GridLayout::GridLayout(int rows, int cols) :
    m_rows(rows),
    m_cols(cols)
{
    assert(rows > 0 && "Invalid grid row count");
    assert(cols > 0 && "Invalid grid col count");
}

void GridLayout::addWidget(int row, int col, Widget *widget)
{
    addWidget(row, col, row, col, widget);
}

void GridLayout::addWidget(int rowFrom, int colFrom, int rowTo, int colTo, Widget *widget)
{
    assert(rowFrom >= 0 && rowFrom < m_rows && "Invalid grid pos");
    assert(colFrom >= 0 && colFrom < m_cols && "Invalid grid pos");
    assert(rowTo >= rowFrom && rowTo < m_rows && "Invalid grid pos");
    assert(colTo >= colFrom && colTo < m_cols && "Invalid grid pos");

    if (widget) {
        addChild(widget);
        m_items.push_back({.rowFrom = rowFrom, .colFrom = colFrom, .rowTo = rowTo, .colTo = colTo, .widget = widget});
    }
}

void GridLayout::adjustWidgetSize(bool adjust)
{
    m_adjustWidgetSize = adjust;
}

void GridLayout::setMargins(float margins)
{
    m_margins = margins;
}

int GridLayout::rowCount() const
{
    return m_rows;
}

int GridLayout::colCount() const
{
    return m_cols;
}

void GridLayout::onPaint(Canvas *canvas)
{
    if (parent()) {
        setGeometry(parent()->geometry());
        for (const auto &i : m_items) {
            align(i);
        }
        Widget::onPaint(canvas);
    }
}

void GridLayout::align(const Item &item)
{
    const float cellHSize = parent()->width() / float(m_cols);
    const float cellVSize = parent()->height() / float(m_rows);
    const int itemRowSpan = item.rowTo - item.rowFrom + 1;
    const int itemColSpan = item.colTo - item.colFrom + 1;
    const float itemCenterX = geometry().x + item.colFrom * cellHSize + itemColSpan * cellHSize / 2;
    const float itemCenterY = geometry().y + item.rowFrom * cellVSize + itemRowSpan * cellVSize / 2;

    if (m_adjustWidgetSize) {
        item.widget->setSize(
            int(itemColSpan * cellHSize - m_margins * 2),
            int(itemRowSpan * cellVSize - m_margins * 2));
    }

    item.widget->setPos(
        int(itemCenterX - item.widget->width() / 2.0f),
        int(itemCenterY - item.widget->height() / 2.0f));
}
