#include "event.h"
#include "stdio.h"

void handleMouseEvent(XEvent *event) {
    if (event->type != ButtonPress)
        return;

    printf("OH MOUSE");
}