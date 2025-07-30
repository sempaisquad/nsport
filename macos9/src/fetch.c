#include "macos9_gui.h"
#include "utils/ring.h"

struct macos9_fetch_context {
    struct fetch *fetch_handle;
    char *url;
    bool aborted;
};

static bool macos9_fetch_initialise(const char *scheme)
{
    return true;
}

static void macos9_fetch_finalise(const char *scheme)
{
    (void)scheme;
}

static bool macos9_fetch_can_fetch(const nsurl *url)
{
    (void)url;
    return true;
}

static void *macos9_fetch_setup(struct fetch *parent, nsurl *url,
                               bool only_2xx, bool downgrade_tls,
                               const char *post_urlenc,
                               const struct fetch_multipart_data *post_multipart,
                               const char **headers)
{
    struct macos9_fetch_context *ctx = calloc(1, sizeof(*ctx));
    if (!ctx) return NULL;
    ctx->fetch_handle = parent;
    ctx->url = strdup(nsurl_access(url));
    return ctx;
}

static bool macos9_fetch_start(void *handle)
{
    struct macos9_fetch_context *ctx = handle;
    if (!ctx) return false;

    fetch_msg msg;
    const char *html = "<html><body>Mac OS 9 stub fetch</body></html>";

    msg.type = FETCH_HEADER;
    msg.data.header_or_data.buf = (const uint8_t *)"Content-Type: text/html";
    msg.data.header_or_data.len = strlen((char *)msg.data.header_or_data.buf);
    fetch_send_callback(&msg, ctx->fetch_handle);

    msg.type = FETCH_DATA;
    msg.data.header_or_data.buf = (const uint8_t *)html;
    msg.data.header_or_data.len = strlen(html);
    fetch_send_callback(&msg, ctx->fetch_handle);

    msg.type = FETCH_FINISHED;
    fetch_send_callback(&msg, ctx->fetch_handle);

    return true;
}

static void macos9_fetch_abort(void *handle)
{
    struct macos9_fetch_context *ctx = handle;
    if (ctx) ctx->aborted = true;
}

static void macos9_fetch_free(void *handle)
{
    struct macos9_fetch_context *ctx = handle;
    if (!ctx) return;
    free(ctx->url);
    free(ctx);
}

static void macos9_fetch_poll(lwc_string *scheme)
{
    (void)scheme;
}

static const struct fetcher_operation_table macos9_fetcher_ops = {
    .initialise = macos9_fetch_initialise,
    .acceptable = macos9_fetch_can_fetch,
    .setup = macos9_fetch_setup,
    .start = macos9_fetch_start,
    .abort = macos9_fetch_abort,
    .free = macos9_fetch_free,
    .poll = macos9_fetch_poll,
    .finalise = macos9_fetch_finalise
};

nserror macos9_fetcher_register(void)
{
    return fetcher_add("http", &macos9_fetcher_ops);
}

struct gui_fetch_table macos9_fetch_table = {
    .filetype = NULL,
    .get_resource_url = NULL,
    .get_resource_data = NULL,
    .release_resource_data = NULL,
    .mimetype = NULL,
};
