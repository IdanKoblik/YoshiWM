#include "mouse.h"

void handleMouseEvent(XEvent *event) {
    if (event->type != ButtonPress)
        return;

    printf("MOUSE\n");
}