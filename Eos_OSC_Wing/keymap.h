#ifndef KEYMAP_H
#define KEYMAP_H

// 8 Rows x 16 Columns
// Rows 1-8 corresponds to indices 0-7
// Cols 9-24 corresponds to indices 0-15

const char* KEYMAP[8][16] = {
    // Row 1 (Cols 9-24)
    {
        "/eos/key/RELEASE_FADER",   // 9: Release
        "/eos/key/SPREAD",          // 10: Spread
        "/eos/key/DISPLAYS",        // 11: Displays
        "/eos/key/ADDRESS",         // 12: Address
        "/eos/key/ENCODER_DISPLAY", // 13: Encoder Display
        "/eos/key/INTENSITY",       // 14: Intensity
        "/eos/key/FOCUS_CAT",       // 15: Focus
        "/eos/key/COLOR_CAT",       // 16: Color
        "/eos/key/SHUTTER_CAT",     // 17: Shutter
        "/eos/key/IMAGE_CAT",       // 18: Image
        "/eos/key/FORM_CAT",        // 19: Form
        "/eos/key/LIVE",            // 20: Live
        "/eos/key/PREVIEW",         // 21: Blind
        "/eos/key/STAGING_MODE",    // 22: Stage
        "/eos/key/MACRO_801",       // 23: M801
        "/eos/key/MACRO_802"        // 24: M802
    },
    // Row 2
    {
        "/eos/key/BUMP_OFF",        // 9: Off
        "/eos/key/ASSERT",          // 10: Assert
        "/eos/key/MACRO",           // 11: Macro
        "/eos/key/HELP",            // 12: Help
        "/eos/key/LEARN",           // 13: Learn
        "/eos/key/QUERY",           // 14: Query
        "/eos/key/COPY_TO",         // 15: Copy to
        "/eos/key/RECALL_FROM",     // 16: Recall
        "/eos/key/LABEL",           // 17: Label
        NULL,                       // 18: Empty
        "/eos/key/ABOUT",           // 19: About
        "/eos/key/ESCAPE",          // 20: Escape
        "/eos/key/PAGE_UP",         // 21: Page up
        "/eos/key/SELECT",          // 22: Select
        "/eos/key/MACRO_803",       // 23: M803
        "/eos/key/MACRO_804"        // 24: M804
    },
    // Row 3
    {
        "/eos/key/GO_TO_CUE_ZERO",  // 9: GoToCue 0
        "/eos/key/STOP_EFFECT",     // 10: Stop Effect
        "/eos/key/DELETE",          // 11: Delete
        "/eos/key/COLOR_PATH",      // 12: Path
        "/eos/key/EFFECT",          // 13: Effect
        "/eos/key/GO_TO_CUE",       // 14: Go To Q
        "/eos/key/BLOCK",           // 15: Block
        "/eos/key/ASSERT",          // 16: Assert
        "/eos/key/UNDO",            // 17: Undo
        "/eos/key/HIGHLIGHT",       // 18: High
        "/eos/key/FAN",             // 19: Fan
        "/eos/key/PAGE_LEFT",       // 20: Page L
        "/eos/key/PAGE_DOWN",       // 21: Page Dwn
        "/eos/key/PAGE_RIGHT",      // 22: Page R
        "/eos/key/MACRO_805",       // 23: M805
        "/eos/key/MACRO_806"        // 24: M806
    },
    // Row 4
    {
        "/eos/key/PLAYBACK_FREEZE", // 9: Freeze
        "/eos/key/FILTER",          // 10: Filter
        "/eos/key/PART",            // 11: Part
        "/eos/key/CUE",             // 12: cue
        "/eos/key/RECORD",          // 13: record
        "/eos/key/PLUS",            // 14: +
        "/eos/key/THRU",            // 15: Thru
        "/eos/key/MINUS",           // 16: -
        "/eos/key/SLASH",           // 17: /
        "/eos/key/MARK",            // 18: Mark
        "/eos/key/SNEAK",           // 19: Sneak
        "/eos/key/SHEET",           // 20: Tab
        "/eos/key/FLEXI_PARTITION_TOGGLE", // 21: Flexi
        "/eos/key/TIME",            // 22: Time
        "/eos/key/MACRO_807",       // 23: M807
        "/eos/key/MACRO_808"        // 24: M808
    },
    // Row 5
    {
        "/eos/key/MANUAL_OVERRIDE", // 9: Man override
        "/eos/key/TIMING_DISABLE",  // 10: Timing Dis
        "/eos/key/INTENSITY_PALETTE", // 11: Intensity Palette
        "/eos/key/FOCUS_PALETTE",   // 12: Focus Palette
        "/eos/key/RECORD_ONLY",     // 13: Rec only
        "/eos/key/7",               // 14: 7
        "/eos/key/8",               // 15: 8
        "/eos/key/9",               // 16: 9
        "/eos/key/REM_DIM",         // 17: Rem Dim
        "/eos/key/PLUS10",          // 18: +%
        "/eos/key/HOME",            // 19: Home
        "/eos/key/FORMAT",          // 20: Format
        "/eos/key/EXPAND",          // 21: Expand
        "/eos/key/DATA",            // 22: Data
        "/eos/key/MACRO_809",       // 23: M809
        "/eos/key/MACRO_810"        // 24: M810
    },
    // Row 6
    {
        "/eos/key/RATE",            // 9: Rate
        "/eos/key/FADER_PAGES",     // 10: Fader Pg
        "/eos/key/COLOR_PALETTE",   // 11: Color Palette
        "/eos/key/BEAM_PALETTE",    // 12: Beam Palette
        "/eos/key/UPDATE",          // 13: update
        "/eos/key/4",               // 14: 4
        "/eos/key/5",               // 15: 5
        "/eos/key/6",               // 16: 6
        "/eos/key/OUT",             // 17: Out
        "/eos/key/MINUS10",         // 18: -%
        "/eos/key/TRACE",           // 19: Trace
        "/eos/key/PARK",            // 20: Park
        "/eos/key/SELECT_MANUAL",   // 21: Select Manual
        "/eos/key/OPEN_ML_CONTROLS",// 22: ML Con
        NULL,                       // 23: Empty
        NULL                        // 24: Empty
    },
    // Row 7
    {
        "/eos/key/SNAPSHOT",        // 9: Snapshot
        "/eos/key/LOAD_PLAYBACK",   // 10: Load
        "/eos/key/PRESET",          // 11: preset
        "/eos/key/SUBMASTER",       // 12: Sub
        "/eos/key/GROUP",           // 13: Group
        "/eos/key/1",               // 14: 1
        "/eos/key/2",               // 15: 2
        "/eos/key/3",               // 16: 3
        "/eos/key/FULL",            // 17: Full
        "/eos/key/LEVEL",           // 18: Level
        "/eos/key/Q_ONLY",          // 19: Q only
        "/eos/key/CAPTURE",         // 20: Capture
        "/eos/key/SELECT_ACTIVE",   // 21: Select active
        NULL,                       // 22: Empty
        NULL,                       // 23: Empty
        "/eos/key/BACK"             // 24: Back
    },
    // Row 8
    {
        NULL,                       // 9: Empty
        "/eos/key/BLACKOUT",        // 10: Blackout
        "/eos/key/SHIFT",           // 11: Shift
        "/eos/key/DELAY",           // 12: Delay
        "/eos/key/TIME",            // 13: Time
        "/eos/key/CLEAR",           // 14: Clear
        "/eos/key/0",               // 15: 0
        "/eos/key/POINT",           // 16: .
        "/eos/key/AT",              // 17: At
        "/eos/key/ENTER",           // 18: Enter
        NULL,                       // 19: Empty
        "/eos/key/SELECT_LAST",     // 20: Select Last
        "/eos/key/LAST",            // 21: Last
        "/eos/key/NEXT",            // 22: Next
        NULL,                       // 23: Empty
        "/eos/key/GO"               // 24: Go
    }
};

#endif
