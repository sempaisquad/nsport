#ifndef NETSURF_MACOS9_GUI_H
#define NETSURF_MACOS9_GUI_H

#include <Carbon/Carbon.h>
#include <MacTypes.h>
#include <Events.h>
#include <Windows.h>
#include <Controls.h>
#include <Menus.h>
#include <TextEdit.h>
#include <Dialogs.h>
#include <Resources.h>
#include <Fonts.h>
#include <QuickDraw.h>
#include <FixMath.h>
#include <Sound.h>
#include <Gestalt.h>
#include <Navigation.h>

#include "utils/config.h"
#include "utils/log.h"
#include "netsurf/browser_window.h"
#include "netsurf/window.h"
#include "netsurf/plotters.h"
#include "netsurf/bitmap.h"

// Window structure for Mac OS 9
struct gui_window {
    WindowPtr window;
    ControlRef vscrollbar;
    ControlRef hscrollbar;
    ControlRef url_bar;
    ControlRef status_bar;
    struct browser_window *bw;
    int scroll_x;
    int scroll_y;
    int width;
    int height;
    bool redraw_pending;
    struct gui_window *next;
};

// Bitmap structure
struct bitmap {
    GWorldPtr gworld;
    PixMapHandle pixmap;
    int width;
    int height;
    bool opaque;
};

// Function prototypes
OSErr InitializeApplication(void);
void RunEventLoop(void);
void HandleEvent(EventRecord *event);
void HandleMenuChoice(long menuChoice);
void HandleMouseDown(EventRecord *event);
void HandleUpdate(EventRecord *event);
void HandleKeyDown(EventRecord *event);

// GUI callbacks
struct gui_window *gui_create_browser_window(struct browser_window *bw,
                                           struct gui_window *existing,
                                           bool new_tab);
void gui_window_destroy(struct gui_window *g);
void gui_window_set_title(struct gui_window *g, const char *title);
void gui_window_redraw_window(struct gui_window *g);
void gui_window_update_box(struct gui_window *g, const struct rect *rect);
bool gui_window_get_scroll(struct gui_window *g, int *sx, int *sy);
void gui_window_set_scroll(struct gui_window *g, int sx, int sy);
void gui_window_get_dimensions(struct gui_window *g, int *width, int *height);
void gui_window_event(struct gui_window *g, enum gui_window_event event);

// Bitmap callbacks
void *bitmap_create(int width, int height, unsigned int state);
void bitmap_destroy(void *bitmap);
void bitmap_set_opaque(void *bitmap, bool opaque);
bool bitmap_test_opaque(void *bitmap);
bool bitmap_get_opaque(void *bitmap);
unsigned char *bitmap_get_buffer(void *bitmap);
size_t bitmap_get_rowstride(void *bitmap);
size_t bitmap_get_bpp(void *bitmap);
bool bitmap_save(void *bitmap, const char *path, unsigned flags);
void bitmap_modified(void *bitmap);
void bitmap_set_suspendable(void *bitmap, void *private_word, 
                           void (*invalidate)(void *private_word));

// Plotter functions
bool macos9_plot_clip(const struct redraw_context *ctx, const struct rect *rect);
bool macos9_plot_arc(const struct redraw_context *ctx, const plot_style_t *style,
                     int x, int y, int radius, int angle1, int angle2);
bool macos9_plot_disc(const struct redraw_context *ctx, const plot_style_t *style,
                      int x, int y, int radius);
bool macos9_plot_line(const struct redraw_context *ctx, const plot_style_t *style,
                      const struct rect *line);
bool macos9_plot_rectangle(const struct redraw_context *ctx, const plot_style_t *style,
                          const struct rect *rect);
bool macos9_plot_polygon(const struct redraw_context *ctx, const plot_style_t *style,
                        const int *p, unsigned int n);
bool macos9_plot_path(const struct redraw_context *ctx, const plot_style_t *pstyle,
                     const float *p, unsigned int n, const float transform[6]);
bool macos9_plot_bitmap(const struct redraw_context *ctx, struct bitmap *bitmap,
                       int x, int y, int width, int height,
                       colour bg, bitmap_flags_t flags);
bool macos9_plot_text(const struct redraw_context *ctx, const plot_font_style_t *fstyle,
                     int x, int y, const char *text, size_t length);

// Constants
#define WINDOW_MIN_WIDTH 320
#define WINDOW_MIN_HEIGHT 240
#define SCROLLBAR_WIDTH 16
#define URL_BAR_HEIGHT 24
#define STATUS_BAR_HEIGHT 16

// Menu resource IDs
#define MENU_APPLE 128
#define MENU_FILE 129
#define MENU_EDIT 130
#define MENU_VIEW 131
#define MENU_GO 132

#define ITEM_ABOUT 1
#define ITEM_NEW 1
#define ITEM_OPEN 2
#define ITEM_CLOSE 3
#define ITEM_SAVE 4
#define ITEM_QUIT 6

// Dialog resource IDs
#define DIALOG_ABOUT 128
#define ALERT_ERROR 129

// Control IDs
#define CONTROL_URL_BAR 1000
#define CONTROL_VSCROLL 1001
#define CONTROL_HSCROLL 1002
#define CONTROL_STATUS 1003

#endif // NETSURF_MACOS9_GUI_H
