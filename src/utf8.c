#include "macos9_gui.h"

static nserror macos9_utf8_to_local(const char *string, size_t len,
                                    char **result)
{
    char *converted = malloc(len + 1);
    if (converted == NULL) {
        return NSERROR_NOMEM;
    }

    memcpy(converted, string, len);
    converted[len] = '\0';

    *result = converted;
    return NSERROR_OK;
}

static nserror macos9_local_to_utf8(const char *string, size_t len,
                                    char **result)
{
    char *converted = malloc(len + 1);
    if (converted == NULL) {
        return NSERROR_NOMEM;
    }

    memcpy(converted, string, len);
    converted[len] = '\0';

    *result = converted;
    return NSERROR_OK;
}

struct gui_utf8_table macos9_utf8_table = {
    .utf8_to_local = macos9_utf8_to_local,
    .local_to_utf8 = macos9_local_to_utf8,
};
