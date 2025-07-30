#include "macos9_gui.h"

static void macos9_poll(bool active)
{
    /* polling handled in main loop */
}

static void macos9_quit(void)
{
    application_running = false;
}

static void macos9_set_scroll(struct gui_window *g, int sx, int sy)
{
    g->scroll_x = sx;
    g->scroll_y = sy;
}

static void macos9_get_scroll(struct gui_window *g, int *sx, int *sy)
{
    *sx = g->scroll_x;
    *sy = g->scroll_y;
}

