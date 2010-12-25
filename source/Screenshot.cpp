#include "Screenshot.h"

Screenshot::Screenshot() :
	image(NULL)
{
	// …
}

Screenshot::~Screenshot()
{
	if (image != NULL)
		gib_imlib_free_image(image);
}

bool Screenshot::captureRegion(Window* root, int x, int y, int width, int height)
{
	if (image != NULL)
		gib_imlib_free_image(image);

	image = (Imlib_Image*)gib_imlib_create_image_from_drawable(*root, 0, x, y, width, height, 1);

	return true;
}

bool Screenshot::save(const char* filename)
{
	if (image != NULL)
	{
		gib_imlib_save_image(image, const_cast<char*>(filename));
		return true;
	} else
		return false;
}
