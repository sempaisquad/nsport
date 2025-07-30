#include "macos9_gui.h"

static void macos9_poll(bool active)
{
}

static void macos9_quit(void)
{
    application_running = false;
}

static void macos9_set_scroll(struct gui_window *g, int sx, int sy)
{
    g->scroll_x = sx;
    g->scroll_y = sy;

    if (g->vscrollbar != NULL) {
        SetControlValue(g->vscrollbar, sy);
    }
    if (g->hscrollbar != NULL) {
        SetControlValue(g->hscrollbar, sx);
    }
}

static void macos9_get_scroll(struct gui_window *g, int *sx, int *sy)
{
    *sx = g->scroll_x;
    *sy = g->scroll_y;
}

struct gui_misc_table macos9_misc_table = {
    .poll = macos9_poll,
    .quit = macos9_quit,
};
