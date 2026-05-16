#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Lifecycle */
void* app_init(int width, int height, const char* title);
bool  app_should_close(void* win);
void  app_new_frame(void* win);
void  app_render(void* win);
void  app_shutdown(void* win);

/* Window */
void app_begin_window(void);
void app_end_window(void);

/* Widgets – return true on interaction */
void app_draw_title(const char* text);
bool app_draw_input(char* buf, int buf_size);
void app_begin_tab_row(void);
bool app_draw_tab(const char* label, bool active);
void app_end_tab_row(void);
void app_begin_todo_list(float avail_h);
/* Returns true when checkbox is clicked */
bool app_draw_todo_item(const char* id_str, const char* text, bool completed);
void app_end_todo_list(void);

#ifdef __cplusplus
}
#endif