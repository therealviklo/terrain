#include "image.h"

void loadImages(DirectV& dv, images_t& images)
{
	images[LOWERCASEMU] = std::make_unique<Bitmap>(dv.createBitmap(L"gfx/lowercaseMu.bmp"));
	images[TILES] = std::make_unique<Bitmap>(dv.createBitmap(L"gfx/tiles.png"));
}

Image::Image() noexcept
	: imageID(LOWERCASEMU),
	  entireImage(false),
	  x(0.0f),
	  y(0.0f),
	  width(0.0f),
	  height(0.0f),
	  dispWidth(0.0f),
	  dispHeight(0.0f) {}

Image::Image(ImageID imageID, float x, float y, float width, float height) noexcept
	: imageID(imageID),
	  entireImage(false),
	  x(x),
	  y(y),
	  width(width),
	  height(height),
	  dispWidth(width),
	  dispHeight(height) {}

Image::Image(ImageID imageID, float dispWidth, float dispHeight) noexcept
	: imageID(imageID),
	  entireImage(true),
	  dispWidth(dispWidth),
	  dispHeight(dispHeight) {}

Image::Image(ImageID imageID, float dispWidth, float dispHeight, float x, float y, float width, float height) noexcept
	: imageID(imageID),
	  entireImage(false),
	  x(x),
	  y(y),
	  width(width),
	  height(height),
	  dispWidth(dispWidth),
	  dispHeight(dispHeight) {}

void Image::draw(float x, float y, DirectV& dv, images_t& images) const
{
	if (entireImage)
	{
		dv.drawBitmap(int(x), int(y), dispWidth, dispHeight, *images[imageID]);
	}
	else
	{
		dv.drawBitmap(int(x), int(y), dispWidth, dispHeight, this->x, this->y, width, height, *images[imageID]);
	}
}