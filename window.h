#ifndef WINDOW_H_
#define WINDOW_H_

#include <X11/Xlib.h>
#include <unistd.h>
#include <stdint.h>

void handleCreateNotify(XEvent *event);
void handleDestroyNotify(XEvent *event);
void handleReparentNotify(XEvent *event);
void handleMapNotify(XEvent *event);
void handleUnmapNotify(XEvent *event, Display *dpy, Window root);
void handleConfigureRequestEvent(XEvent *event);
void handleMapRequest(XEvent *event, Display *dpy, Window root);

#endif // WINDOW_H_
