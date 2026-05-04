C_BG        = "#1C1C1C"
C_SURFACE   = "#2A2A2A"
C_INPUT     = "#303030"
C_TEXT      = "#D2D2D2"
C_MUTED     = "#9B9B9B"
C_ACCENT    = "#5DC2AF"
C_WHITE     = "#FFFFFF"
C_CB_BORDER = "#D9D9D9"

FONT_TITLE  = ("Helvetica", 18, "bold")
FONT_NORMAL = ("Helvetica", 14)
FONT_BOLD   = ("Helvetica", 14, "bold")
FONT_STRIKE = ("Helvetica", 14, "overstrike")

CORNER_R = 8


def rounded_rect(canvas, x1, y1, x2, y2, r=CORNER_R, **kw):
    """Draw a smooth rounded rectangle polygon on canvas."""
    return canvas.create_polygon(
        [
            x1 + r, y1,   x2 - r, y1,
            x2,     y1,   x2,     y1 + r,
            x2,     y2 - r, x2,   y2,
            x2 - r, y2,   x1 + r, y2,
            x1,     y2,   x1,     y2 - r,
            x1,     y1 + r, x1,   y1,
        ],
        smooth=True, **kw
    )