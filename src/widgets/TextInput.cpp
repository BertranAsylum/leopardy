#include "TextInput.h"
#include "Style.h"

#include <direct/Canvas.h>
#include <utils/Timer.h>

#include <regex>

bool isCursorVisible()
{
    static Timer timer;
    static bool visible = true;
    static constexpr auto cursorBlinkInterval = 500ms;

    if (timer.elapsed() >= cursorBlinkInterval) {
        timer.reset();
        visible = !visible;
    }
    return visible;
}

TextInput::TextInput()
{
    m_normalStyle.setStrokeWidth(1.0f);
    m_normalStyle.setStrokeColor({0.2f, 0.2f, 0.2f});
    m_normalStyle.setFillColor({1.0f, 1.0f, 1.0f});

    m_focusedStyle.setStrokeWidth(4.0f);
    m_focusedStyle.setStrokeColor({0.8f, 0.5f, 0.4f});
    m_focusedStyle.setFillColor({1.0f, 1.0f, 1.0f});

    m_font = Style::font();
}

void TextInput::setPlaceholder(const std::wstring &text)
{
    m_placeholder = text;
}

void TextInput::setCharFilter(const std::wstring &regex)
{
    m_charRegex = regex;
}

void TextInput::setMaxLength(int length)
{
    m_maxLength = length;
}

void TextInput::setText(const std::wstring &text)
{
    m_text = text;
}

std::wstring TextInput::text() const
{
    return m_text;
}

void TextInput::onPaint(Canvas *canvas)
{
    D2D1_RECT_F bounding = D2D1::RectF(
        float(geometry().x),
        float(geometry().y),
        float(geometry().x + geometry().width),
        float(geometry().y + geometry().height));

    auto &style = focused()
                      ? m_focusedStyle
                      : m_normalStyle;

    canvas->drawRoundedRect(D2D1::RoundedRect(
                                bounding,
                                8.0f, 8.0f),
                            style);

    TextLayout layout;
    layout.setBounding(bounding);
    layout.setAlignment(TextLayout::HAlignment::Left);
    layout.setAlignment(TextLayout::VAlignment::Center);
    layout.setMargins(20.f);

    if (m_text.empty() && !focused()) {
        canvas->drawText(m_placeholder, m_font, layout, {0.65f, 0.65f, 0.65f});
    }
    else {
        auto text = m_text;
        if (focused() && isCursorVisible()) {
            text += L"_";
        }
        canvas->drawText(text, m_font, layout, {0.0f, 0.0f, 0.0f});
    }

    Widget::onPaint(canvas);
}

void TextInput::onKeyboardInput(uint16_t keyCode, uint16_t scanCode)
{
    if (focused()) {
        switch (keyCode) {
            case VK_BACK:
                if (!m_text.empty()) {
                    m_text.resize(m_text.size() - 1);
                    m_cursor--;
                }
                break;
            default:
                break;
        }
    }
    Widget::onKeyboardInput(keyCode, scanCode);
}

void TextInput::onCharInput(wchar_t character)
{
    if (focused()) {
        if (!limitReached() && charAllowed(character)) {
            m_text += character;
            m_cursor++;
        }
    }
    Widget::onCharInput(character);
}

bool TextInput::charAllowed(wchar_t character) const
{
    if (!m_charRegex.empty()) {
        const std::wregex regex(m_charRegex);
        return std::regex_match(std::wstring(1, character), regex);
    }
    return true;
}

bool TextInput::limitReached() const
{
    if (m_maxLength && m_text.size() >= m_maxLength) {
        return true;
    }
    return false;
}
