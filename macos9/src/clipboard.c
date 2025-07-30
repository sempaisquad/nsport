#include "macos9_gui.h"

static void macos9_get_clipboard(char **buffer, size_t *length)
{
    *buffer = NULL;
    *length = 0;
}

static void macos9_set_clipboard(const char *buffer, size_t length,
                                nsclipboard_styles styles[], int n_styles)
{
    (void)buffer; (void)length; (void)styles; (void)n_styles;
}

struct gui_clipboard_table macos9_clipboard_table = {
    .get = macos9_get_clipboard,
    .set = macos9_set_clipboard,
};
