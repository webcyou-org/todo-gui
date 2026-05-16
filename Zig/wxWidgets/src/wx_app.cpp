#include "wx_app.h"
#include "widgets/todo_input.h"
#include "widgets/tab_menu.h"
#include "widgets/todo_item.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <vector>

// ── Design tokens ─────────────────────────────────────────────────────────────

static const wxColour C_BG   { 0x1C, 0x1C, 0x1C };

// ── Helpers ───────────────────────────────────────────────────────────────────

static std::vector<WxTodo> filteredTodos(const WxAppState* s) {
    std::vector<WxTodo> out;
    for (int i = 0; i < s->todo_count; ++i) {
        const WxTodo& t = s->todos[i];
        if (s->active_tab == WX_TAB_ALL)
            out.push_back(t);
        else if (s->active_tab == WX_TAB_ACTIVE    && !t.is_completed)
            out.push_back(t);
        else if (s->active_tab == WX_TAB_COMPLETED &&  t.is_completed)
            out.push_back(t);
    }
    return out;
}

// ── MainFrame ─────────────────────────────────────────────────────────────────

class MainFrame : public wxFrame {
public:
    MainFrame(WxAppState* state);

private:
    WxAppState* m_state;
    wxPanel*    m_root    = nullptr;
    wxBoxSizer* m_col     = nullptr;
    TodoInput*  m_input   = nullptr;
    TabMenu*    m_tabMenu  = nullptr;
    TodoList*   m_todoList = nullptr;

    void BuildUi();
    void RefreshList();

    void OnAddTodo    (wxCommandEvent& e);
    void OnTabChanged (wxCommandEvent& e);
    void OnToggleTodo (wxCommandEvent& e);
};

MainFrame::MainFrame(WxAppState* state)
    : wxFrame(nullptr, wxID_ANY, "ToDo", wxDefaultPosition, wxSize(800, 600))
    , m_state(state)
{
    SetMinSize(wxSize(800, 600));
    SetMaxSize(wxSize(800, 600));
    BuildUi();
}

void MainFrame::BuildUi() {
    m_root = new wxPanel(this);
    m_root->SetBackgroundColour(C_BG);

    // Outer sizer: top/bottom padding
    auto* root = new wxBoxSizer(wxVERTICAL);
    root->AddSpacer(10);  // CONTENT_V

    auto* hrow = new wxBoxSizer(wxHORIZONTAL);
    root->Add(hrow, 1, wxEXPAND);
    root->AddSpacer(10);  // CONTENT_V

    hrow->AddSpacer(24);  // CONTENT_H
    m_col = new wxBoxSizer(wxVERTICAL);
    hrow->Add(m_col, 1, wxEXPAND);
    hrow->AddSpacer(24);  // CONTENT_H

    m_root->SetSizer(root);

    // Title
    auto* title = new wxStaticText(m_root, wxID_ANY, "ToDo");
    title->SetFont(wxFont(wxFontInfo(wxSize(0, 18)).Bold()));
    title->SetForegroundColour(wxColour(0xFF, 0xFF, 0xFF));
    title->SetBackgroundColour(C_BG);
    m_col->Add(title, 0, wxEXPAND);
    m_col->AddSpacer(14);  // Title margin-bottom

    // Input
    m_input = new TodoInput(m_root);
    m_input->GetTextCtrl()->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnAddTodo, this);
    m_col->Add(m_input, 0, wxEXPAND);
    m_col->AddSpacer(14);  // Input margin-bottom

    // Tabs
    m_tabMenu = new TabMenu(m_root);
    m_tabMenu->Bind(EVT_TAB_CHANGED, &MainFrame::OnTabChanged, this);
    m_col->Add(m_tabMenu, 0, wxEXPAND);
    m_col->AddSpacer(3);   // TabMenu margin-bottom

    // Todo list
    m_todoList = new TodoList(m_root);
    m_todoList->Bind(EVT_TOGGLE_TODO, &MainFrame::OnToggleTodo, this);
    m_col->Add(m_todoList, 1, wxEXPAND);

    auto* frameSizer = new wxBoxSizer(wxVERTICAL);
    frameSizer->Add(m_root, 1, wxEXPAND);
    SetSizer(frameSizer);

    RefreshList();
}

void MainFrame::RefreshList() {
    if (!m_todoList) return;
    m_todoList->Refresh(filteredTodos(m_state));
}

void MainFrame::OnAddTodo(wxCommandEvent&) {
    wxString text = m_input->GetTextCtrl()->GetValue().Trim();
    if (text.empty()) return;
    state_add_todo(m_state, text.utf8_str());
    m_input->GetTextCtrl()->Clear();
    RefreshList();
}

void MainFrame::OnTabChanged(wxCommandEvent& e) {
    state_set_tab(m_state, static_cast<WxTabFilter>(e.GetInt()));
    m_tabMenu->SetActive(static_cast<WxTabFilter>(e.GetInt()));
    RefreshList();
}

void MainFrame::OnToggleTodo(wxCommandEvent& e) {
    state_toggle_todo(m_state, static_cast<unsigned int>(e.GetInt()));
    RefreshList();
}

// ── wxApp ─────────────────────────────────────────────────────────────────────

static WxAppState* g_state = nullptr;

class TodoApp : public wxApp {
public:
    bool OnInit() override {
        auto* frame = new MainFrame(g_state);
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP_NO_MAIN(TodoApp);

extern "C" void wx_run(WxAppState* state) {
    g_state = state;
    static char name[] = "todo";
    static char* argv[] = { name, nullptr };
    int argc = 1;
    wxEntry(argc, argv);
}