#pragma once

#include "Widget.h"
#include "Style.h"
#include "direct/Font.h"

class TextLabel : public Widget {
public:
    explicit TextLabel(const std::wstring &text = L"");

    void setText(const std::wstring &text);
    void setFontSize(Style::FontSize size);
    void setShadowed(bool shadowed);

protected:
    void onPaint(Canvas *canvas) override;

private:
    Font m_font;
    std::wstring m_text;
    bool m_shadowed = false;
};
