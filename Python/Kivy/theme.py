from kivy.core.text import LabelBase

LabelBase.register(
    name='UI',
    fn_regular='fonts/NotoSansJP.ttf',
    fn_bold='fonts/NotoSansJPBold.ttf',
)

def _hex(h: str):
    h = h.lstrip('#')
    r, g, b = int(h[0:2], 16), int(h[2:4], 16), int(h[4:6], 16)
    return r / 255, g / 255, b / 255, 1


C_BG       = _hex('#1C1C1C')
C_SURFACE  = _hex('#2A2A2A')
C_INPUT    = _hex('#303030')
C_TEXT     = _hex('#D2D2D2')
C_MUTED    = _hex('#9B9B9B')
C_ACCENT   = _hex('#5DC2AF')
C_WHITE    = _hex('#FFFFFF')
C_CB_BORDER = _hex('#D9D9D9')

FONT_SIZE_TITLE  = '18sp'
FONT_SIZE_NORMAL = '14sp'
FONT_NAME        = 'UI'