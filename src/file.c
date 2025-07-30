#include "macos9_gui.h"

static nserror macos9_file_mkpath(const char *path)
{
    return NSERROR_OK;
}

struct gui_file_table macos9_file_table = {
    .mkpath = macos9_file_mkpath,
};
