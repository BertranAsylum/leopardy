#pragma once

#include <d2d1.h>
#include <dwrite.h>

class TextLayout {
public:
    enum class HAlignment {
        Left = DWRITE_TEXT_ALIGNMENT_LEADING,
        Right = DWRITE_TEXT_ALIGNMENT_TRAILING,
        Center = DWRITE_TEXT_ALIGNMENT_CENTER
    };
    
    enum class VAlignment {
        Top = DWRITE_PARAGRAPH_ALIGNMENT_NEAR,
        Bottom = DWRITE_PARAGRAPH_ALIGNMENT_FAR,
        Center = DWRITE_PARAGRAPH_ALIGNMENT_CENTER
    };

    TextLayout &setBounding(float left, float top, float right, float bottom);
    TextLayout &setBounding(const D2D1_POINT_2F &center, float width, float height);
    TextLayout &setBounding(const D2D1_RECT_F &rect);

    TextLayout &setAlignment(HAlignment horizontal);
    TextLayout &setAlignment(VAlignment vertical);

    TextLayout &setMargins(float margins);

    D2D1_RECT_F rect() const;
    DWRITE_TEXT_ALIGNMENT hAlignment() const;
    DWRITE_PARAGRAPH_ALIGNMENT vAlignment() const;

private:
    D2D1_RECT_F m_rect;
    DWRITE_TEXT_ALIGNMENT m_hAlignment = DWRITE_TEXT_ALIGNMENT_LEADING;
    DWRITE_PARAGRAPH_ALIGNMENT m_vAlignment = DWRITE_PARAGRAPH_ALIGNMENT_NEAR;
    float m_margins = 0.0f;
};

