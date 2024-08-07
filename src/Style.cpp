#include "Style.h"

Font Style::font(FontSize size)
{
    Font f;
    f.setFamily(L"DejaVu Sans Mono");

    switch (size) {
        case FontSize::Tiny:
            f.setSize(6);
            break;
        case FontSize::Small:
            f.setSize(12);
            break;
        case FontSize::Medium:
            f.setSize(16);
            break;
        case FontSize::Large:
            f.setSize(20);
            break;
    }

    return f;
}

D2D1::ColorF Style::color(const D2D1::ColorF &color, ColorShift shift)
{
    D2D1::ColorF shifted(color);
    switch (shift) {
        case ColorShift::MuchDarker:
            shifted.r *= 0.5f;
            shifted.g *= 0.5f;
            shifted.b *= 0.5f;
            break;
        case ColorShift::Darker:
            shifted.r *= 0.75f;
            shifted.g *= 0.75f;
            shifted.b *= 0.75f;
            break;
        case ColorShift::Lighter:
            shifted.r *= 1.25f;
            shifted.g *= 1.25f;
            shifted.b *= 1.25f;
            break;
        case ColorShift::MuchLighter:
            shifted.r *= 1.5f;
            shifted.g *= 1.5f;
            shifted.b *= 1.5f;
            break;
    }
    return shifted;
}

D2D1::ColorF Style::color(ColorTag tag)
{
    switch (tag) {
        case ColorTag::Foreground:
            return {1.0f, 1.0f, 1.0f};
        case ColorTag::Background:
            return {0.2f, 0.2f, 0.2f};
        case ColorTag::Shadow:
            return {0.0f, 0.0f, 0.0f};
    }
    return {0.0f, 0.0f, 0.0f};
}

float Style::borderWidth()
{
    return 1.0f;
}
