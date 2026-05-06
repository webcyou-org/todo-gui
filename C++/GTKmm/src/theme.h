#pragma once

namespace Theme {
    struct RGB { double r, g, b; };
    constexpr RGB BG      = {0x1C/255.0, 0x1C/255.0, 0x1C/255.0};
    constexpr RGB SURFACE = {0x2A/255.0, 0x2A/255.0, 0x2A/255.0};
    constexpr RGB TEXT_C  = {0xD2/255.0, 0xD2/255.0, 0xD2/255.0};
    constexpr RGB WHITE   = {1.0, 1.0, 1.0};
    constexpr RGB MUTED   = {0x9B/255.0, 0x9B/255.0, 0x9B/255.0};
    constexpr RGB ACCENT  = {0x5D/255.0, 0xC2/255.0, 0xAF/255.0};
    constexpr RGB CB_BDR  = {0xD9/255.0, 0xD9/255.0, 0xD9/255.0};
    constexpr RGB INPUT   = {0x30/255.0, 0x30/255.0, 0x30/255.0};

    constexpr int WIN_W    = 800;
    constexpr int WIN_H    = 600;
    constexpr int PAD_H    = 24;
    constexpr int PAD_V    = 10;
    constexpr int ITEM_H   = 35;
    constexpr int ITEM_MB  = 5;
    constexpr int CB_SIZE  = 16;
    constexpr int CB_MR    = 18;
    constexpr int CB_PAD_L = 10;

    static const char* CSS =
        "window { background-color: #1C1C1C; }"
        ".title { color: #FFFFFF; font-size: 18px; font-weight: bold; }"
        ".todo-entry { background-color: #303030; color: #FFFFFF;"
        "  caret-color: #FFFFFF; font-size: 14px;"
        "  border: none; box-shadow: none; border-radius: 0;"
        "  padding: 4px 16px; min-height: 0; }"
        ".todo-entry:focus { border: none; box-shadow: none; }"
        ".tab-btn { color: #D2D2D2; font-size: 14px; padding: 0 8px;"
        "  background: none; border: none; box-shadow: none;"
        "  min-height: 28px; min-width: 0; border-radius: 0; }"
        ".tab-btn:hover { background: none; box-shadow: none; }"
        ".tab-btn-active { font-weight: bold; }"
        "scrolledwindow { background-color: #1C1C1C; }"
        "scrolledwindow viewport { background-color: #1C1C1C; }";
}