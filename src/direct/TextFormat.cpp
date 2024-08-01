#include "TextFormat.h"

#include <cassert>

TextFormat::~TextFormat()
{
    if (m_handle) {
        m_handle->Release();
    }
}

TextFormat::TextFormat(IDWriteFactory *factory, const Font &font)
{
    assert(factory);
    factory->CreateTextFormat(
        font.family().c_str(),
        nullptr,
        font.weight(),
        font.style(),
        DWRITE_FONT_STRETCH_NORMAL,
        font.size(),
        L"",
        &m_handle
    );
}

IDWriteTextFormat *TextFormat::handle() const
{
    return m_handle;
}
