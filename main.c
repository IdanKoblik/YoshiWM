#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/cursorfont.h>
#include "event.h"
#include "toml.h"
#include "config.h"
#include "window.h"

int main(void) {
    Display *display;
    XEvent event;
    Window root;

    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Error occurred while trying to open a display\n");
        exit(1);
    }

    printf("Display opened successfully.\n");

    root = DefaultRootWindow(display);
    XSelectInput(display, DefaultRootWindow(display), KeyPressMask | ButtonPressMask);
    XSync(display, 0);

    Cursor cursor = XCreateFontCursor(display, XC_left_ptr);
    XDefineCursor(display, root, cursor);
    XSync(display, False);

    config *cfg = malloc(sizeof(config));
    if (cfg == NULL) {
        fprintf(stderr, "Memory allocation failed for config\n");
        return 1;
    }

    printf("Loading config...\n");
    if (loadConfig(cfg) != 0) {
        fprintf(stderr, "Failed to load config.\n");
        return 1;
    }

    if (cfg->generalConfig.wallpaperPath) {
        printf("Wallpaper path: %s\n", cfg->generalConfig.wallpaperPath);
        setRootBackground(display, root, cfg->generalConfig.wallpaperPath);
    }
    
    printf("Entering event loop...\n");
    for (;;) {
        XNextEvent(display, &event);
        eventHandler(&event);
        XSync(display, 0);
    }

    XCloseDisplay(display);
    free(cfg);
    return 0;
}