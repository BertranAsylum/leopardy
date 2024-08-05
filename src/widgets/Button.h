#pragma once

#include "Widget.h"

class Button : public Widget {
public:
    void setCheckable(bool value);
    bool checkable() const;
    bool checked() const;

    using Widget::onMousePress;
    using Widget::onMouseRelease;

protected:
    void onMousePress(int x, int y) override;
    void onMouseRelease(int x, int y) override;

private:
    bool m_checkable = false;
    bool m_checked = false;
};

