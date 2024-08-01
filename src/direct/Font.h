#pragma once

#include <dwrite.h>
#include <string>

class Font {
public:
    enum class Weight {
        Regular = DWRITE_FONT_WEIGHT_REGULAR,
        Bold = DWRITE_FONT_WEIGHT_BOLD,
        SemiBold = DWRITE_FONT_WEIGHT_SEMI_BOLD
    };

    enum class Style {
        Normal = DWRITE_FONT_STYLE_NORMAL,
        Italic = DWRITE_FONT_STYLE_ITALIC
    };

    Font &setFamily(const std::wstring &name);
    Font &setSize(float value);
    Font &setWeight(Weight value);
    Font &setStyle(Style value);

    std::wstring family() const;
    float size() const;
    DWRITE_FONT_WEIGHT weight() const;
    DWRITE_FONT_STYLE style() const;

private:
    std::wstring m_family;
    float m_size = 0.0f;
    DWRITE_FONT_WEIGHT m_weight = DWRITE_FONT_WEIGHT_REGULAR;
    DWRITE_FONT_STYLE m_style = DWRITE_FONT_STYLE_NORMAL;
};

