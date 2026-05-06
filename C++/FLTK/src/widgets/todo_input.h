#pragma once
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>

class InnerInput : public Fl_Input {
public:
    InnerInput(int x, int y, int w, int h);
    int handle(int event) override;
};

class TodoInput : public Fl_Group {
    InnerInput* m_input;

    void draw() override;

public:
    TodoInput(int x, int y, int w, int h);
    Fl_Input* input();
};