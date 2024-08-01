#pragma once

#include "widgets/Widget.h"

class GridLayout : public Widget {
public:
    struct Item {
        int rowFrom = 0;
        int colFrom = 0;
        int rowTo = 0;
        int colTo = 0;
        Widget *widget = nullptr;
    };

    GridLayout(int rows, int cols);
    void addWidget(int row, int col, Widget *widget);
    void addWidget(int rowFrom, int colFrom, int rowTo, int colTo, Widget *widget);

    void adjustWidgetSize(bool adjust);
    void setMargins(float margins);

    int rowCount() const;
    int colCount() const;

protected:
    using Widget::addChild;
    using Widget::removeChild;
    void onPaint(Canvas *canvas) override;

private:
    void align(const Item &item);

private:
    int m_rows = 0;
    int m_cols = 0;
    bool m_adjustWidgetSize = false;
    float m_margins = 0.0f;
    std::vector<Item> m_items;
};
