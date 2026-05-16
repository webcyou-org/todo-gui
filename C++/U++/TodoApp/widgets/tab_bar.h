#pragma once
#include <CtrlLib/CtrlLib.h>
#include "../theme.h"

using namespace Upp;

static const char* TAB_LABELS[] = { "All", "Active", "Completed" };

struct TabBar : Ctrl {
    int        active_idx = 0;
    Event<int> WhenTab;

    void Paint(Draw& w) override {
        w.DrawRect(GetSize(), Theme::BG());
        int x = 0;
        for(int i = 0; i < 3; i++) {
            Font fnt = StdFont().Height(Theme::FONT_NORM());
            if(i == active_idx) fnt.Bold();
            int tw = GetTextSize(TAB_LABELS[i], fnt).cx;
            int pad = DPI(8);
            int bw = tw + 2 * pad;
            w.DrawText(x + pad, (GetSize().cy - fnt.GetCy()) / 2,
                       TAB_LABELS[i], fnt, Theme::TEXT());
            x += bw;
        }
    }

    void LeftDown(Point p, dword) override {
        int x = 0;
        for(int i = 0; i < 3; i++) {
            Font fnt = StdFont().Height(Theme::FONT_NORM()).Bold();
            int pad = DPI(8);
            int bw = GetTextSize(TAB_LABELS[i], fnt).cx + 2 * pad;
            if(p.x < x + bw) {
                if(active_idx != i) {
                    active_idx = i;
                    Refresh();
                    WhenTab(i);
                }
                return;
            }
            x += bw;
        }
    }
};
