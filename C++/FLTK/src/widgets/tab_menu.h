#pragma once
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include "../data.h"
#include <functional>

class TabMenu : public Fl_Group {
    static constexpr int N = 3;
    Fl_Button*                     m_btns[N];
    std::function<void(TabFilter)> m_onChange;

    static void btnCb(Fl_Widget* w, void* data);
    void draw() override;

public:
    TabMenu(int x, int y, int w, int h, std::function<void(TabFilter)> cb);
    void setActive(TabFilter f);
};