#pragma once
#include <QColor>

// Design tokens — source of truth: design/tokens.md
namespace Theme {
    inline const QColor BG        = QColor(0x1C, 0x1C, 0x1C);
    inline const QColor SURFACE   = QColor(0x2A, 0x2A, 0x2A);
    inline const QColor INPUT     = QColor(0x30, 0x30, 0x30);
    inline const QColor TEXT      = QColor(0xD2, 0xD2, 0xD2);
    inline const QColor WHITE     = QColor(0xFF, 0xFF, 0xFF);
    inline const QColor MUTED     = QColor(0x9B, 0x9B, 0x9B);
    inline const QColor ACCENT    = QColor(0x5D, 0xC2, 0xAF);
    inline const QColor CB_BORDER = QColor(0xD9, 0xD9, 0xD9);

    constexpr int CONTENT_H  = 24;   // content left/right padding
    constexpr int CONTENT_V  = 10;   // content top/bottom padding
    constexpr int INPUT_H    = 35;
    constexpr int ITEM_H     = 35;
    constexpr int ITEM_MB    = 5;    // margin-bottom between items
    constexpr int CB_SIZE    = 16;
    constexpr int CB_PAD_L   = 10;   // checkbox left offset inside row
    constexpr int CB_MR      = 18;   // checkbox margin-right
    constexpr int LABEL_X    = CB_PAD_L + CB_SIZE + CB_MR; // = 44
}