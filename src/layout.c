#include "macos9_gui.h"

static nserror macos9_width(const plot_font_style_t *fstyle,
                           const char *string, size_t length,
                           int *width)
{
    if (string == NULL || length == 0) {
        *width = 0;
        return NSERROR_OK;
    }

    short fontNum;
    GetFNum("\pGeneva", &fontNum);
    TextFont(fontNum);
    TextSize(fstyle->size / FONT_SIZE_SCALE);

    short style = normal;
    if (fstyle->weight >= 700) style |= bold;
    if (fstyle->flags & FONTF_ITALIC) style |= italic;
    TextFace(style);

    *width = TextWidth(string, 0, length);

    return NSERROR_OK;
}

static nserror macos9_position(const plot_font_style_t *fstyle,
                              const char *string, size_t length,
                              int x, size_t *char_offset, int *actual_x)
{
    if (string == NULL || length == 0) {
        *char_offset = 0;
        *actual_x = 0;
        return NSERROR_OK;
    }

    short fontNum;
    GetFNum("\pGeneva", &fontNum);
    TextFont(fontNum);
    TextSize(fstyle->size / FONT_SIZE_SCALE);

    short style = normal;
    if (fstyle->weight >= 700) style |= bold;
    if (fstyle->flags & FONTF_ITALIC) style |= italic;
    TextFace(style);

    int current_x = 0;
    size_t i;

    for (i = 0; i < length; i++) {
        int char_width = CharWidth(string[i]);
        if (current_x + char_width / 2 >= x) {
            break;
        }
        current_x += char_width;
    }

    *char_offset = i;
    *actual_x = current_x;

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
