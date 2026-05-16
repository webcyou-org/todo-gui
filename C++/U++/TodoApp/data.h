#pragma once
#include <CtrlLib/CtrlLib.h>

using namespace Upp;

enum class TabFilter { All, Active, Completed };

struct Todo : Moveable<Todo> {
    int    id           = 0;
    String task;
    bool   is_completed = false;
};

class TodoModel {
    Vector<Todo> todos;
    int          next_id = 1;

public:
    TodoModel();

    const Vector<Todo>& getData() const { return todos; }
    void         addTodo(const String& task);
    Todo*        findById(int id);
    void         changeCompleted(int id);
    Vector<Todo> getFilteredTodos(TabFilter filter) const;
    void         removeData(int id);
};

class MenuModel {
    TabFilter active_tab = TabFilter::All;

public:
    void      setActiveTab(TabFilter tab) { active_tab = tab; }
    TabFilter getActiveTab() const        { return active_tab; }
};