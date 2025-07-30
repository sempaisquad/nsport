#include "macos9_gui.h"

struct gui_window *gui_create_browser_window(struct browser_window *bw,
                                           struct gui_window *existing,
                                           bool new_tab)
{
    struct gui_window *g = calloc(1, sizeof(struct gui_window));
    if (g == NULL) return NULL;

    g->bw = bw;
    g->width = 640;
    g->height = 480;
    g->next = window_list;
    window_list = g;
    return g;
}

void gui_window_destroy(struct gui_window *g)
{
    if (g == NULL) return;

    if (window_list == g) {
        window_list = g->next;
    } else {
        struct gui_window *p = window_list;
        while (p && p->next != g) p = p->next;
        if (p) p->next = g->next;
    }

    browser_window_destroy(g->bw);
    free(g);

    if (window_list == NULL)
        application_running = false;
}

void gui_window_set_title(struct gui_window *g, const char *title)
{
    (void)g; (void)title;
}

void gui_window_redraw_window(struct gui_window *g)
{
    (void)g;
}

void gui_window_update_box(struct gui_window *g, const struct rect *rect)
{
    (void)g; (void)rect;
}

bool gui_window_get_scroll(struct gui_window *g, int *sx, int *sy)
{
    *sx = g->scroll_x;
    *sy = g->scroll_y;
    return true;
}

void gui_window_set_scroll(struct gui_window *g, int sx, int sy)
{
    macos9_set_scroll(g, sx, sy);
}

void gui_window_get_dimensions(struct gui_window *g, int *width, int *height)
{
    *width = g->width;
    *height = g->height;
}

void gui_window_event(struct gui_window *g, enum gui_window_event event)
{
    (void)g; (void)event;
}

struct gui_window_table macos9_window_table = {
    .create = gui_create_browser_window,
    .destroy = gui_window_destroy,
    .invalidate = gui_window_update_box,
    .get_scroll = gui_window_get_scroll,
    .set_scroll = gui_window_set_scroll,
    .get_dimensions = gui_window_get_dimensions,
    .event = gui_window_event,
    .set_title = gui_window_set_title,
};
