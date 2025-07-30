#include "macos9_gui.h"

struct gui_window_history {
    WindowPtr window;
    struct browser_window *bw;
};

static struct gui_window_history *macos9_local_history_create(struct gui_window *gw)
{
    struct gui_window_history *history;

    history = calloc(1, sizeof(struct gui_window_history));
    if (history == NULL) {
        return NULL;
    }

    history->bw = gw->bw;

    return history;
}

static void macos9_local_history_destroy(struct gui_window_history *history)
{
    if (history == NULL) return;

    if (history->window != NULL) {
        DisposeWindow(history->window);
    }

    free(history);
}

static nserror macos9_local_history_set(struct gui_window *gw,
                                       struct gui_window_history *history,
                                       nsurl *url)
{
    return NSERROR_OK;
}

static nserror macos9_local_history_get_url(struct gui_window_history *history,
                                          nsurl **url_out)
{
    return NSERROR_NOT_IMPLEMENTED;
}

struct gui_window_history_table macos9_history_table = {
    .create = macos9_local_history_create,
    .destroy = macos9_local_history_destroy,
    .set = macos9_local_history_set,
    .get_url = macos9_local_history_get_url,
};
