#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    Display *display;
    Window window;
    XEvent event;

    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Error accure while trying to open a display\n");
        exit(1);
    }

    int screen = DefaultScreen(display);

    window = XCreateSimpleWindow(display,
        RootWindow(display, screen),
        10, 10, 200, 200, 1,
        BlackPixel(display, screen),
        WhitePixel(display, screen)
    );

    while (1) {
        XNextEvent(display, &event);
    }

    XCloseDisplay(display);

    return 0;
}
