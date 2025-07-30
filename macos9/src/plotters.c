#include "macos9_gui.h"

static RGBColor color_to_rgb(colour c)
{
    RGBColor rgb;
    rgb.red = ((c >> 16) & 0xFF) << 8;
    rgb.green = ((c >> 8) & 0xFF) << 8;
    rgb.blue = (c & 0xFF) << 8;
    return rgb;
}

bool macos9_plot_clip(const struct redraw_context *ctx, const struct rect *rect)
{
    (void)ctx; (void)rect;
    return true;
}

bool macos9_plot_arc(const struct redraw_context *ctx, const plot_style_t *style,
                     int x, int y, int radius, int angle1, int angle2)
{
    (void)ctx; (void)style; (void)x; (void)y; (void)radius; (void)angle1; (void)angle2;
    return true;
}

bool macos9_plot_disc(const struct redraw_context *ctx, const plot_style_t *style,
                      int x, int y, int radius)
{
    (void)ctx; (void)style; (void)x; (void)y; (void)radius;
    return true;
}

bool macos9_plot_line(const struct redraw_context *ctx, const plot_style_t *style,
                      const struct rect *line)
{
    (void)ctx; (void)style; (void)line;
    return true;
}

bool macos9_plot_rectangle(const struct redraw_context *ctx, const plot_style_t *style,
                          const struct rect *rect)
{
    (void)ctx; (void)style; (void)rect;
    return true;
}

bool macos9_plot_polygon(const struct redraw_context *ctx, const plot_style_t *style,
                        const int *p, unsigned int n)
{
    (void)ctx; (void)style; (void)p; (void)n;
    return true;
}

bool macos9_plot_path(const struct redraw_context *ctx, const plot_style_t *pstyle,
                     const float *p, unsigned int n, const float transform[6])
{
    (void)ctx; (void)pstyle; (void)p; (void)n; (void)transform;
    return true;
}

bool macos9_plot_bitmap(const struct redraw_context *ctx, struct bitmap *bitmap,
                       int x, int y, int width, int height,
                       colour bg, bitmap_flags_t flags)
{
    (void)ctx; (void)bitmap; (void)x; (void)y; (void)width; (void)height;
    (void)bg; (void)flags;
    return true;
}

bool macos9_plot_text(const struct redraw_context *ctx, const plot_font_style_t *fstyle,
                     int x, int y, const char *text, size_t length)
{
    (void)ctx; (void)fstyle; (void)x; (void)y; (void)text; (void)length;
    return true;
}

const struct plotter_table macos9_plotters = {
    .clip = macos9_plot_clip,
    .arc = macos9_plot_arc,
    .disc = macos9_plot_disc,
    .line = macos9_plot_line,
    .rectangle = macos9_plot_rectangle,
    .polygon = macos9_plot_polygon,
    .path = macos9_plot_path,
    .bitmap = macos9_plot_bitmap,
    .text = macos9_plot_text,
    .option_knockout = true,
};
