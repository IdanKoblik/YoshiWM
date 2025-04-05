#ifndef _CONFIG_
#define _CONFIG_

#include "toml.h"
#include <string.h>

typedef enum {
    SUPER_WINDOW,
    SUPER_ALT
} super;

typedef enum {
    ACTION_RELOAD,
    ACTION_EXIT
} windowAction;

typedef struct {
    char *wallpaperPath;
    super superKey;
} general;

typedef struct {
    char *shortcut;
    char *command;
} execShortcut;

typedef struct {
    char *shortcut;
    windowAction action;
} windowShortcut;

typedef struct {
    general generalConfig;
    windowShortcut *windowShortcuts;
    size_t windowShortcutsCount;
    execShortcut *execShortcuts;
    size_t execShortcutsCount;
} config;

int loadConfig(config *cfg);
void freeConfig(config *cfg);

#endif // _CONFIG_