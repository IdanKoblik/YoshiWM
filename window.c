#include "window.h"
#include <X11/Xlib.h>
<<<<<<< HEAD
#include <X11/Xutil.h>
#include <stdbool.h>
=======
>>>>>>> f79ff52 (Map window + other things)

void handleCreateNotify(XEvent *event) {}
void handleDestroyNotify(XEvent *event) {}
void handleReparentNotify(XEvent *event) {}
void handleMapNotify(XEvent *event) {}

void handleConfigureRequestEvent(XEvent *event) {
    XConfigureRequestEvent e = event->xconfigurerequest;
    XWindowChanges changes;
    changes.x = e.x;
    changes.y = e.y;
    changes.width = e.width;
    changes.height = e.height;
    changes.border_width = 2; // just a random number
    changes.sibling = e.above;
    changes.stack_mode = e.detail;

    XConfigureWindow(e.display, e.window, e.value_mask, &changes);
}

void frameWindow(Window win, Display *dpy, Window root) {
    const unsigned int BORDER_WIDTH = 2;
    const unsigned long BORDER_COLOR = 0xff0000;
    const unsigned long BG_COLOR = 0x0000ff;

    XWindowAttributes xAttrs;
    XGetWindowAttributes(dpy, win, &xAttrs);


    Window frame = XCreateSimpleWindow(
        dpy,
        root,
        xAttrs.x,
        xAttrs.y,
        xAttrs.width,
        xAttrs.height,
        BORDER_WIDTH,
        BORDER_COLOR,
        BG_COLOR);

    XSelectInput(dpy, frame, SubstructureRedirectMask | SubstructureNotifyMask);

    XReparentWindow(dpy, root, frame, 0, 0);

    XMapWindow(dpy, frame);
}

void handleMapRequest(XEvent *event, Display *dpy, Window root) {
    XMapRequestEvent e = event->xmaprequest;

    frameWindow(e.window, dpy, root);

    XMapWindow(dpy, e.window);
}

void handleUnmapNotify(XEvent *event, Display *dpy, Window root) {
    XUnmapEvent e = event->xunmap;

    Window frame = e.window;

    XUnmapWindow(dpy, frame);
    XReparentWindow(dpy, frame, root, 0, 0);

    XRemoveFromSaveSet(dpy, frame);
    XDestroyWindow(dpy, frame);
}
