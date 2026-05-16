#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int id;
    const char* task;
    int is_completed;
} CTodo;

typedef struct {
    void (*add_todo)(const char* task);
    void (*toggle_todo)(int id);
    void (*set_tab)(int tab_idx);
    void (*on_ready)(void);
} TodoCallbacks;

int  qt_run(int width, int height, const char* title, TodoCallbacks cbs);
void qt_update_todos(const CTodo* todos, int count, int active_tab);

#ifdef __cplusplus
}
#endif