#ifndef __SCREENSHOT_MANAGER_H
#define __SCREENSHOT_MANAGER_H

#define SCREENSHOTMANAGER ScreenshotManager::Instance()

#include <giblib/giblib.h>

class Screenshot;

class ScreenshotManager {
public:
	~ScreenshotManager();
	static ScreenshotManager& Instance() {
		static ScreenshotManager instance;
		return instance;
	}

	Screenshot* captureSelectiveRegion();
	Screenshot* captureWindow(Window* window);
	Screenshot* captureRegion(int x, int y, int width, int height);
	Screenshot* captureFullscreen();

protected:
	ScreenshotManager();

	int      depth, width, height;
	Window   root;
	Screen*  screen;
	Visual*  visual;
	Display* display;
	Colormap colormap;
};

#endif
