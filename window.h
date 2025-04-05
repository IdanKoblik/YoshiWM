#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "stb_image.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

XImage* loadWallpaper(Display *display, const char *path, int *width, int *height);
void setRootBackground(Display *display, Window root, const char *wallpaperPath);

#endif