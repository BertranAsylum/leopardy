#pragma once

#include "Font.h"
#include "TextLayout.h"
#include "ShapeStyle.h"

#include <d2d1.h>
#include <dwrite.h>
#include <string>
#include <stack>


class Window;

class Canvas {
    friend class Window;

public:
    ~Canvas();
    Canvas();

    Window *window();

    void clear();
    void clear(const D2D1::ColorF &color);

    void begin();
    void end();

    void setTransform(const D2D1::Matrix3x2F &matrix);
    void addTransform(const D2D1::Matrix3x2F &matrix);
    void pushTransform();
    void popTransform();
    void resetTransform();

    void drawText(const std::wstring &text, const Font &font, const TextLayout &layout, const D2D1::ColorF &color);
    void drawShadowedText(const std::wstring &text, const Font &font, const TextLayout &layout,
                          const D2D1::ColorF &textColor, const D2D1::ColorF &shadowColor);
    void drawRect(const D2D1_RECT_F &rect, const ShapeStyle &style);
    void drawRoundedRect(const D2D1_ROUNDED_RECT &rect, const ShapeStyle &style);

private:
    bool init(Window *window);

private:
    Window *m_window = nullptr;
    ID2D1HwndRenderTarget *m_renderTarget = nullptr;
    ID2D1Factory *m_factory = nullptr;
    IDWriteFactory *m_writeFactory = nullptr;

    std::stack<D2D1::Matrix3x2F> m_trasformStask;
};

