#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include "todomodel.h"

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void onAddTodo();
    void onToggle(int id);
    void onTabClicked(TabFilter tab);

private:
    void setupUi();
    void refreshList();
    void refreshTabs();

    TodoModel    m_todoModel;
    MenuModel    m_menuModel;

    QLineEdit   *m_input          = nullptr;
    QLabel      *m_tabAll         = nullptr;
    QLabel      *m_tabActive      = nullptr;
    QLabel      *m_tabCompleted   = nullptr;
    QWidget     *m_listContainer  = nullptr;
    QVBoxLayout *m_listLayout     = nullptr;
    QScrollArea *m_scrollArea     = nullptr;
};