#pragma once

#include "Button.h"
#include "direct/Font.h"
#include "direct/ShapeStyle.h"

class TextButton : public Button {
public:
    explicit TextButton(const std::wstring &text);

protected:
    void onPaint(Canvas *canvas) override;

private:
    Font m_font;
    ShapeStyle m_normalStyle;
    ShapeStyle m_hoveredStyle;
    ShapeStyle m_pressedStyle;
    std::wstring m_text;
};
