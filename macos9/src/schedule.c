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
    struct macos9_scheduled_event *event = malloc(sizeof(*event));
    if (!event) return NSERROR_NOMEM;

    event->callback = callback;
    event->p = p;
    event->when = TickCount() + (t * 60) / 1000;
    event->next = scheduled_events;
    scheduled_events = event;

    return NSERROR_OK;
}

void macos9_schedule_run(void)
{
    unsigned long now = TickCount();
    struct macos9_scheduled_event *prev = NULL;
    struct macos9_scheduled_event *cur = scheduled_events;
    while (cur) {
        if (cur->when <= now) {
            cur->callback(cur->p);
            if (prev) prev->next = cur->next; else scheduled_events = cur->next;
            struct macos9_scheduled_event *tmp = cur;
            cur = cur->next;
            free(tmp);
        } else {
            prev = cur;
            cur = cur->next;
        }
    }
}

