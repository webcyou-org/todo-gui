#pragma once
#include <wx/colour.h>

namespace Theme {
    inline const wxColour BG        { 0x1C, 0x1C, 0x1C };
    inline const wxColour SURFACE   { 0x2A, 0x2A, 0x2A };
    inline const wxColour INPUT     { 0x30, 0x30, 0x30 };
    inline const wxColour TEXT      { 0xD2, 0xD2, 0xD2 };
    inline const wxColour WHITE     { 0xFF, 0xFF, 0xFF };
    inline const wxColour MUTED     { 0x9B, 0x9B, 0x9B };
    inline const wxColour ACCENT    { 0x5D, 0xC2, 0xAF };
    inline const wxColour CB_BORDER { 0xD9, 0xD9, 0xD9 };

    constexpr int CONTENT_H = 24;   // left/right padding
    constexpr int CONTENT_V = 10;   // top/bottom padding
    constexpr int INPUT_H   = 35;
    constexpr int ITEM_H    = 35;
    constexpr int ITEM_MB   = 5;    // margin-bottom between items
    constexpr int CB_SIZE   = 16;
    constexpr int CB_PAD_L  = 10;   // checkbox left offset inside row
    constexpr int CB_MR     = 18;   // checkbox margin-right
    constexpr int LABEL_X   = CB_PAD_L + CB_SIZE + CB_MR; // = 44
}