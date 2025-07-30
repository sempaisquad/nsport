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
    Rect clipRect;
    clipRect.left = rect->x0;
    clipRect.top = rect->y0;
    clipRect.right = rect->x1;
    clipRect.bottom = rect->y1;

    ClipRect(&clipRect);
    return true;
}

bool macos9_plot_arc(const struct redraw_context *ctx, const plot_style_t *style,
                     int x, int y, int radius, int angle1, int angle2)
{
    if (style->fill_type == PLOT_OP_TYPE_NONE &&
        style->stroke_type == PLOT_OP_TYPE_NONE) {
        return true;
    }

    Rect ovalRect;
    ovalRect.left = x - radius;
    ovalRect.top = y - radius;
    ovalRect.right = x + radius;
    ovalRect.bottom = y + radius;

    if (style->fill_type != PLOT_OP_TYPE_NONE) {
        RGBColor fillColor = color_to_rgb(style->fill_colour);
        RGBForeColor(&fillColor);
        PaintArc(&ovalRect, angle1, angle2 - angle1);
    }

    if (style->stroke_type != PLOT_OP_TYPE_NONE) {
        RGBColor strokeColor = color_to_rgb(style->stroke_colour);
        RGBForeColor(&strokeColor);
        PenSize(style->stroke_width, style->stroke_width);
        FrameArc(&ovalRect, angle1, angle2 - angle1);
    }

    return true;
}

bool macos9_plot_disc(const struct redraw_context *ctx, const plot_style_t *style,
                      int x, int y, int radius)
{
    Rect ovalRect;
    ovalRect.left = x - radius;
    ovalRect.top = y - radius;
    ovalRect.right = x + radius;
    ovalRect.bottom = y + radius;

    if (style->fill_type != PLOT_OP_TYPE_NONE) {
        RGBColor fillColor = color_to_rgb(style->fill_colour);
        RGBForeColor(&fillColor);
        PaintOval(&ovalRect);
    }

    if (style->stroke_type != PLOT_OP_TYPE_NONE) {
        RGBColor strokeColor = color_to_rgb(style->stroke_colour);
        RGBForeColor(&strokeColor);
        PenSize(style->stroke_width, style->stroke_width);
        FrameOval(&ovalRect);
    }

    return true;
}

bool macos9_plot_line(const struct redraw_context *ctx, const plot_style_t *style,
                      const struct rect *line)
{
    if (style->stroke_type == PLOT_OP_TYPE_NONE) {
        return true;
    }

    RGBColor strokeColor = color_to_rgb(style->stroke_colour);
    RGBForeColor(&strokeColor);
    PenSize(style->stroke_width, style->stroke_width);

    MoveTo(line->x0, line->y0);
    LineTo(line->x1, line->y1);

    return true;
}

bool macos9_plot_rectangle(const struct redraw_context *ctx, const plot_style_t *style,
                          const struct rect *rect)
{
    Rect drawRect;
    drawRect.left = rect->x0;
    drawRect.top = rect->y0;
    drawRect.right = rect->x1;
    drawRect.bottom = rect->y1;

    if (style->fill_type != PLOT_OP_TYPE_NONE) {
        RGBColor fillColor = color_to_rgb(style->fill_colour);
        RGBForeColor(&fillColor);
        PaintRect(&drawRect);
    }

    if (style->stroke_type != PLOT_OP_TYPE_NONE) {
        RGBColor strokeColor = color_to_rgb(style->stroke_colour);
        RGBForeColor(&strokeColor);
        PenSize(style->stroke_width, style->stroke_width);
        FrameRect(&drawRect);
    }

    return true;
}

bool macos9_plot_polygon(const struct redraw_context *ctx, const plot_style_t *style,
                        const int *p, unsigned int n)
{
    if (n < 3) return false;

    PolyHandle poly = OpenPoly();

    MoveTo(p[0], p[1]);
    for (unsigned int i = 1; i < n; i++) {
        LineTo(p[i * 2], p[i * 2 + 1]);
    }
    LineTo(p[0], p[1]);

    ClosePoly();

    if (style->fill_type != PLOT_OP_TYPE_NONE) {
        RGBColor fillColor = color_to_rgb(style->fill_colour);
        RGBForeColor(&fillColor);
        PaintPoly(poly);
    }

    if (style->stroke_type != PLOT_OP_TYPE_NONE) {
        RGBColor strokeColor = color_to_rgb(style->stroke_colour);
        RGBForeColor(&strokeColor);
        PenSize(style->stroke_width, style->stroke_width);
        FramePoly(poly);
    }

    KillPoly(poly);
    return true;
}

bool macos9_plot_path(const struct redraw_context *ctx, const plot_style_t *pstyle,
                     const float *p, unsigned int n, const float transform[6])
{
    if (n < 2) return false;

    int *points = malloc(n * sizeof(int));
    if (points == NULL) return false;

    for (unsigned int i = 0; i < n; i++) {
        points[i] = (int)p[i];
    }

    bool result = macos9_plot_polygon(ctx, pstyle, points, n / 2);
    free(points);

    return result;
}

bool macos9_plot_bitmap(const struct redraw_context *ctx, struct bitmap *bitmap,
                       int x, int y, int width, int height,
                       colour bg, bitmap_flags_t flags)
{
    if (bitmap == NULL) return false;

    struct bitmap *bmp = (struct bitmap *)bitmap;
    if (bmp->gworld == NULL) return false;

    Rect srcRect, dstRect;

    SetRect(&srcRect, 0, 0, bmp->width, bmp->height);
    SetRect(&dstRect, x, y, x + width, y + height);

    GWorldPtr oldWorld;
    GDHandle oldDevice;
    GetGWorld(&oldWorld, &oldDevice);

    CopyBits(GetPortBitMapForCopyBits(bmp->gworld),
             GetPortBitMapForCopyBits(GetWindowPort(FrontWindow())),
             &srcRect, &dstRect, srcCopy, NULL);

    SetGWorld(oldWorld, oldDevice);

    return true;
}

bool macos9_plot_text(const struct redraw_context *ctx, const plot_font_style_t *fstyle,
                     int x, int y, const char *text, size_t length)
{
    if (text == NULL || length == 0) return false;

    RGBColor textColor = color_to_rgb(fstyle->foreground);
    RGBForeColor(&textColor);

    short fontNum;
    GetFNum("\pGeneva", &fontNum);
    TextFont(fontNum);
    TextSize(fstyle->size / FONT_SIZE_SCALE);

    short style = normal;
    if (fstyle->weight >= 700) style |= bold;
    if (fstyle->flags & FONTF_ITALIC) style |= italic;
    TextFace(style);

    MoveTo(x, y);

    char *macText = malloc(length + 1);
    if (macText == NULL) return false;

    memcpy(macText, text, length);
    macText[length] = '\0';

    DrawText(macText, 0, length);

    free(macText);
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
