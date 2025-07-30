#include "macos9_gui.h"

struct macos9_scheduled_event {
    void (*callback)(void *p);
    void *p;
    unsigned long when;
    struct macos9_scheduled_event *next;
};

static struct macos9_scheduled_event *scheduled_events = NULL;

static nserror macos9_schedule(int t, void (*callback)(void *p), void *p)
{
    struct macos9_scheduled_event *event;
    unsigned long when;

    if (t < 0) {
        struct macos9_scheduled_event **current = &scheduled_events;

        while (*current != NULL) {
            if ((*current)->callback == callback && (*current)->p == p) {
                struct macos9_scheduled_event *to_remove = *current;
                *current = (*current)->next;
                free(to_remove);
            } else {
                current = &(*current)->next;
            }
        }

        return NSERROR_OK;
    }

    event = malloc(sizeof(struct macos9_scheduled_event));
    if (event == NULL) {
        return NSERROR_NOMEM;
    }

    when = TickCount() + (t * 60) / 1000;

    event->callback = callback;
    event->p = p;
    event->when = when;

    if (scheduled_events == NULL || scheduled_events->when > when) {
        event->next = scheduled_events;
        scheduled_events = event;
    } else {
        struct macos9_scheduled_event *current = scheduled_events;
        while (current->next != NULL && current->next->when <= when) {
            current = current->next;
        }
        event->next = current->next;
        current->next = event;
    }

    return NSERROR_OK;
}

void macos9_schedule_run(void)
{
    unsigned long now = TickCount();

    while (scheduled_events != NULL && scheduled_events->when <= now) {
        struct macos9_scheduled_event *event = scheduled_events;
        scheduled_events = event->next;

        event->callback(event->p);
        free(event);
    }
}

struct gui_misc_table macos9_misc_table = {
    .schedule = macos9_schedule,
    .quit = macos9_quit,
    .present_cookies = NULL,
};
