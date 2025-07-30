#include "macos9_gui.h"

static void macos9_warning(const char *warning, const char *detail)
{
    (void)warning; (void)detail;
}

static nserror macos9_login(nsurl *url, const char *realm,
                           const char *username, const char *password,
                           nserror (*cb)(nserror, nsurl *, const char *,
                                       const char *, void *),
                           void *cbpw)
{
    (void)url; (void)realm; (void)username; (void)password; (void)cb; (void)cbpw;
    return NSERROR_NOT_IMPLEMENTED;
}

static nserror macos9_pdf_password(const char **owner_pass, const char **user_pass,
                                  const char *path)
{
    (void)owner_pass; (void)user_pass; (void)path;
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
