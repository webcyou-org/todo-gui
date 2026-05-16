from PySide6.QtGui import QColor

C_BG        = QColor(0x1C, 0x1C, 0x1C)
C_SURFACE   = QColor(0x2A, 0x2A, 0x2A)
C_INPUT     = QColor(0x30, 0x30, 0x30)
C_TEXT      = QColor(0xD2, 0xD2, 0xD2)
C_WHITE     = QColor(0xFF, 0xFF, 0xFF)
C_MUTED     = QColor(0x9B, 0x9B, 0x9B)
C_ACCENT    = QColor(0x5D, 0xC2, 0xAF)
C_CB_BORDER = QColor(0xD9, 0xD9, 0xD9)

CONTENT_H = 24   # left/right padding
CONTENT_V = 10   # top/bottom padding
INPUT_H   = 35
ITEM_H    = 35
ITEM_MB   = 5    # margin-bottom between items
CB_SIZE   = 16
CB_PAD_L  = 10   # checkbox left offset inside row
CB_MR     = 18   # checkbox margin-right
LABEL_X   = CB_PAD_L + CB_SIZE + CB_MR  # = 44