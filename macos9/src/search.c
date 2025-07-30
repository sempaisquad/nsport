#include "macos9_gui.h"

static void macos9_search_set_status(bool found, void *p)
{
    (void)found; (void)p;
}

static void macos9_search_set_hourglass(bool active, void *p)
{
    (void)active; (void)p;
}

static void macos9_search_add_recent(const char *string, void *p)
{
    (void)string; (void)p;
}

static void macos9_search_set_forward_state(bool active, void *p)
{
    (void)active; (void)p;
}

static void macos9_search_set_back_state(bool active, void *p)
{
    (void)active; (void)p;
}

struct gui_search_table macos9_search_table = {
    .status = macos9_search_set_status,
    .hourglass = macos9_search_set_hourglass,
    .add_recent = macos9_search_add_recent,
    .forward_state = macos9_search_set_forward_state,
    .back_state = macos9_search_set_back_state,
};
