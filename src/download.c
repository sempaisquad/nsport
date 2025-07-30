#include "macos9_gui.h"

static struct gui_download_window *macos9_download_create(download_context *ctx,
                                                         struct gui_window *gui)
{
    return NULL;
}

static nserror macos9_download_data(struct gui_download_window *dw,
                                   const char *data, unsigned int size)
{
    return NSERROR_NOT_IMPLEMENTED;
}

static void macos9_download_error(struct gui_download_window *dw,
                                 const char *error_msg)
{
}

static void macos9_download_done(struct gui_download_window *dw)
{
}

struct gui_download_table macos9_download_table = {
    .create = macos9_download_create,
    .data = macos9_download_data,
    .error = macos9_download_error,
    .done = macos9_download_done,
};
