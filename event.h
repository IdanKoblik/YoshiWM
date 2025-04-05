#ifndef EVENT_H
#define EVENT_H

#include <X11/Xlib.h>
#include <stdio.h>
#include "window.h"

void eventHandler(XEvent *event, Display *dpy, Window root);

#endif
