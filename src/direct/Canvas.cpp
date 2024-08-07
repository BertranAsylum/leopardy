#include "Canvas.h"
#include "Window.h"
#include "Brush.h"
#include "TextFormat.h"

#include <cassert>


Canvas::~Canvas()
{
    if (m_factory) {
        m_factory->Release();
    }
    if (m_renderTarget) {
        m_renderTarget->Release();
    }
}

Canvas::Canvas()
{}

Window *Canvas::window()
{
    return m_window;
}

void Canvas::clear()
{
    clear(D2D1::ColorF{D2D1::ColorF::Gray});
}

void Canvas::clear(const D2D1::ColorF &color)
{
    m_renderTarget->Clear(color);
}

void Canvas::begin()
{
    assert(m_renderTarget);
    m_renderTarget->BeginDraw();
}

void Canvas::end()
{
    assert(m_renderTarget);
    m_renderTarget->EndDraw();
}

void Canvas::setTransform(const D2D1::Matrix3x2F &matrix)
{
    assert(m_renderTarget);
    m_renderTarget->SetTransform(matrix);
}

void Canvas::addTransform(const D2D1::Matrix3x2F &matrix)
{
    assert(m_renderTarget);
    D2D1::Matrix3x2F currentMatrix;
    m_renderTarget->GetTransform(&currentMatrix);
    m_renderTarget->SetTransform(currentMatrix * matrix);
}

void Canvas::pushTransform()
{
    assert(m_renderTarget);
    D2D1::Matrix3x2F currentMatrix;
    m_renderTarget->GetTransform(&currentMatrix);
    m_trasformStask.push(currentMatrix);
}

void Canvas::popTransform()
{
    assert(m_renderTarget);
    auto &matrix = m_trasformStask.top();
    m_renderTarget->SetTransform(matrix);
    m_trasformStask.pop();
}

void Canvas::resetTransform()
{
    assert(m_renderTarget);
    m_renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void Canvas::drawText(const std::wstring &text, const Font &font, const TextLayout &layout, const D2D1::ColorF &color)
{
    Brush brush(m_renderTarget, color);
    TextFormat format(m_writeFactory, font);

    format.handle()->SetTextAlignment(layout.hAlignment());
    format.handle()->SetParagraphAlignment(layout.vAlignment());

    m_renderTarget->DrawText(text.c_str(), text.size(), format.handle(), layout.rect(), brush.handle());
}

void Canvas::drawShadowedText(const std::wstring &text, const Font &font, const TextLayout &layout,
                              const D2D1::ColorF &textColor, const D2D1::ColorF &shadowColor)
{
    Brush textBrush(m_renderTarget, textColor);
    Brush shadowBrush(m_renderTarget, shadowColor);
    TextFormat format(m_writeFactory, font);

    D2D1_RECT_F shadowRect = layout.rect();
    shadowRect.left += 2.0f;
    shadowRect.right += 2.0f;
    shadowRect.top += 2.0f;
    shadowRect.bottom += 2.0f;

    format.handle()->SetTextAlignment(layout.hAlignment());
    format.handle()->SetParagraphAlignment(layout.vAlignment());

    m_renderTarget->DrawText(text.c_str(), text.size(), format.handle(), shadowRect, shadowBrush.handle());
    m_renderTarget->DrawText(text.c_str(), text.size(), format.handle(), layout.rect(), textBrush.handle());
}

void Canvas::drawRect(const D2D1_RECT_F &rect, const ShapeStyle &style)
{
    if (style.fill()) {
        Brush brush(m_renderTarget, style.fillColor());
        m_renderTarget->FillRectangle(rect, brush.handle());
    }

    if (style.stroke()) {
        Brush brush(m_renderTarget, style.strokeColor());
        m_renderTarget->DrawRectangle(rect, brush.handle(), style.strokeWidth());
    }
}

void Canvas::drawRoundedRect(const D2D1_ROUNDED_RECT &rect, const ShapeStyle &style)
{
    if (style.fill()) {
        Brush brush(m_renderTarget, style.fillColor());
        m_renderTarget->FillRoundedRectangle(rect, brush.handle());
    }

    if (style.stroke()) {
        Brush brush(m_renderTarget, style.strokeColor());
        m_renderTarget->DrawRoundedRectangle(rect, brush.handle(), style.strokeWidth());
    }
}

bool Canvas::init(Window *window)
{
    if (!window) {
        return false;
    }

    if (D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_factory) != S_OK) {
        return false;
    }

    RECT rect;
    GetClientRect(window->handle(), &rect);
    if (m_factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
                                          D2D1::HwndRenderTargetProperties(
                                              window->handle(), D2D1::SizeU(rect.right, rect.bottom)),
                                          &m_renderTarget) != S_OK) {
        return false;
    }

    if (DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_writeFactory),
                            reinterpret_cast<IUnknown**>(&m_writeFactory)) != S_OK) {
        return false;
    }

    m_window = window;
    return true;
}
