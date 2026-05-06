"""Design tokens — single source of truth."""
import wx

C_BG      = wx.Colour(28,  28,  28)   # #1C1C1C
C_SURFACE = wx.Colour(42,  42,  42)   # #2A2A2A
C_INPUT   = wx.Colour(48,  48,  48)   # #303030
C_TEXT    = wx.Colour(210, 210, 210)  # #D2D2D2
C_WHITE   = wx.Colour(255, 255, 255)  # #FFFFFF
C_MUTED   = wx.Colour(155, 155, 155)  # #9B9B9B
C_ACCENT  = wx.Colour(93,  194, 175)  # #5DC2AF
C_CB_BDR  = wx.Colour(217, 217, 217)  # #D9D9D9

CB_SIZE  = 16
CB_PAD_L = 10
CB_MR    = 18
ITEM_H   = 35
ITEM_MB  = 5
FONT_SZ  = 11


def font(size: int = FONT_SZ, bold: bool = False) -> wx.Font:
    weight = wx.FONTWEIGHT_BOLD if bold else wx.FONTWEIGHT_NORMAL
    return wx.Font(size, wx.FONTFAMILY_DEFAULT, wx.FONTSTYLE_NORMAL, weight)