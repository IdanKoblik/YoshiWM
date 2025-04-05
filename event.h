#ifndef EVENT_H
#define EVENT_H

#include <X11/Xlib.h>

void handleKeyboardEvent(XEvent *event);
void handleMouseEvent(XEvent *event);

typedef void (*EventHandler)(XEvent *);
EventHandler eventHandler(XEvent *event);

#endif