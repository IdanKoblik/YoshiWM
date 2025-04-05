#include "event.h"
#include "stdio.h"

void handleKeyboardEvent(XEvent *event) {
    if (event->type != KeyPress)
        return;

    printf("OH KEYBOARD");
}