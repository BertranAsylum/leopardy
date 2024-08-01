#pragma once

#include "Widget.h"

class Pager : public Widget {
public:
    void addPage(Widget *page);
    void switchTo(int pageNum);
    int pageCount() const;

protected:
    using Widget::addChild;
    using Widget::removeChild;

private:
    std::vector<Widget*> m_pages;
};
