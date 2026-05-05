#pragma once
#include <QString>

enum class TabFilter { All, Active, Completed };

struct Todo {
    int     id;
    QString task;
    bool    isCompleted;
};