#include "event.h"

EventHandler eventHandler(XEvent *event) {
    switch (event->type) {
        case KeyPress:
            return handleKeyboardEvent;

        case ButtonPress:
            return handleMouseEvent;
    
        default:
            return NULL;
    }
}