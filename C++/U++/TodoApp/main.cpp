#include <CtrlLib/CtrlLib.h>
#include "data.h"
#include "theme.h"
#include "widgets/tab_bar.h"
#include "widgets/todo_list.h"

using namespace Upp;

// ────────────────────────────────────────────────────────────────────────────
//  Custom EditField style — dark background, white text, accent focus border
// ────────────────────────────────────────────────────────────────────────────
static const EditField::Style& TodoEditStyle() {
    static EditField::Style s;
    static bool init = false;
    if(!init) {
        s            = EditField::StyleDefault();
        s.paper      = Theme::INPUT_BG();
        s.focus      = Theme::INPUT_BG();
        s.text       = Theme::WHITE();
        s.coloredge  = Theme::ACCENT();
        s.activeedge = true;
        init = true;
    }
    return s;
}

// ────────────────────────────────────────────────────────────────────────────
//  Main application window
// ────────────────────────────────────────────────────────────────────────────
struct TodoApp : TopWindow {
    TodoModel     todo_model;
    MenuModel     menu_model;

    Label         lbl_title;
    EditString    input_field;
    TabBar        tab_bar;
    TodoListCtrl  todo_list;

    Vector<Todo>  filtered;

    // ── helpers ──────────────────────────────────────────────────────────
    void RefreshList() {
        filtered = todo_model.getFilteredTodos(menu_model.getActiveTab());
        todo_list.SetTodos(filtered);
    }

    void AddTodo() {
        String task = TrimBoth(input_field.GetText().ToString());
        if(task.IsEmpty()) return;
        todo_model.addTodo(task);
        input_field.SetData(Value());
        RefreshList();
    }

    void OnToggle(int id) {
        todo_model.changeCompleted(id);
        RefreshList();
    }

    void OnTabChanged(int idx) {
        TabFilter filters[] = { TabFilter::All, TabFilter::Active, TabFilter::Completed };
        menu_model.setActiveTab(filters[idx]);
        RefreshList();
    }

    // ── layout helpers ───────────────────────────────────────────────────
    int title_y() const { return Theme::PAD_V(); }
    int input_y() const { return title_y() + DPI(24) + Theme::TITLE_MB(); }
    int tabs_y()  const { return input_y() + Theme::INPUT_H() + Theme::INPUT_MB(); }
    int list_y()  const { return tabs_y()  + Theme::TAB_H()   + Theme::TAB_MB();  }

    // ── overrides ────────────────────────────────────────────────────────
    void Paint(Draw& w) override {
        w.DrawRect(GetSize(), Theme::BG());
    }

    TodoApp() {
        Title("ToDo").Zoomable();
        SetRect(0, 0, Theme::WIN_W(), Theme::WIN_H());

        // Title
        lbl_title.SetText("ToDo")
                 .SetFont(StdFont().Height(Theme::FONT_TITLE()).Bold())
                 .SetInk(Theme::WHITE())
                 .Transparent();
        Add(lbl_title.TopPos(title_y(), DPI(24)).HSizePos(Theme::PAD_H(), Theme::PAD_H()));

        // Input field
        input_field.SetStyle(TodoEditStyle())
                   .NullText("Add Task", Theme::MUTED());
        input_field.WhenEnter = [this] { AddTodo(); };
        Add(input_field.TopPos(input_y(), Theme::INPUT_H())
                       .HSizePos(Theme::PAD_H(), Theme::PAD_H()));

        // Tab bar
        tab_bar.WhenTab = [this](int idx) { OnTabChanged(idx); };
        Add(tab_bar.TopPos(tabs_y(), Theme::TAB_H())
                   .HSizePos(Theme::PAD_H(), Theme::PAD_H()));

        // Todo list
        todo_list.WhenToggle = [this](int id) { OnToggle(id); };
        Add(todo_list.VSizePos(list_y(), Theme::PAD_V())
                     .HSizePos(Theme::PAD_H(), Theme::PAD_H()));

        RefreshList();
    }
};

GUI_APP_MAIN {
    TodoApp().Run();
}