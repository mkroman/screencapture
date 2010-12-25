#ifndef __SCREENSHOT_H
#define __SCREENSHOT_H

#include <string>
#include <giblib/giblib.h>

class Screenshot {
public:
	Screenshot();
	~Screenshot();

	bool captureRegion(Window* root, int x, int y, int width, int height);

	bool save(const char* filename);

private:
	Imlib_Image* image;
};

#endif
