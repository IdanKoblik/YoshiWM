#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/cursorfont.h>
#include "event.h"


int main(void) {
    Display *display;
    XEvent event;
    Window root;

    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Error occurred while trying to open a display\n");
        exit(1);
    }

    root = DefaultRootWindow(display);
    XSelectInput(display, DefaultRootWindow(display), KeyPressMask | ButtonPressMask);
    XSync(display, 0);

    Cursor cursor = XCreateFontCursor(display, XC_left_ptr);
    XDefineCursor(display, root, cursor);
    XSync(display, False);

    for (;;) {
        XNextEvent(display, &event);
        printf("Event received: %d\n", event.type);  // Debugging line
        eventHandler(&event, display, root);
        XSync(display, 0);
    }

    XCloseDisplay(display);
    return 0;
}
