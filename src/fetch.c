#include "macos9_gui.h"
#include "utils/ring.h"
#include "content/fetchers.h"
#include "content/fetchers/curl.h"

struct macos9_fetch_context {
    struct fetch *fetch_handle;
    char *url;
    char *referer;
    lwc_string *scheme;
    bool aborted;
    bool finished;
};

static RING(macos9_fetch_context, macos9_fetch_ring);

static bool macos9_fetch_initialise(const char *scheme)
{
    return true;
}

static void macos9_fetch_finalise(const char *scheme)
{
}

static bool macos9_fetch_can_fetch(const nsurl *url)
{
    lwc_string *scheme = nsurl_get_component(url, NSURL_SCHEME);
    bool can_fetch = false;

    if (scheme != NULL) {
        if (lwc_string_caseless_isequal(scheme, corestring_lwc_http,
                                       &can_fetch) != lwc_error_ok) {
            can_fetch = false;
        }

        if (!can_fetch &&
            lwc_string_caseless_isequal(scheme, corestring_lwc_https,
                                       &can_fetch) != lwc_error_ok) {
            can_fetch = false;
        }

        lwc_string_unref(scheme);
    }

    return can_fetch;
}

static void *macos9_fetch_setup(struct fetch *parent_fetch, nsurl *url,
                               bool only_2xx, bool downgrade_tls,
                               const char *post_urlenc,
                               const struct fetch_multipart_data *post_multipart,
                               const char **headers)
{
    struct macos9_fetch_context *ctx;

    ctx = calloc(1, sizeof(struct macos9_fetch_context));
    if (ctx == NULL) {
        return NULL;
    }

    ctx->fetch_handle = parent_fetch;
    ctx->url = strdup(nsurl_access(url));
    ctx->aborted = false;
    ctx->finished = false;

    RING_INSERT(macos9_fetch_ring, ctx);

    return ctx;
}

static bool macos9_fetch_start(void *handle)
{
    struct macos9_fetch_context *ctx = (struct macos9_fetch_context *)handle;

    if (ctx == NULL) return false;

    const char *html = "<html><head><title>NetSurf for Mac OS 9</title></head>"
                      "<body><h1>Welcome to NetSurf</h1>"
                      "<p>This is a basic HTML page served by the Mac OS 9 port.</p>"
                      "<p>URL: %s</p></body></html>";

    char *content = malloc(strlen(html) + strlen(ctx->url) + 1);
    if (content != NULL) {
        sprintf(content, html, ctx->url);

        fetch_msg msg;
        msg.type = FETCH_HEADER;
        msg.data.header_or_data.buf = (const uint8_t *)"Content-Type: text/html";
        msg.data.header_or_data.len = strlen((char *)msg.data.header_or_data.buf);
        fetch_send_callback(&msg, ctx->fetch_handle);

        msg.type = FETCH_DATA;
        msg.data.header_or_data.buf = (const uint8_t *)content;
        msg.data.header_or_data.len = strlen(content);
        fetch_send_callback(&msg, ctx->fetch_handle);

        msg.type = FETCH_FINISHED;
        fetch_send_callback(&msg, ctx->fetch_handle);

        free(content);
        ctx->finished = true;
    }

    return true;
}

static void macos9_fetch_abort(void *handle)
{
    struct macos9_fetch_context *ctx = (struct macos9_fetch_context *)handle;

    if (ctx != NULL) {
        ctx->aborted = true;
    }
}

static void macos9_fetch_free(void *handle)
{
    struct macos9_fetch_context *ctx = (struct macos9_fetch_context *)handle;

    if (ctx == NULL) return;

    RING_REMOVE(macos9_fetch_ring, ctx);

    if (ctx->url != NULL) {
        free(ctx->url);
    }
    if (ctx->referer != NULL) {
        free(ctx->referer);
    }

    free(ctx);
}

static void macos9_fetch_poll(lwc_string *scheme)
{
    struct macos9_fetch_context *ctx = macos9_fetch_ring;

    if (ctx != NULL) {
        do {
            if (!ctx->finished && !ctx->aborted) {
            }
            ctx = ctx->r_next;
        } while (ctx != macos9_fetch_ring);
    }
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
