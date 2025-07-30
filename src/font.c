#include "macos9_gui.h"

static bool macos9_font_paint(const plot_font_style_t *fstyle,
                             const char *string, size_t length,
                             int x, int y)
{
    return macos9_plot_text(NULL, fstyle, x, y, string, length);
}

static bool macos9_font_width(const plot_font_style_t *fstyle,
                             const char *string, size_t length,
                             int *width)
{
    nserror ret = macos9_width(fstyle, string, length, width);
    return ret == NSERROR_OK;
}

static bool macos9_font_position_in_string(const plot_font_style_t *fstyle,
                                          const char *string, size_t length,
                                          int x, size_t *char_offset,
                                          int *actual_x)
{
    nserror ret = macos9_position(fstyle, string, length, x, char_offset, actual_x);
    return ret == NSERROR_OK;
}

static bool macos9_font_split(const plot_font_style_t *fstyle,
                             const char *string, size_t length,
                             int x, size_t *char_offset, int *actual_x)
{
    nserror ret = macos9_split(fstyle, string, length, x, char_offset, actual_x);
    return ret == NSERROR_OK;
}

const struct font_functions nsfont = {
    .font_paint = macos9_font_paint,
    .font_width = macos9_font_width,
    .font_position_in_string = macos9_font_position_in_string,
    .font_split = macos9_font_split,
};
