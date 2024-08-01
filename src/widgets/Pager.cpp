#include "Pager.h"

void Pager::addPage(Widget *page)
{
    if (page) {
        if (!m_pages.empty()) {
            page->hide();
        }
        addChild(page);
        m_pages.push_back(page);
    }
}

void Pager::switchTo(int pageNum)
{
    for (int i = 0; i < m_pages.size(); ++i) {
        m_pages[i]->setVisible(i == pageNum);
    }
}

int Pager::pageCount() const
{
    return m_pages.size();
}
