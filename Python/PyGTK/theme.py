import math


class Theme:
    BG      = "#1C1C1C"
    SURFACE = "#2A2A2A"
    INPUT   = "#303030"
    TEXT    = "#D2D2D2"
    WHITE   = "#FFFFFF"
    MUTED   = "#9B9B9B"
    ACCENT  = "#5DC2AF"
    CB_BDR  = "#D9D9D9"

    BG_C      = (0x1C/255, 0x1C/255, 0x1C/255)
    SURFACE_C = (0x2A/255, 0x2A/255, 0x2A/255)
    TEXT_C    = (0xD2/255, 0xD2/255, 0xD2/255)
    WHITE_C   = (1.0, 1.0, 1.0)
    MUTED_C   = (0x9B/255, 0x9B/255, 0x9B/255)
    ACCENT_C  = (0x5D/255, 0xC2/255, 0xAF/255)
    CB_BDR_C  = (0xD9/255, 0xD9/255, 0xD9/255)
    INPUT_C   = (0x30/255, 0x30/255, 0x30/255)

    CB_SIZE  = 16
    CB_PAD_L = 10
    CB_MR    = 18
    ITEM_H   = 35
    ITEM_MB  = 5

    CSS = b"""
        window { background-color: #1C1C1C; }
        .title { color: #FFFFFF; font-size: 18px; font-weight: bold; }
        .todo-entry {
            background-color: #303030; color: #FFFFFF;
            caret-color: #FFFFFF; font-size: 14px;
            border: none; box-shadow: none; border-radius: 0;
            padding: 4px 16px; min-height: 0;
        }
        .todo-entry:focus { border: none; box-shadow: none; }
        .tab-btn {
            color: #D2D2D2; font-size: 14px; padding: 0 8px;
            background: none; border: none; box-shadow: none;
            min-height: 28px; min-width: 0; border-radius: 0;
        }
        .tab-btn:hover { background: none; box-shadow: none; }
        .tab-btn-active { font-weight: bold; }
        scrolledwindow { background-color: #1C1C1C; }
        scrolledwindow viewport { background-color: #1C1C1C; }
    """


def set_color(cr, rgb):
    cr.set_source_rgb(*rgb)


def rounded_rect(cr, x, y, w, h, r):
    cr.arc(x + r,     y + r,     r, math.pi,       1.5 * math.pi)
    cr.arc(x + w - r, y + r,     r, 1.5 * math.pi, 2.0 * math.pi)
    cr.arc(x + w - r, y + h - r, r, 0,              0.5 * math.pi)
    cr.arc(x + r,     y + h - r, r, 0.5 * math.pi,  math.pi)
    cr.close_path()