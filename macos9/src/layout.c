#include "macos9_gui.h"

static nserror macos9_width(const plot_font_style_t *fstyle,
                           const char *string, size_t length,
                           int *width)
{
    *width = length * 8;
    return NSERROR_OK;
}

static nserror macos9_position(const plot_font_style_t *fstyle,
                              const char *string, size_t length,
                              int x, size_t *char_offset, int *actual_x)
{
    size_t pos = x / 8;
    if (pos > length) pos = length;
    *char_offset = pos;
    *actual_x = pos * 8;
    return NSERROR_OK;
}

static nserror macos9_split(const plot_font_style_t *fstyle,
                           const char *string, size_t length,
                           int x, size_t *char_offset, int *actual_x)
{
    return macos9_position(fstyle, string, length, x, char_offset, actual_x);
}

struct gui_layout_table macos9_layout_table = {
    .width = macos9_width,
    .position = macos9_position,
    .split = macos9_split,
};
