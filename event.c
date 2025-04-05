#include "event.h"
#include "mouse.h"
#include "keyboard.h"
#include "window.h"
#include <stdio.h>


void eventHandler(XEvent *event, Display *dpy, Window root) {
    printf("EventHandler called with event type: %d\n", event->type);
    switch (event->type) {
        case KeyPress:
            handleKeyboardEvent(event);
            break;
        case ButtonPress:
            handleMouseEvent(event);
            break;
        case CreateNotify:
            handleCreateNotify(event);
            break;
        case DestroyNotify:
            handleDestroyNotify(event);
            break;
        case ConfigureRequest:
            handleConfigureRequestEvent(event);
            break;
        case MapRequest:
            handleMapRequest(event, dpy, root);
            break;
        case ReparentNotify:
            handleReparentNotify(event);
            break;
        case MapNotify:
            handleMapNotify(event);
            break;
        case UnmapNotify:
            handleUnmapNotify(event, dpy, root);
            break;
        default:
            printf("Unhandled event\n");
            break;
    }
}
