#include "window.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>

void setWallpaper(const char *wallpaperPath) {
    char command[1024];
    snprintf(command, sizeof(command), "feh --bg-scale %s", wallpaperPath);

    int output = system(command);
    if (output != 0)
        fprintf(stderr, "Error: feh command failed to set wallpaper\n");
    else
        printf("Wallpaper set successfully with feh\n");
}