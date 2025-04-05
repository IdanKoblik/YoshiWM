#include "window.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>

#include "stb_image.h"

XImage* loadWallpaper(Display *display, const char *path, int *width, int *height) {
    printf("Loading wallpaper from path: %s\n", path);

    unsigned char *image_data = stbi_load(path, width, height, NULL, STBI_rgb);
    if (!image_data) {
        const char *reason = stbi_failure_reason();
        fprintf(stderr, "Error loading wallpaper image: %s\nReason: %s\n", path, reason);
        return NULL;
    }

    printf("Loaded image with width: %d, height: %d\n", *width, *height);

    XImage *ximage = XCreateImage(
        display,
        DefaultVisual(display, 0),
        DefaultDepth(display, 0),
        ZPixmap,
        0,
        (char *)image_data,
        *width,
        *height,
        32,
        0
    );

    if (!ximage) {
        fprintf(stderr, "Error creating XImage\n");
        stbi_image_free(image_data);
        return NULL;
    }

    return ximage;
}

void setRootBackground(Display *display, Window root, const char *wallpaperPath) {
    int width, height;
    XImage *image = loadWallpaper(display, wallpaperPath, &width, &height);
    if (!image) {
        return;
    }

    Pixmap pixmap = XCreatePixmap(display, root, width, height, DefaultDepth(display, 0));
    GC gc = XCreateGC(display, root, 0, NULL);

    XPutImage(display, pixmap, gc, image, 0, 0, 0, 0, width, height);
    XFillRectangle(display, root, gc, 0, 0, width, height);
    XSetWindowBackgroundPixmap(display, root, pixmap);

    XFreeGC(display, gc);
    XFreePixmap(display, pixmap);
    XFree(image);
}