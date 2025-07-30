#include "macos9_gui.h"

struct gui_window *gui_create_browser_window(struct browser_window *bw,
                                           struct gui_window *existing,
                                           bool new_tab)
{
    struct gui_window *g;
    WindowPtr window;
    Rect windowBounds = {50, 50, 400, 600};

    g = calloc(1, sizeof(struct gui_window));
    if (g == NULL) {
        return NULL;
    }

    window = NewCWindow(NULL, &windowBounds, "\pNetSurf", true,
                       documentProc, (WindowPtr)-1, true, 0);
    if (window == NULL) {
        free(g);
        return NULL;
    }

    g->window = window;
    g->bw = bw;
    g->width = windowBounds.right - windowBounds.left;
    g->height = windowBounds.bottom - windowBounds.top;
    g->scroll_x = 0;
    g->scroll_y = 0;
    g->redraw_pending = false;

    SetWRefCon(window, (long)g);

    Rect scrollRect;

    scrollRect.left = g->width - SCROLLBAR_WIDTH;
    scrollRect.top = -1;
    scrollRect.right = g->width + 1;
    scrollRect.bottom = g->height - SCROLLBAR_WIDTH + 1;

    g->vscrollbar = NewControl(window, &scrollRect, "\p", true, 0, 0, 100,
                              scrollBarProc, CONTROL_VSCROLL);

    scrollRect.left = -1;
    scrollRect.top = g->height - SCROLLBAR_WIDTH;
    scrollRect.right = g->width - SCROLLBAR_WIDTH + 1;
    scrollRect.bottom = g->height + 1;

    g->hscrollbar = NewControl(window, &scrollRect, "\p", true, 0, 0, 100,
                              scrollBarProc, CONTROL_HSCROLL);

    g->next = window_list;
    window_list = g;

    ShowWindow(window);
    SelectWindow(window);

    return g;
}

void gui_window_destroy(struct gui_window *g)
{
    if (g == NULL) return;

    if (window_list == g) {
        window_list = g->next;
    } else {
        struct gui_window *prev = window_list;
        while (prev != NULL && prev->next != g) {
            prev = prev->next;
        }
        if (prev != NULL) {
            prev->next = g->next;
        }
    }

    if (g->bw != NULL) {
        browser_window_destroy(g->bw);
    }

    if (g->vscrollbar != NULL) {
        DisposeControl(g->vscrollbar);
    }
    if (g->hscrollbar != NULL) {
        DisposeControl(g->hscrollbar);
    }

    if (g->window != NULL) {
        DisposeWindow(g->window);
    }

    free(g);

    if (window_list == NULL) {
        application_running = false;
    }
}

void gui_window_set_title(struct gui_window *g, const char *title)
{
    if (g == NULL || g->window == NULL) return;

    Str255 ptitle;
    int len = strlen(title);
    if (len > 255) len = 255;

    ptitle[0] = len;
    memcpy(&ptitle[1], title, len);

    SetWTitle(g->window, ptitle);
}

void gui_window_redraw_window(struct gui_window *g)
{
    if (g == NULL || g->window == NULL) return;

    SetPort(GetWindowPort(g->window));

    Rect contentRect;
    GetWindowPortBounds(g->window, &contentRect);

    contentRect.right -= SCROLLBAR_WIDTH;
    contentRect.bottom -= SCROLLBAR_WIDTH;

    struct rect clip = {
        .x0 = contentRect.left,
        .y0 = contentRect.top,
        .x1 = contentRect.right,
        .y1 = contentRect.bottom
    };

    struct redraw_context ctx = {
        .interactive = true,
        .background_images = true,
        .plot = &macos9_plotters
    };

    browser_window_redraw(g->bw, g->scroll_x, g->scroll_y, &clip, &ctx);
}

void gui_window_update_box(struct gui_window *g, const struct rect *rect)
{
    if (g == NULL || g->window == NULL) return;

    Rect updateRect;
    updateRect.left = rect->x0 - g->scroll_x;
    updateRect.top = rect->y0 - g->scroll_y;
    updateRect.right = rect->x1 - g->scroll_x;
    updateRect.bottom = rect->y1 - g->scroll_y;

    InvalWindowRect(g->window, &updateRect);
    g->redraw_pending = true;
}

bool gui_window_get_scroll(struct gui_window *g, int *sx, int *sy)
{
    if (g == NULL) return false;

    *sx = g->scroll_x;
    *sy = g->scroll_y;
    return true;
}

void gui_window_set_scroll(struct gui_window *g, int sx, int sy)
{
    if (g == NULL) return;

    macos9_set_scroll(g, sx, sy);
    gui_window_redraw_window(g);
}

void gui_window_get_dimensions(struct gui_window *g, int *width, int *height)
{
    if (g == NULL) return;

    Rect contentRect;
    GetWindowPortBounds(g->window, &contentRect);

    *width = contentRect.right - contentRect.left - SCROLLBAR_WIDTH;
    *height = contentRect.bottom - contentRect.top - SCROLLBAR_WIDTH;

    g->width = *width;
    g->height = *height;
}

void gui_window_event(struct gui_window *g, enum gui_window_event event)
{
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
