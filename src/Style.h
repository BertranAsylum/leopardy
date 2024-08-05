#pragma once

#include "direct/Font.h"
#include <d2d1.h>

class Style {
public:
    enum class FontSize {
        Tiny,
        Small,
        Medium,
        Large,
        Default = Medium
    };

    enum class ColorShift {
        MuchDarker,
        Darker,
        Lighter,
        MuchLighter
    };

    enum class ColorTag {
        Foreground,
        Background
    };

    static Font font(FontSize size = FontSize::Default);
    static D2D1::ColorF color(const D2D1::ColorF &color, ColorShift shift);
    static D2D1::ColorF color(ColorTag tag);
    static float borderWidth();
};
