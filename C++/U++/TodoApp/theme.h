#pragma once
#include <CtrlLib/CtrlLib.h>

using namespace Upp;

namespace Theme {
    // Colors (not DPI-dependent)
    inline Color BG()        { return Color(28,  28,  28);  } // #1C1C1C
    inline Color SURFACE()   { return Color(42,  42,  42);  } // #2A2A2A
    inline Color INPUT_BG()  { return Color(48,  48,  48);  } // #303030
    inline Color TEXT()      { return Color(210, 210, 210); } // #D2D2D2
    inline Color WHITE()     { return Color(255, 255, 255); } // #FFFFFF
    inline Color MUTED()     { return Color(155, 155, 155); } // #9B9B9B
    inline Color ACCENT()    { return Color(93,  194, 175); } // #5DC2AF
    inline Color CB_BORDER() { return Color(217, 217, 217); } // #D9D9D9

    // Sizes — DPI() converts 100dpi design values to actual display pixels.
    // On a Retina (2x) display DPI(n) ≈ 2n, keeping logical size correct.
    inline int ITEM_H()     { return DPI(35); }
    inline int ITEM_MB()    { return DPI(5);  }
    inline int INPUT_H()    { return DPI(35); }
    inline int CB_SIZE()    { return DPI(16); }
    inline int CB_MR()      { return DPI(18); }
    inline int PAD_H()      { return DPI(24); }
    inline int PAD_V()      { return DPI(10); }
    inline int TITLE_MB()   { return DPI(14); }
    inline int INPUT_MB()   { return DPI(14); }
    inline int TAB_MB()     { return DPI(3);  }
    inline int TAB_H()      { return DPI(28); }
    inline int FONT_TITLE() { return DPI(18); }
    inline int FONT_NORM()  { return DPI(14); }
    inline int WIN_W()      { return DPI(800); }
    inline int WIN_H()      { return DPI(600); }
}