#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "data.h"
#include "theme.h"
#include "widgets/todo_input.h"
#include "widgets/tab_menu.h"
#include "widgets/todo_item.h"

// ── TodoApp ───────────────────────────────────────────────────────────────────

class TodoApp : public wxApp {
public:
    bool OnInit() override;
};

// ── MainFrame ─────────────────────────────────────────────────────────────────

class MainFrame : public wxFrame {
public:
    MainFrame();

private:
    void BuildUi();
    void OnAddTodo(wxCommandEvent& e);
    void OnTabChanged(wxCommandEvent& e);
    void OnToggleTodo(wxCommandEvent& e);
    void RefreshList();

    TodoModel   m_todoModel;
    MenuModel   m_menuModel;
    wxPanel*    m_root    = nullptr;
    wxBoxSizer* m_col     = nullptr;
    TodoInput*  m_input   = nullptr;
    TabMenu*    m_tabMenu  = nullptr;
    TodoList*   m_todoList = nullptr;
};

wxIMPLEMENT_APP(TodoApp);

bool TodoApp::OnInit() {
    auto* frame = new MainFrame();
    frame->Show(true);
    return true;
}

MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "ToDo", wxDefaultPosition, wxSize(800, 600))
{
    SetMinSize(wxSize(800, 600));
    SetMaxSize(wxSize(800, 600));
    BuildUi();
}

void MainFrame::BuildUi() {
    m_root = new wxPanel(this);
    m_root->SetBackgroundColour(Theme::BG);

    auto* root = new wxBoxSizer(wxVERTICAL);
    root->AddSpacer(Theme::CONTENT_V);
    auto* hrow = new wxBoxSizer(wxHORIZONTAL);
    root->Add(hrow, 1, wxEXPAND);
    root->AddSpacer(Theme::CONTENT_V);
    hrow->AddSpacer(Theme::CONTENT_H);
    m_col = new wxBoxSizer(wxVERTICAL);
    hrow->Add(m_col, 1, wxEXPAND);
    hrow->AddSpacer(Theme::CONTENT_H);
    m_root->SetSizer(root);

    // Title
    auto* title = new wxStaticText(m_root, wxID_ANY, "ToDo");
    title->SetFont(wxFont(wxFontInfo(wxSize(0, 18)).Bold()));
    title->SetForegroundColour(Theme::WHITE);
    title->SetBackgroundColour(Theme::BG);
    m_col->Add(title, 0, wxEXPAND);
    m_col->AddSpacer(14);

    // Input
    m_input = new TodoInput(m_root);
    m_input->GetTextCtrl()->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnAddTodo, this);
    m_col->Add(m_input, 0, wxEXPAND);
    m_col->AddSpacer(14);

    // Tabs
    m_tabMenu = new TabMenu(m_root);
    m_tabMenu->Bind(EVT_TAB_CHANGED, &MainFrame::OnTabChanged, this);
    m_col->Add(m_tabMenu, 0, wxEXPAND);
    m_col->AddSpacer(3);

    // Todo list
    m_todoList = new TodoList(m_root);
    m_todoList->Bind(EVT_TOGGLE_TODO, &MainFrame::OnToggleTodo, this);
    m_col->Add(m_todoList, 1, wxEXPAND);

    auto* frameSizer = new wxBoxSizer(wxVERTICAL);
    frameSizer->Add(m_root, 1, wxEXPAND);
    SetSizer(frameSizer);

    RefreshList();
}

void MainFrame::OnAddTodo(wxCommandEvent&) {
    wxString text = m_input->GetTextCtrl()->GetValue().Trim();
    if (text.empty()) return;
    m_todoModel.addTodo(text);
    m_input->GetTextCtrl()->Clear();
    RefreshList();
}

void MainFrame::OnTabChanged(wxCommandEvent& e) {
    m_menuModel.activeTab = static_cast<TabFilter>(e.GetInt());
    m_tabMenu->SetActive(m_menuModel.activeTab);
    RefreshList();
}

void MainFrame::OnToggleTodo(wxCommandEvent& e) {
    m_todoModel.toggleCompleted(e.GetInt());
    RefreshList();
}

void MainFrame::RefreshList() {
    if (!m_todoList) return;
    m_todoList->Refresh(m_todoModel.filteredTodos(m_menuModel.activeTab));
}