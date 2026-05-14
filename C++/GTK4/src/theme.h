#pragma once

namespace Theme {
    struct RGB { double r, g, b; };
    constexpr RGB SURFACE = {0x2A/255.0, 0x2A/255.0, 0x2A/255.0};
    constexpr RGB INPUT   = {0x30/255.0, 0x30/255.0, 0x30/255.0};
    constexpr RGB TEXT_C  = {0xD2/255.0, 0xD2/255.0, 0xD2/255.0};
    constexpr RGB WHITE   = {1.0,        1.0,        1.0};
    constexpr RGB MUTED   = {0x9B/255.0, 0x9B/255.0, 0x9B/255.0};
    constexpr RGB ACCENT  = {0x5D/255.0, 0xC2/255.0, 0xAF/255.0};
    constexpr RGB CB_BDR  = {0xD9/255.0, 0xD9/255.0, 0xD9/255.0};

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
        "window { background-color: #1C1C1C; }\n"
        ".title { color: #FFFFFF; font-size: 18px; font-weight: bold; }\n"
        "entry.todo-entry {\n"
        "  background: transparent; background-image: none;\n"
        "  color: #FFFFFF; caret-color: #FFFFFF;\n"
        "  font-size: 14px; border: none;\n"
        "  box-shadow: none; padding: 4px 16px;\n"
        "  min-height: 0; outline-width: 0;\n"
        "}\n"
        "entry.todo-entry placeholder { color: #9B9B9B; }\n"
        ".tab-btn {\n"
        "  color: #D2D2D2; font-size: 14px; padding: 0 8px;\n"
        "  background: none; border: none; box-shadow: none;\n"
        "  min-height: 28px; min-width: 0; border-radius: 0;\n"
        "}\n"
        ".tab-btn:hover { background: rgba(255,255,255,0.05); }\n"
        ".tab-btn.active { font-weight: bold; }\n"
        "scrolledwindow { background-color: #1C1C1C; }\n"
        "scrolledwindow viewport { background-color: #1C1C1C; }\n";
}