#pragma once

#include "widgets/Widget.h"
#include "direct/Font.h"
#include "direct/ShapeStyle.h"

class TextInput : public Widget {
public:
    using TextChangedCallback = std::function<void(const std::wstring &text)>;

    ~TextInput() override = default;
    explicit TextInput();

    void setPlaceholder(const std::wstring &text);
    void setCharFilter(const std::wstring &regex);
    void setMaxLength(int length);
    void setText(const std::wstring &text);
    std::wstring text() const;

    void onTextChanged(const TextChangedCallback &callback);

protected:
    void onPaint(Canvas *canvas) override;
    void onKeyboardInput(uint16_t keyCode, uint16_t scanCode) override;
    void onCharInput(wchar_t character) override;

private:
    bool charAllowed(wchar_t character) const;
    bool limitReached() const;

private:
    Font m_font;
    ShapeStyle m_normalStyle;
    ShapeStyle m_focusedStyle;
    std::wstring m_placeholder;
    std::wstring m_text;

    std::wstring m_charRegex;
    int m_maxLength = 0;
    int m_cursor = 0;

    TextChangedCallback m_textChangedCallback;
};
