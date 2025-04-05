#include "event.h"
#include "mouse.h"
#include "keyboard.h"
#include <stdio.h>

void eventHandler(XEvent *event) {
    printf("EventHandler called with event type: %d\n", event->type);  
    switch (event->type) {
        case KeyPress:
            handleKeyboardEvent(event);
            break;
        case ButtonPress:
            handleMouseEvent(event);
            break;
        default:
            printf("Unhandled event\n");
            break;
    }
}
