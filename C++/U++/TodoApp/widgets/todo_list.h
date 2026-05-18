#pragma once
#include <CtrlLib/CtrlLib.h>
#include "../data.h"
#include "../theme.h"

using namespace Upp;

struct TodoListCtrl : Ctrl {
    const Vector<Todo>* todos = nullptr;
    Event<int>          WhenToggle;

    VScrollBar sb;

    TodoListCtrl() {
        AddFrame(sb);
        sb.WhenScroll = [this] { Refresh(); };
    }

    void SetTodos(const Vector<Todo>& data) {
        todos = &data;
        UpdateScroll();
        Refresh();
    }

    void UpdateScroll() {
        if(!todos) return;
        int total = todos->GetCount() * (Theme::ITEM_H() + Theme::ITEM_MB());
        sb.SetTotal(total);
        sb.SetPage(GetSize().cy);
    }

    void Layout() override { UpdateScroll(); }

    void Paint(Draw& w) override {
        w.DrawRect(GetSize(), Theme::BG());
        if(!todos || todos->IsEmpty()) return;

        int scroll_y = (int)sb;
        int y = -scroll_y;
        int w_cx = GetSize().cx;

        for(int i = 0; i < todos->GetCount(); i++) {
            const Todo& t = (*todos)[i];

            if(y + Theme::ITEM_H() < 0) { y += Theme::ITEM_H() + Theme::ITEM_MB(); continue; }
            if(y > GetSize().cy) break;

            // Item background with border-radius (drawn as plain rect; U++ has no built-in rounded rect)
            w.DrawRect(0, y, w_cx, Theme::ITEM_H(), Theme::SURFACE());

            // Circular checkbox
            int cb_x  = DPI(10);
            int cb_y  = y + (Theme::ITEM_H() - Theme::CB_SIZE()) / 2;
            Rect cb(cb_x, cb_y, cb_x + Theme::CB_SIZE(), cb_y + Theme::CB_SIZE());
            if(t.is_completed) {
                w.DrawEllipse(cb, Theme::SURFACE(), DPI(2), Theme::CB_BORDER());
                int cx = cb_x + Theme::CB_SIZE() / 2;
                int cy = y + Theme::ITEM_H() / 2;
                w.DrawLine(cx - 4, cy, cx - 1, cy + 3, DPI(1), Theme::ACCENT());
                w.DrawLine(cx - 1, cy + 3, cx + 4, cy - 3, DPI(1), Theme::ACCENT());
            } else {
                w.DrawEllipse(cb, Theme::BG(), DPI(2), Theme::CB_BORDER());
            }

            // Task text with optional strikethrough
            int text_x = cb_x + Theme::CB_SIZE() + Theme::CB_MR();
            Font fnt = StdFont().Height(Theme::FONT_NORM());
            if(t.is_completed) fnt.Strikeout();
            Color ink = t.is_completed ? Theme::MUTED() : Theme::TEXT();
            int ty = y + (Theme::ITEM_H() - fnt.GetCy()) / 2;
            w.DrawText(text_x, ty, t.task, fnt, ink);

            y += Theme::ITEM_H() + Theme::ITEM_MB();
        }
    }

    void LeftDown(Point p, dword) override {
        if(!todos) return;
        int scroll_y = (int)sb;
        int y = -scroll_y;
        for(int i = 0; i < todos->GetCount(); i++) {
            if(p.y >= y && p.y < y + Theme::ITEM_H()) {
                int cb_x  = DPI(10);
                int cb_cx = Theme::CB_SIZE() + Theme::CB_MR();
                if(p.x >= cb_x && p.x <= cb_x + cb_cx)
                    WhenToggle((*todos)[i].id);
                return;
            }
            y += Theme::ITEM_H() + Theme::ITEM_MB();
        }
    }

    bool Key(dword key, int) override {
        return sb.VertKey(key);
    }

    void MouseWheel(Point, int zdelta, dword) override {
        sb.Wheel(zdelta);
    }
};