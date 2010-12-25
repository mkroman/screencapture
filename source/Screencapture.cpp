#include <string>
#include <stdio.h>
#include <iostream>

#include "ScreenshotManager.h"
#include "Screenshot.h"

int main(int argc, char** argv)
{
	char* filename = "screencapture.png";

	if (argv[1] != NULL)
		filename = argv[1];

	Screenshot* image = SCREENSHOTMANAGER.captureSelectiveRegion();

	if (image != NULL)
	{
		std::cout << "Image captured, saving \u2026" << std::endl;

		if (image->save(filename))
			std::cout << "Done." << std::endl;
		else
			std::cout << "Could not save." << std::endl;
	} else
		std::cout << "Screenshot could not be taken \u2026" << std::endl;

	return 0;
}
