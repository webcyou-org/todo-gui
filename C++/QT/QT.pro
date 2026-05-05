TEMPLATE = app
TARGET   = QT
QT      += widgets
INCLUDEPATH += .

HEADERS += \
    data.h \
    theme.h \
    todomodel.h \
    todoitemwidget.h \
    mainwindow.h

SOURCES += \
    main.cpp \
    todomodel.cpp \
    todoitemwidget.cpp \
    mainwindow.cpp