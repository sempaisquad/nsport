#include "macos9_gui.h"

void *bitmap_create(int width, int height, unsigned int state)
{
    struct bitmap *bmp;
    OSErr err;
    Rect bounds;

    bmp = calloc(1, sizeof(struct bitmap));
    if (bmp == NULL) {
        return NULL;
    }

    bmp->width = width;
    bmp->height = height;
    bmp->opaque = (state & BITMAP_OPAQUE) != 0;

    SetRect(&bounds, 0, 0, width, height);
    err = NewGWorld(&bmp->gworld, 32, &bounds, NULL, NULL, 0);
    if (err != noErr) {
        free(bmp);
        return NULL;
    }

    bmp->pixmap = GetGWorldPixMap(bmp->gworld);
    if (bmp->pixmap == NULL) {
        DisposeGWorld(bmp->gworld);
        free(bmp);
        return NULL;
    }

    return bmp;
}

void bitmap_destroy(void *bitmap)
{
    struct bitmap *bmp = (struct bitmap *)bitmap;

    if (bmp == NULL) return;

    if (bmp->gworld != NULL) {
        DisposeGWorld(bmp->gworld);
    }

    free(bmp);
}

void bitmap_set_opaque(void *bitmap, bool opaque)
{
    struct bitmap *bmp = (struct bitmap *)bitmap;

    if (bmp != NULL) {
        bmp->opaque = opaque;
    }
}

bool bitmap_test_opaque(void *bitmap)
{
    struct bitmap *bmp = (struct bitmap *)bitmap;

    if (bmp == NULL) return false;

    if (bmp->pixmap == NULL) return false;

    LockPixels(bmp->pixmap);
    Ptr baseAddr = GetPixBaseAddr(bmp->pixmap);
    short rowBytes = GetPixRowBytes(bmp->pixmap);

    bool opaque = true;
    for (int y = 0; y < bmp->height && opaque; y++) {
        unsigned char *row = (unsigned char *)(baseAddr + y * rowBytes);
        for (int x = 0; x < bmp->width; x++) {
            if (row[x * 4] < 255) {
                opaque = false;
                break;
            }
        }
    }

    UnlockPixels(bmp->pixmap);
    return opaque;
}

bool bitmap_get_opaque(void *bitmap)
{
    struct bitmap *bmp = (struct bitmap *)bitmap;
    return bmp ? bmp->opaque : false;
}

unsigned char *bitmap_get_buffer(void *bitmap)
{
    struct bitmap *bmp = (struct bitmap *)bitmap;

    if (bmp == NULL || bmp->pixmap == NULL) return NULL;

    LockPixels(bmp->pixmap);
    return (unsigned char *)GetPixBaseAddr(bmp->pixmap);
}

size_t bitmap_get_rowstride(void *bitmap)
{
    struct bitmap *bmp = (struct bitmap *)bitmap;

    if (bmp == NULL || bmp->pixmap == NULL) return 0;

    return GetPixRowBytes(bmp->pixmap);
}

size_t bitmap_get_bpp(void *bitmap)
{
    return 4;
}

bool bitmap_save(void *bitmap, const char *path, unsigned flags)
{
    return false;
}

void bitmap_modified(void *bitmap)
{
    struct bitmap *bmp = (struct bitmap *)bitmap;

    if (bmp != NULL && bmp->pixmap != NULL) {
        UnlockPixels(bmp->pixmap);
    }
}

void bitmap_set_suspendable(void *bitmap, void *private_word,
                           void (*invalidate)(void *private_word))
{
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
