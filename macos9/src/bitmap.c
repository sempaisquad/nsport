#include "macos9_gui.h"

void *bitmap_create(int width, int height, unsigned int state)
{
    struct bitmap *bmp = calloc(1, sizeof(struct bitmap));
    if (bmp == NULL) return NULL;
    bmp->width = width;
    bmp->height = height;
    bmp->opaque = (state & BITMAP_OPAQUE) != 0;
    return bmp;
}

void bitmap_destroy(void *bitmap)
{
    free(bitmap);
}

void bitmap_set_opaque(void *bitmap, bool opaque)
{
    struct bitmap *bmp = bitmap;
    if (bmp) bmp->opaque = opaque;
}

bool bitmap_test_opaque(void *bitmap)
{
    struct bitmap *bmp = bitmap;
    return bmp ? bmp->opaque : false;
}

bool bitmap_get_opaque(void *bitmap)
{
    struct bitmap *bmp = bitmap;
    return bmp ? bmp->opaque : false;
}

unsigned char *bitmap_get_buffer(void *bitmap)
{
    return NULL;
}

size_t bitmap_get_rowstride(void *bitmap)
{
    return 0;
}

size_t bitmap_get_bpp(void *bitmap)
{
    return 4;
}

bool bitmap_save(void *bitmap, const char *path, unsigned flags)
{
    (void)bitmap; (void)path; (void)flags;
    return false;
}

void bitmap_modified(void *bitmap)
{
    (void)bitmap;
}

void bitmap_set_suspendable(void *bitmap, void *private_word,
                           void (*invalidate)(void *private_word))
{
    (void)bitmap; (void)private_word; (void)invalidate;
}

struct gui_bitmap_table macos9_bitmap_table = {
    .create = bitmap_create,
    .destroy = bitmap_destroy,
    .set_opaque = bitmap_set_opaque,
    .get_opaque = bitmap_get_opaque,
    .test_opaque = bitmap_test_opaque,
    .get_buffer = bitmap_get_buffer,
    .get_rowstride = bitmap_get_rowstride,
    .get_bpp = bitmap_get_bpp,
    .save = bitmap_save,
    .modified = bitmap_modified,
    .render = NULL,
};
