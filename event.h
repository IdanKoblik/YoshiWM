#ifndef _EVENT_H_
#define _EVENT_H_

#include <X11/Xlib.h>
#include <stdio.h>
#include "window.h"

void eventHandler(XEvent *event, Display *dpy, Window root);

#endif // _EVENT_H_
