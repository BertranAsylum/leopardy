#pragma once

#include "Font.h"

class TextFormat {
public:
    ~TextFormat();
    TextFormat(IDWriteFactory *factory, const Font &font);

    IDWriteTextFormat *handle() const;

private:
    IDWriteTextFormat *m_handle;
};

