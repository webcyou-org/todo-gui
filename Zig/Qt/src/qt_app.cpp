#include "qt_bridge.h"
#include "theme.h"
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QCheckBox>
#include <QFrame>
#include <QFont>
#include <QSizePolicy>
#include <QPalette>
#include <QStyleFactory>

// ── global UI references ──────────────────────────────────────────
static QVBoxLayout*  g_todoLayout = nullptr;
static QPushButton*  g_tabs[3]    = { nullptr, nullptr, nullptr };
static TodoCallbacks g_callbacks  = { nullptr, nullptr, nullptr, nullptr };

// ── helpers ───────────────────────────────────────────────────────
static void updateTabStyles(int active_tab) {
    for (int i = 0; i < 3; i++) {
        if (!g_tabs[i]) continue;
        QFont f = g_tabs[i]->font();
        f.setBold(i == active_tab);
        g_tabs[i]->setFont(f);
    }
}

static QWidget* createTodoRow(CTodo todo) {
    QWidget* row = new QWidget();
    row->setFixedHeight(35);

    QString bgStyle = QString("background-color: %1; border-radius: 4px;").arg(C_SURFACE);
    row->setStyleSheet(bgStyle);

    QHBoxLayout* hl = new QHBoxLayout(row);
    hl->setContentsMargins(10, 0, 10, 0);
    hl->setSpacing(0);

    // circular checkbox
    QCheckBox* cb = new QCheckBox();
    cb->setChecked(todo.is_completed);

    QString cbStyle;
    if (todo.is_completed) {
        cbStyle = QString(
            "QCheckBox { spacing: 0px; margin: 0px; }"
            "QCheckBox::indicator {"
            "  width: 16px; height: 16px; border-radius: 8px;"
            "  background-color: transparent; border: 2px solid %1;"
            "}").arg(C_CB_BORDER);
    } else {
        cbStyle = QString(
            "QCheckBox { spacing: 0px; margin: 0px; }"
            "QCheckBox::indicator {"
            "  width: 16px; height: 16px; border-radius: 8px;"
            "  border: 2px solid %1; background-color: transparent;"
            "}").arg(C_CB_BORDER);
    }
    cb->setStyleSheet(cbStyle);

    int todo_id = todo.id;
    QObject::connect(cb, &QAbstractButton::clicked, [todo_id]() {
        g_callbacks.toggle_todo(todo_id);
    });

    // task label
    QLabel* label = new QLabel(QString::fromUtf8(todo.task));
    QString labelStyle;
    if (todo.is_completed) {
        labelStyle = QString(
            "color: %1; text-decoration: line-through;"
            " background-color: transparent; font-size: 14px;"
        ).arg(C_MUTED);
    } else {
        labelStyle = QString(
            "color: %1; background-color: transparent; font-size: 14px;"
        ).arg(C_TEXT);
    }
    label->setStyleSheet(labelStyle);

    hl->addWidget(cb);
    hl->addSpacing(18);
    hl->addWidget(label);
    hl->addStretch();

    return row;
}

// ── C interface ───────────────────────────────────────────────────
extern "C" {

void qt_update_todos(const CTodo* todos, int count, int active_tab) {
    if (!g_todoLayout) return;

    // clear current items
    while (g_todoLayout->count() > 0) {
        QLayoutItem* item = g_todoLayout->takeAt(0);
        if (QWidget* w = item->widget()) w->deleteLater();
        delete item;
    }

    // add updated items
    for (int i = 0; i < count; i++) {
        g_todoLayout->addWidget(createTodoRow(todos[i]));
    }

    updateTabStyles(active_tab);
}

int qt_run(int width, int height, const char* title, TodoCallbacks cbs) {
    g_callbacks = cbs;

    static int   fake_argc    = 1;
    static char  prog[]       = "todo";
    static char* fake_argv[1] = { prog };

    QApplication app(fake_argc, fake_argv);
    app.setStyle(QStyleFactory::create("Fusion"));

    // ── main window ──────────────────────────────────────
    QMainWindow mainWin;
    mainWin.setWindowTitle(title);
    mainWin.resize(width, height);

    QWidget* central = new QWidget();
    mainWin.setCentralWidget(central);
    central->setStyleSheet(
        QString("QWidget { background-color: %1; }").arg(C_BG)
    );

    QVBoxLayout* vbox = new QVBoxLayout(central);
    vbox->setContentsMargins(24, 10, 24, 10);
    vbox->setSpacing(0);

    // ── Step 2: title ─────────────────────────────────────
    QLabel* titleLbl = new QLabel(title);
    titleLbl->setStyleSheet(
        QString("color: %1; background-color: transparent;"
                " font-size: 18px; font-weight: bold;").arg(C_WHITE)
    );
    vbox->addWidget(titleLbl);
    vbox->addSpacing(14);

    // ── Step 3: input ─────────────────────────────────────
    QLineEdit* lineEdit = new QLineEdit();
    lineEdit->setPlaceholderText("Add Task");
    lineEdit->setFixedHeight(35);
    lineEdit->setStyleSheet(
        QString(
            "QLineEdit {"
            "  background-color: %1; color: %2;"
            "  border: 1px solid transparent; border-radius: 4px;"
            "  padding-left: 16px; padding-right: 16px;"
            "}"
            "QLineEdit:focus { border: 1px solid %3; }"
        ).arg(C_INPUT).arg(C_WHITE).arg(C_ACCENT)
    );
    QPalette ple = lineEdit->palette();
    ple.setColor(QPalette::PlaceholderText, QColor(C_MUTED));
    lineEdit->setPalette(ple);

    QObject::connect(lineEdit, &QLineEdit::returnPressed, [=]() {
        QString text = lineEdit->text().trimmed();
        if (!text.isEmpty()) {
            QByteArray ba = text.toUtf8();
            g_callbacks.add_todo(ba.constData());
            lineEdit->clear();
        }
    });

    vbox->addWidget(lineEdit);
    vbox->addSpacing(14);

    // ── Step 4: tab menu ──────────────────────────────────
    QHBoxLayout* tabRow = new QHBoxLayout();
    tabRow->setContentsMargins(0, 0, 0, 0);
    tabRow->setSpacing(0);

    const char* tabNames[3] = { "All", "Active", "Completed" };
    for (int i = 0; i < 3; i++) {
        QPushButton* btn = new QPushButton(tabNames[i]);
        btn->setFixedHeight(28);
        btn->setStyleSheet(
            QString(
                "QPushButton {"
                "  color: %1; background: transparent; border: none;"
                "  padding: 0px 8px; font-size: 14px;"
                "}"
                "QPushButton:hover { color: %2; }"
            ).arg(C_TEXT).arg(C_WHITE)
        );
        int idx = i;
        QObject::connect(btn, &QPushButton::clicked, [idx]() {
            g_callbacks.set_tab(idx);
        });
        g_tabs[i] = btn;
        tabRow->addWidget(btn);
    }
    tabRow->addStretch();

    vbox->addLayout(tabRow);
    vbox->addSpacing(3);

    // ── Step 5: todo list in scroll area ──────────────────
    QScrollArea* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setStyleSheet(
        QString("QScrollArea { background-color: %1; border: none; }"
                "QScrollBar:vertical { background: %1; width: 6px; border: none; }"
                "QScrollBar::handle:vertical {"
                "  background: #404040; border-radius: 3px; min-height: 20px;"
                "}"
                "QScrollBar::add-line:vertical,"
                "QScrollBar::sub-line:vertical { height: 0px; }"
        ).arg(C_BG)
    );

    QWidget* container = new QWidget();
    container->setStyleSheet(
        QString("background-color: %1;").arg(C_BG)
    );

    g_todoLayout = new QVBoxLayout(container);
    g_todoLayout->setContentsMargins(0, 0, 0, 0);
    g_todoLayout->setSpacing(5);
    g_todoLayout->setAlignment(Qt::AlignTop);

    scroll->setWidget(container);
    vbox->addWidget(scroll, 1);

    // notify Zig that the UI is ready → populates initial todo list
    if (g_callbacks.on_ready) g_callbacks.on_ready();

    mainWin.show();
    return app.exec();
}

} // extern "C"