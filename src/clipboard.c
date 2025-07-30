#include "macos9_gui.h"

static void macos9_get_clipboard(char **buffer, size_t *length)
{
    Handle scrapHandle;
    long scrapLength;
    OSErr err;

    scrapLength = GetScrap(NULL, 'TEXT', &scrapHandle);
    if (scrapLength < 0) {
        *buffer = NULL;
        *length = 0;
        return;
    }

    *buffer = malloc(scrapLength + 1);
    if (*buffer == NULL) {
        *length = 0;
        return;
    }

    HLock(scrapHandle);
    memcpy(*buffer, *scrapHandle, scrapLength);
    HUnlock(scrapHandle);

    (*buffer)[scrapLength] = '\0';
    *length = scrapLength;

    DisposeHandle(scrapHandle);
}

static void macos9_set_clipboard(const char *buffer, size_t length,
                                nsclipboard_styles styles[], int n_styles)
{
    ZeroScrap();
    PutScrap(length, 'TEXT', buffer);
}

struct gui_clipboard_table macos9_clipboard_table = {
    .get = macos9_get_clipboard,
    .set = macos9_set_clipboard,
};
