#include "mainwindow.h"
#include "theme.h"
#include "todoitemwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QPalette>
#include <QFrame>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    setFixedSize(800, 600);
    setupUi();
    refreshList();
    refreshTabs();
}

void MainWindow::setupUi() {
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Theme::BG);
    setPalette(pal);
    setAutoFillBackground(true);

    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(Theme::CONTENT_H, Theme::CONTENT_V,
                             Theme::CONTENT_H, Theme::CONTENT_V);
    root->setSpacing(0);

    // Title
    auto *title = new QLabel("ToDo");
    QFont tf = title->font();
    tf.setPixelSize(18);
    tf.setBold(true);
    title->setFont(tf);
    QPalette tp = title->palette();
    tp.setColor(QPalette::WindowText, Theme::WHITE);
    title->setPalette(tp);
    root->addWidget(title);
    root->addSpacing(14);

    // Input
    m_input = new QLineEdit;
    m_input->setFixedHeight(Theme::INPUT_H);
    m_input->setPlaceholderText("Add Task");
    m_input->setStyleSheet(QString(
        "QLineEdit {"
        "  background: %1;"
        "  color: %2;"
        "  border: 1px solid transparent;"
        "  border-radius: 4px;"
        "  padding: 4px 16px;"
        "}"
        "QLineEdit:focus {"
        "  border: 1px solid %3;"
        "}"
    ).arg(Theme::INPUT.name(), Theme::WHITE.name(), Theme::ACCENT.name()));

    QPalette ip = m_input->palette();
    ip.setColor(QPalette::PlaceholderText, Theme::MUTED);
    m_input->setPalette(ip);

    connect(m_input, &QLineEdit::returnPressed, this, &MainWindow::onAddTodo);
    root->addWidget(m_input);
    root->addSpacing(14);

    // Tabs
    auto *tabRow = new QHBoxLayout;
    tabRow->setContentsMargins(0, 0, 0, 0);
    tabRow->setSpacing(0);

    auto makeTab = [&](const QString &text) -> QLabel * {
        auto *lbl = new QLabel(text);
        QFont f = lbl->font();
        f.setPixelSize(14);
        lbl->setFont(f);
        QPalette p = lbl->palette();
        p.setColor(QPalette::WindowText, Theme::TEXT);
        lbl->setPalette(p);
        lbl->setContentsMargins(8, 0, 8, 0);
        lbl->setFixedHeight(28);
        lbl->setCursor(Qt::PointingHandCursor);
        lbl->installEventFilter(this);
        tabRow->addWidget(lbl);
        return lbl;
    };

    m_tabAll       = makeTab("All");
    m_tabActive    = makeTab("Active");
    m_tabCompleted = makeTab("Completed");
    tabRow->addStretch();
    root->addLayout(tabRow);
    root->addSpacing(3);

    // Scroll area
    m_scrollArea = new QScrollArea;
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setFrameShape(QFrame::NoFrame);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setStyleSheet("QScrollArea { background: transparent; border: none; }");
    m_scrollArea->viewport()->setStyleSheet("background: transparent;");

    m_listContainer = new QWidget;
    m_listContainer->setAutoFillBackground(false);
    m_listContainer->setStyleSheet("background: transparent;");

    m_listLayout = new QVBoxLayout(m_listContainer);
    m_listLayout->setContentsMargins(0, 0, 0, 0);
    m_listLayout->setSpacing(Theme::ITEM_MB);
    m_listLayout->addStretch();

    m_scrollArea->setWidget(m_listContainer);
    root->addWidget(m_scrollArea, 1);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {
        if (obj == m_tabAll)       { onTabClicked(TabFilter::All);       return true; }
        if (obj == m_tabActive)    { onTabClicked(TabFilter::Active);    return true; }
        if (obj == m_tabCompleted) { onTabClicked(TabFilter::Completed); return true; }
    }
    return QWidget::eventFilter(obj, event);
}

void MainWindow::onAddTodo() {
    QString text = m_input->text().trimmed();
    if (text.isEmpty()) return;
    m_todoModel.addTodo(text);
    m_input->clear();
    refreshList();
}

void MainWindow::onToggle(int id) {
    m_todoModel.toggleCompleted(id);
    refreshList();
}

void MainWindow::onTabClicked(TabFilter tab) {
    m_menuModel.setActiveTab(tab);
    refreshTabs();
    refreshList();
}

void MainWindow::refreshList() {
    while (m_listLayout->count() > 1) {
        auto *item = m_listLayout->takeAt(0);
        if (item->widget()) delete item->widget();
        delete item;
    }
    for (const auto &todo : m_todoModel.filteredTodos(m_menuModel.activeTab())) {
        auto *row = new TodoItemWidget(todo, m_listContainer);
        connect(row, &TodoItemWidget::toggleRequested, this, &MainWindow::onToggle);
        m_listLayout->insertWidget(m_listLayout->count() - 1, row);
    }
}

void MainWindow::refreshTabs() {
    auto applyBold = [&](QLabel *lbl, TabFilter filter) {
        QFont f = lbl->font();
        f.setBold(m_menuModel.activeTab() == filter);
        lbl->setFont(f);
    };
    applyBold(m_tabAll,       TabFilter::All);
    applyBold(m_tabActive,    TabFilter::Active);
    applyBold(m_tabCompleted, TabFilter::Completed);
}