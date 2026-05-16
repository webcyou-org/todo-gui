#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define WX_MAX_TODOS    256
#define WX_MAX_TASK_LEN 256

typedef struct {
    unsigned int id;
    char         task[WX_MAX_TASK_LEN];
    int          is_completed;
} WxTodo;

typedef enum {
    WX_TAB_ALL       = 0,
    WX_TAB_ACTIVE    = 1,
    WX_TAB_COMPLETED = 2,
} WxTabFilter;

typedef struct {
    WxTodo       todos[WX_MAX_TODOS];
    int          todo_count;
    WxTabFilter  active_tab;
    unsigned int next_id;
} WxAppState;

/* Zig-exported CRUD functions */
void state_add_todo   (WxAppState* state, const char* task);
void state_toggle_todo(WxAppState* state, unsigned int id);
void state_set_tab    (WxAppState* state, WxTabFilter tab);

#ifdef __cplusplus
}
#endif