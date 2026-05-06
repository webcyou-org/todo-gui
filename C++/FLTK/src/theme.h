#pragma once
#include <FL/Fl.H>
#include <FL/fl_draw.H>

namespace Theme {
    inline Fl_Color c(uchar r, uchar g, uchar b) { return fl_rgb_color(r, g, b); }

    const Fl_Color BG      = c(0x1C, 0x1C, 0x1C);
    const Fl_Color SURFACE = c(0x2A, 0x2A, 0x2A);
    const Fl_Color INPUT   = c(0x30, 0x30, 0x30);
    const Fl_Color TEXT    = c(0xD2, 0xD2, 0xD2);
    const Fl_Color WHITE   = c(0xFF, 0xFF, 0xFF);
    const Fl_Color MUTED   = c(0x9B, 0x9B, 0x9B);
    const Fl_Color ACCENT  = c(0x5D, 0xC2, 0xAF);
    const Fl_Color CB_BDR  = c(0xD9, 0xD9, 0xD9);

    constexpr int WIN_W  = 800;
    constexpr int WIN_H  = 600;
    constexpr int PAD_H  = 24;
    constexpr int PAD_V  = 10;
    constexpr int CONT_X = PAD_H;
    constexpr int CONT_W = WIN_W - 2 * PAD_H;

    constexpr int TITLE_Y = PAD_V;
    constexpr int TITLE_H = 24;
    constexpr int INPUT_Y = TITLE_Y + TITLE_H + 14;
    constexpr int INPUT_H = 35;
    constexpr int TABS_Y  = INPUT_Y + INPUT_H + 14;
    constexpr int TABS_H  = 28;
    constexpr int LIST_Y  = TABS_Y + TABS_H + 3;
    constexpr int LIST_H  = WIN_H - LIST_Y - PAD_V;

    constexpr int ITEM_H   = 35;
    constexpr int ITEM_MB  = 5;
    constexpr int CB_SIZE  = 16;
    constexpr int CB_PAD_L = 10;
    constexpr int CB_MR    = 18;
    constexpr int LABEL_X  = CB_PAD_L + CB_SIZE + CB_MR;
}