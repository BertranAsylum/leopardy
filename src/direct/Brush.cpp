#include "Brush.h"

#include <cassert>

Brush::Brush(ID2D1HwndRenderTarget* target, const D2D1::ColorF& color)
{
    assert(target);
    target->CreateSolidColorBrush(color, reinterpret_cast<ID2D1SolidColorBrush**>(&m_handle));
}

Brush::~Brush()
{
    if (m_handle) {
        m_handle->Release();
    }
}

ID2D1Brush* Brush::handle() const
{
    return m_handle;
}
