#include "macos9_gui.h"
#include "utils/utils.h"
#include "utils/nsoption.h"
#include "utils/filepath.h"
#include "utils/file.h"
#include "netsurf/netsurf.h"
#include "netsurf/misc.h"
#include "netsurf/content.h"
#include "netsurf/fetch.h"
#include "netsurf/url_db.h"
#include "content/backing_store.h"

static bool application_running = true;
static struct gui_window *window_list = NULL;

static struct netsurf_table macos9_table = {
    .misc = &macos9_misc_table,
    .window = &macos9_window_table,
    .clipboard = &macos9_clipboard_table,
    .download = &macos9_download_table,
    .fetch = &macos9_fetch_table,
    .file = &macos9_file_table,
    .utf8 = &macos9_utf8_table,
    .search = &macos9_search_table,
    .llcache = &macos9_llcache_table,
    .bitmap = &macos9_bitmap_table,
    .layout = &macos9_layout_table,
};

int main(void)
{
    OSErr err;
    nserror ret;

    InitGraf(&qd.thePort);
    InitFonts();
    InitWindows();
    InitMenus();
    TEInit();
    InitDialogs(NULL);
    InitCursor();

    long response;
    err = Gestalt(gestaltSystemVersion, &response);
    if (err != noErr || response < 0x0900) {
        SysBeep(30);
        return -1;
    }

    err = InitializeApplication();
    if (err != noErr) {
        return -1;
    }

    ret = netsurf_register(&macos9_table);
    if (ret != NSERROR_OK) {
        return -1;
    }

    nsoption_set_bool(enable_javascript, false);
    nsoption_set_int(memory_cache_size, 2 * 1024 * 1024);
    nsoption_set_int(disc_cache_size, 10 * 1024 * 1024);
    nsoption_set_charp(homepage_url, strdup("http://www.netsurf-browser.org/"));

    ret = netsurf_init(NULL);
    if (ret != NSERROR_OK) {
        return -1;
    }

    struct browser_window *bw;
    ret = browser_window_create(BW_CREATE_HISTORY, 
                               nsoption_charp(homepage_url), 
                               NULL, NULL, &bw);
    if (ret != NSERROR_OK) {
        netsurf_exit();
        return -1;
    }

    RunEventLoop();

    netsurf_exit();
    return 0;
}

OSErr InitializeApplication(void)
{
    Handle menuBar;
    MenuRef menu;
    OSErr err;

    menuBar = GetNewMBar(128);
    if (menuBar == NULL) {
        return resNotFound;
    }

    SetMenuBar(menuBar);
    DisposeHandle(menuBar);

    menu = GetMenuRef(MENU_APPLE);
    if (menu != NULL) {
        AppendResMenu(menu, 'DRVR');
    }

    DrawMenuBar();

    return noErr;
}

void RunEventLoop(void)
{
    EventRecord event;

    while (application_running) {
        if (WaitNextEvent(everyEvent, &event, 30, NULL)) {
            HandleEvent(&event);
        }

        netsurf_poll(false);

        struct gui_window *g = window_list;
        while (g != NULL) {
            if (g->redraw_pending) {
                gui_window_redraw_window(g);
                g->redraw_pending = false;
            }
            g = g->next;
        }
    }
}

void HandleEvent(EventRecord *event)
{
    switch (event->what) {
        case mouseDown:
            HandleMouseDown(event);
            break;

        case keyDown:
        case autoKey:
            HandleKeyDown(event);
            break;

        case updateEvt:
            HandleUpdate(event);
            break;

        case diskEvt:
            break;

        case activateEvt:
            break;

        case osEvt:
            break;
    }
}

void HandleMouseDown(EventRecord *event)
{
    WindowPtr window;
    short part;
    long menuChoice;

    part = FindWindow(event->where, &window);

    switch (part) {
        case inMenuBar:
            menuChoice = MenuSelect(event->where);
            HandleMenuChoice(menuChoice);
            break;

        case inSysWindow:
            SystemClick(event, window);
            break;

        case inContent:
            if (window != FrontWindow()) {
                SelectWindow(window);
            } else {
                struct gui_window *g = (struct gui_window *)GetWRefCon(window);
                if (g != NULL) {
                    Point localPoint = event->where;
                    GlobalToLocal(&localPoint);
                    int x = localPoint.h + g->scroll_x;
                    int y = localPoint.v + g->scroll_y;
                    browser_window_mouse_click(g->bw, BROWSER_MOUSE_PRESS_1, x, y);
                }
            }
            break;

        case inDrag:
            DragWindow(window, event->where, &qd.screenBits.bounds);
            break;

        case inGrow:
            {
                Rect sizeRect = {WINDOW_MIN_HEIGHT, WINDOW_MIN_WIDTH, 
                               qd.screenBits.bounds.bottom, 
                               qd.screenBits.bounds.right};
                long newSize = GrowWindow(window, event->where, &sizeRect);
                if (newSize != 0) {
                    SizeWindow(window, LoWord(newSize), HiWord(newSize), true);

                    struct gui_window *g = (struct gui_window *)GetWRefCon(window);
                    if (g != NULL) {
                        gui_window_get_dimensions(g, &g->width, &g->height);
                        browser_window_reformat(g->bw, false, g->width, g->height);
                    }
                }
            }
            break;

        case inGoAway:
            if (TrackGoAway(window, event->where)) {
                struct gui_window *g = (struct gui_window *)GetWRefCon(window);
                if (g != NULL) {
                    gui_window_destroy(g);
                }
            }
            break;
    }
}

void HandleKeyDown(EventRecord *event)
{
    char key = event->message & charCodeMask;

    if ((event->modifiers & cmdKey) != 0) {
        long menuChoice = MenuKey(key);
        HandleMenuChoice(menuChoice);
    } else {
        WindowPtr frontWindow = FrontWindow();
        if (frontWindow != NULL) {
            struct gui_window *g = (struct gui_window *)GetWRefCon(frontWindow);
            if (g != NULL) {
                uint32_t nskey = 0;
                switch (key) {
                    case 0x08: nskey = NS_KEY_DELETE_LEFT; break;
                    case 0x7F: nskey = NS_KEY_DELETE_RIGHT; break;
                    case 0x1C: nskey = NS_KEY_LEFT; break;
                    case 0x1D: nskey = NS_KEY_RIGHT; break;
                    case 0x1E: nskey = NS_KEY_UP; break;
                    case 0x1F: nskey = NS_KEY_DOWN; break;
                    case 0x0D: nskey = NS_KEY_NL; break;
                    default: nskey = key; break;
                }

                if (nskey != 0) {
                    browser_window_key_press(g->bw, nskey);
                }
            }
        }
    }
}

void HandleUpdate(EventRecord *event)
{
    WindowPtr window = (WindowPtr)event->message;
    struct gui_window *g = (struct gui_window *)GetWRefCon(window);

    if (g != NULL) {
        BeginUpdate(window);
        gui_window_redraw_window(g);
        EndUpdate(window);
    }
}

void HandleMenuChoice(long menuChoice)
{
    short menu = HiWord(menuChoice);
    short item = LoWord(menuChoice);
    Str255 itemName;

    switch (menu) {
        case MENU_APPLE:
            if (item == ITEM_ABOUT) {
                Alert(DIALOG_ABOUT, NULL);
            } else {
                GetMenuItemText(GetMenuRef(MENU_APPLE), item, itemName);
                OpenDeskAcc(itemName);
            }
            break;

        case MENU_FILE:
            switch (item) {
                case ITEM_NEW:
                    {
                        struct browser_window *bw;
                        browser_window_create(BW_CREATE_HISTORY,
                                            nsoption_charp(homepage_url),
                                            NULL, NULL, &bw);
                    }
                    break;

                case ITEM_QUIT:
                    application_running = false;
                    break;
            }
            break;
    }

    HiliteMenu(0);
}
