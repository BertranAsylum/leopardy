#pragma once

#include <d2d1.h>

class Brush {
public:
    Brush(ID2D1HwndRenderTarget *target, const D2D1::ColorF& color);
    ~Brush();
    
    ID2D1Brush *handle() const;

private:
    ID2D1Brush *m_handle;
};

