/*
 * NetSurf Mac OS 9 Resources
 * Compile with: Rez -o NetSurf NetSurf.r
 */

#include "Types.r"
#include "MacTypes.r"

type 'BNDL' {
    integer = 0;
    array TypeArray {
        literal longint;
        integer;
        array IDArray {
            integer;
            integer;
        };
    };
};

resource 'BNDL' (128, "NetSurf Bundle") {
    {
        'FREF', 0, {
            0, 128
        },
        'ICN#', 0, {
            0, 128
        }
    }
};

resource 'FREF' (128, "Application") {
    'APPL', 0, ""
};

resource 'vers' (1, "Version") {
    0x03, 0x11, final, 0x00, verUS,
    "3.11",
    "NetSurf 3.11, Copyright © 2025 The NetSurf Developers"
};

resource 'vers' (2, "Get Info Version") {
    0x03, 0x11, final, 0x00, verUS,
    "3.11",
    "NetSurf web browser for Mac OS 9"
};

resource 'ICN#' (128, "NetSurf Icon") {
    {
        "$""00 00 00 00 00 00 00 00 00 1F F8 00 00 7F FE 00"
        "$""01 FF FF 80 03 FF FF C0 07 FF FF E0 0F FF FF F0"
        "$""1F E0 07 F8 3F C0 03 FC 7F 80 01 FE FF 00 00 FF"
        "$""FF 00 00 FF FF 00 00 FF FF 00 00 FF FF 00 00 FF"
        "$""FF 80 01 FF 7F C0 03 FE 3F E0 07 FC 1F F0 0F F8"
        "$""0F F8 1F F0 07 FC 3F E0 03 FE 7F C0 01 FF FF 80"
        "$""00 FF FF 00 00 7F FE 00 00 3F FC 00 00 1F F8 00"
        "$""00 0F F0 00 00 07 E0 00 00 03 C0 00 00 00 00 00",
        
        "$""00 00 00 00 00 00 00 00 00 1F F8 00 00 7F FE 00"
        "$""01 FF FF 80 03 FF FF C0 07 FF FF E0 0F FF FF F0"
        "$""1F E0 07 F8 3F C0 03 FC 7F 80 01 FE FF 00 00 FF"
        "$""FF 00 00 FF FF 00 00 FF FF 00 00 FF FF 00 00 FF"
        "$""FF 80 01 FF 7F C0 03 FE 3F E0 07 FC 1F F0 0F F8"
        "$""0F F8 1F F0 07 FC 3F E0 03 FE 7F C0 01 FF FF 80"
        "$""00 FF FF 00 00 7F FE 00 00 3F FC 00 00 1F F8 00"
        "$""00 0F F0 00 00 07 E0 00 00 03 C0 00 00 00 00 00"
    }
};

resource 'ics#' (128, "Small NetSurf Icon") {
    {
        "$""01 F8 07 FE 0F FF 1F FF 3F 0F 7E 07 FC 03 FC 03"
        "$""FC 03 FC 03 FE 07 7F 0F 3F 9F 1F FF 0F FE 07 FC"
        "$""03 F8 01 F0 00 E0 00 C0 00 80 00 00 00 00 00 00",
        
        "$""01 F8 07 FE 0F FF 1F FF 3F 0F 7E 07 FC 03 FC 03"
        "$""FC 03 FC 03 FE 07 7F 0F 3F 9F 1F FF 0F FE 07 FC"
        "$""03 F8 01 F0 00 E0 00 C0 00 80 00 00 00 00 00 00"
    }
};

resource 'MBAR' (128, "Menu Bar") {
    { 128, 129, 130, 131, 132 }
};

resource 'MENU' (128, "Apple Menu") {
    128, textMenuProc, allEnabled, enabled, apple,
    {
        "About NetSurf…", noIcon, noKey, noMark, plain;
        "-", noIcon, noKey, noMark, plain
    }
};

resource 'MENU' (129, "File Menu") {
    129, textMenuProc, allEnabled, enabled, "File",
    {
        "New Window", noIcon, "N", noMark, plain;
        "Open Location…", noIcon, "L", noMark, plain;
        "-", noIcon, noKey, noMark, plain;
        "Close Window", noIcon, "W", noMark, plain;
        "-", noIcon, noKey, noMark, plain;
        "Save Page As…", noIcon, "S", noMark, plain;
        "-", noIcon, noKey, noMark, plain;
        "Page Setup…", noIcon, noKey, noMark, plain;
        "Print…", noIcon, "P", noMark, plain;
        "-", noIcon, noKey, noMark, plain;
        "Quit", noIcon, "Q", noMark, plain
    }
};

resource 'MENU' (130, "Edit Menu") {
    130, textMenuProc, allEnabled, enabled, "Edit",
    {
        "Undo", noIcon, "Z", noMark, plain;
        "-", noIcon, noKey, noMark, plain;
        "Cut", noIcon, "X", noMark, plain;
        "Copy", noIcon, "C", noMark, plain;
        "Paste", noIcon, "V", noMark, plain;
        "Clear", noIcon, noKey, noMark, plain;
        "Select All", noIcon, "A", noMark, plain;
        "-", noIcon, noKey, noMark, plain;
        "Find…", noIcon, "F", noMark, plain;
        "Find Again", noIcon, "G", noMark, plain
    }
};

resource 'MENU' (131, "View Menu") {
    131, textMenuProc, allEnabled, enabled, "View",
    {
        "Reload", noIcon, "R", noMark, plain;
        "Stop", noIcon, ".", noMark, plain;
        "-", noIcon, noKey, noMark, plain;
        "Scale View", noIcon, noKey, noMark, plain;
        "-", noIcon, noKey, noMark, plain;
        "View Source", noIcon, "U", noMark, plain;
        "Local History", noIcon, "H", noMark, plain
    }
};

resource 'MENU' (132, "Go Menu") {
    132, textMenuProc, allEnabled, enabled, "Go",
    {
        "Back", noIcon, leftArrowKey, noMark, plain;
        "Forward", noIcon, rightArrowKey, noMark, plain;
        "Home", noIcon, "1", noMark, plain;
        "-", noIcon, noKey, noMark, plain;
        "Bookmarks", noIcon, "B", noMark, plain
    }
};

resource 'DLOG' (128, "About NetSurf") {
    {100, 150, 300, 450},
    dBoxProc,
    visible,
    noGoAway,
    0,
    128,
    "About NetSurf",
    centerMainScreen
};

resource 'DITL' (128, "About NetSurf Items") {
    {
        {170, 220, 190, 280},
        Button {
            enabled,
            "OK"
        };
        
        {10, 10, 42, 42},
        Icon {
            disabled,
            128
        };
        
        {10, 50, 30, 290},
        StaticText {
            disabled,
            "NetSurf Web Browser"
        };
        
        {35, 50, 55, 290},
        StaticText {
            disabled,
            "Version 3.11 for Mac OS 9"
        };
        
        {70, 10, 90, 290},
        StaticText {
            disabled,
            "A lightweight web browser"
        };
        
        {95, 10, 115, 290},
        StaticText {
            disabled,
            "Copyright © 2025 The NetSurf Developers"
        };
        
        {130, 10, 150, 290},
        StaticText {
            disabled,
            "Built with Retro68 for Mac OS 9"
        }
    }
};

resource 'ALRT' (129, "Error Alert") {
    {100, 100, 200, 400},
    129,
    {
        OK, visible, sound1,
        OK, visible, sound1,
        OK, visible, sound1,
        OK, visible, sound1
    },
    centerMainScreen
};

resource 'DITL' (129, "Error Alert Items") {
    {
        {70, 250, 90, 310},
        Button {
            enabled,
            "OK"
        };
        
        {10, 10, 42, 42},
        Icon {
            disabled,
            0
        };
        
        {10, 50, 60, 290},
        StaticText {
            disabled,
            "An error has occurred: ^0"
        }
    }
};

resource 'SIZE' (-1) {
    reserved,
    acceptSuspendResumeEvents,
    reserved,
    canBackground,
    doesActivateOnFGSwitch,
    backgroundAndForeground,
    dontGetFrontClicks,
    ignoreChildDiedEvents,
    is32BitCompatible,
    isHighLevelEventAware,
    onlyLocalHLEvents,
    notStationeryAware,
    dontUseTextEditServices,
    reserved,
    reserved,
    reserved,
    2097152,
    1048576
};
