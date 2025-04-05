#include "keyboard.h"

void handleKeyboardEvent(XEvent *event) {
    if (event->type != KeyPress)
        return;

    printf("KEYBOARD\n");
}