#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <X11/Xlib.h>
#include <unistd.h>
#include <stdint.h>
#include <X11/Xutil.h>

void setWallpaper(const char *wallpaperPath);
void handleCreateNotify(XEvent *event);
void handleDestroyNotify(XEvent *event);
void handleReparentNotify(XEvent *event);
void handleMapNotify(XEvent *event);
void handleUnmapNotify(XEvent *event, Display *dpy, Window root);
void handleConfigureRequestEvent(XEvent *event);
void handleMapRequest(XEvent *event, Display *dpy, Window root);

void setWallpaper(const char *wallpaperPath);

#endif // _WINDOW_H_
