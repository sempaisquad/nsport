#include "macos9_gui.h"

static void macos9_warning(const char *warning, const char *detail)
{
    char message[512];
    snprintf(message, sizeof(message), "Warning: %s\n%s", warning, detail ? detail : "");

    Str255 pmessage;
    int len = strlen(message);
    if (len > 255) len = 255;
    pmessage[0] = len;
    memcpy(&pmessage[1], message, len);

    ParamText(pmessage, NULL, NULL, NULL);
    Alert(ALERT_ERROR, NULL);
}

static nserror macos9_login(nsurl *url, const char *realm,
                           const char *username, const char *password,
                           nserror (*cb)(nserror, nsurl *, const char *,
                                       const char *, void *),
                           void *cbpw)
{
    return NSERROR_NOT_IMPLEMENTED;
}

static nserror macos9_pdf_password(const char **owner_pass, const char **user_pass,
                                  const char *path)
{
    return NSERROR_NOT_IMPLEMENTED;
}

struct gui_misc_table macos9_misc_table = {
    .schedule = macos9_schedule,
    .warning = macos9_warning,
    .login = macos9_login,
    .pdf_password = macos9_pdf_password,
    .quit = macos9_quit,
    .present_cookies = NULL,
};
