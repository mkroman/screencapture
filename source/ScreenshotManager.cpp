#include <iostream>
#include <X11/cursorfont.h>
#include <giblib/giblib.h>

#include "ScreenshotManager.h"
#include "Screenshot.h"

ScreenshotManager::ScreenshotManager()
{
	display = XOpenDisplay(0);

	if (!display)
	{
		fprintf(stderr, "Could not connect to display :0!\n");
		return;
	}

	screen = ScreenOfDisplay(display, DefaultScreen(display));

	colormap = DefaultColormap(display, XScreenNumberOfScreen(screen));
	visual = DefaultVisual(display, XScreenNumberOfScreen(screen));
	depth = DefaultDepth(display, XScreenNumberOfScreen(screen));
	root = RootWindow(display, XScreenNumberOfScreen(screen));

	width = DisplayWidth(display, XScreenNumberOfScreen(screen));
	height = DisplayHeight(display, XScreenNumberOfScreen(screen));

	imlib_context_set_display(display);
	imlib_context_set_visual(visual);
	imlib_context_set_colormap(colormap);
	imlib_context_set_color_modifier(NULL);
	imlib_context_set_operation(IMLIB_OP_COPY);
}

ScreenshotManager::~ScreenshotManager()
{
}

Screenshot* ScreenshotManager::captureWindow(Window* window)
{
	Window target;
	int x, y;
	unsigned int width, height, border, depth;

	if (XTranslateCoordinates(display, *window, root, 0, 0, &x, &y, &target))
		return captureRegion(x, y, 800, 600);
	else
		return NULL;
}

Screenshot* ScreenshotManager::captureFullscreen()
{
	Screenshot* image = new Screenshot();

	if (image->captureRegion(&root, 0, 0, width, height))
		return image;

	return NULL;
}

Screenshot* ScreenshotManager::captureRegion(int x, int y, int width, int height)
{
	Screenshot* image = new Screenshot();

	if (image->captureRegion(&root, x, y, width, height))
		return image;

	return NULL;
}

Screenshot* ScreenshotManager::captureSelectiveRegion()
{

	Screenshot* image;
	bool complete = false;
	Cursor cursor = XCreateFontCursor(display, XC_crosshair);
	XEvent event;

	if (XGrabPointer(display, root, false, ButtonPressMask, GrabModeAsync, GrabModeAsync, root, cursor, CurrentTime) != GrabSuccess)
		std::cout << "Could not grab keyboard." << std::endl;

	while (true)
	{
		while (!complete && XPending(display))
		{
			XNextEvent(display, &event);

			switch (event.type) {
				case ButtonPress:
					image = captureWindow(&event.xbutton.subwindow);
					printf("Selected window's pointer reference: 0x%x\n", (unsigned int)event.xbutton.subwindow);
					complete = true;

					break;
				default:
					break;
			}
		}

		if (complete)
			break;
	}

	return image;
}
