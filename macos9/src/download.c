#include "macos9_gui.h"

struct gui_download_window *macos9_download_create(download_context *ctx,
                                                 struct gui_window *gui)
{
    (void)ctx; (void)gui;
    return NULL;
}

static nserror macos9_download_data(struct gui_download_window *dw,
                                   const char *data, unsigned int size)
{
    (void)dw; (void)data; (void)size;
    return NSERROR_NOT_IMPLEMENTED;
}

static void macos9_download_error(struct gui_download_window *dw,
                                 const char *error_msg)
{
    (void)dw; (void)error_msg;
}

static void macos9_download_done(struct gui_download_window *dw)
{
    (void)dw;
}

struct gui_download_table macos9_download_table = {
    .create = macos9_download_create,
    .data = macos9_download_data,
    .error = macos9_download_error,
    .done = macos9_download_done,
};
