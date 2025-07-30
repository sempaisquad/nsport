#include "macos9_gui.h"

static void macos9_search_set_status(bool found, void *p)
{
}

static void macos9_search_set_hourglass(bool active, void *p)
{
    if (active) {
        SetCursor(*GetCursor(watchCursor));
    } else {
        SetCursor(&qd.arrow);
    }
}

static void macos9_search_add_recent(const char *string, void *p)
{
}

static void macos9_search_set_forward_state(bool active, void *p)
{
}

static void macos9_search_set_back_state(bool active, void *p)
{
}

struct gui_search_table macos9_search_table = {
    .status = macos9_search_set_status,
    .hourglass = macos9_search_set_hourglass,
    .add_recent = macos9_search_add_recent,
    .forward_state = macos9_search_set_forward_state,
    .back_state = macos9_search_set_back_state,
};
